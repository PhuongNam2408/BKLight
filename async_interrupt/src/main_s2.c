/***************************************************************************//**
 * @file main_s2.c
 *
 * @brief This project demonstrates asynchronous mode use of the USART
 * with interrupts.
 *
 * After initialization, the MCU goes into EM1 where the receive interrupt
 * handler buffers incoming data until the reception of 80 characters or a
 * CR (carriage return, ASCII 0x0D).
 *
 * Once the CR or 80 characters is hit, the receive data valid interrupt is
 * disabled, and the transmit buffer level interrupt, which, by default, is set
 * after power-on, is is enabled.  Each entry into the transmit interrupt
 * handler causes a character to be sent until all the characters originally
 * received have been echoed.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *******************************************************************************
 * # Evaluation Quality
 * This code has been minimally tested to ensure that it builds and is suitable
 * as a demonstration for evaluation purposes only. This code will be maintained
 * at the sole discretion of Silicon Labs.
 ******************************************************************************/

//#include "em_device.h"
//#include "em_chip.h"
//#include "em_emu.h"
//#include "em_cmu.h"
//#include "em_gpio.h"
//#include "em_usart.h"

#include "LoRa.h"
#include "pwm.h"
#include "delay.h"

// BSP for board controller pin macros
#include "bsp.h"

/**************************************************************************//**
 * @brief
 *    Define
 *****************************************************************************/

// Size of the buffer for received data
#define BUFLEN  80

// Define VALUE
#define ADDH          0xFF
#define ADDL          0xFF
#define CHAN          0x0f
#define SRC_SYNC1     0x45
#define SRC_SYNC2     0x4E
#define SRC_ADDR_H    0x00
#define SRC_ADDR_L    0x02

// Define pwm_lut
#define LED_DIMMING_PIR_ON  pwm_lut[100]
#define LED_DIMMING_PIR_OFF pwm_lut[0]

// Define LED control state
#define LED_CONTROL_ON      pwm_lut[100]
#define LED_CONTROL_OFF     pwm_lut[0]

// Define LENGTH
#define LENGTH_AUTO             10
#define LENGTH_VALUE_LED        8
#define LENGTH_VALUE_CRSENSOR   5
#define LENGTH_SYNCTIME         0

// Define set USART

#define USART_INITASYNC_SET                                                                  \
  {                                                                                                \
    usartEnable,           /* Enable RX/TX when initialization is complete. */                     \
    0,                     /* Use current configured reference clock for configuring baud rate. */ \
    115200,                /* 115200 bits/s. */                                                    \
    usartOVS16,            /* 16x oversampling. */                                                 \
    usartDatabits8,        /* 8 data bits. */                                                      \
    usartNoParity,         /* No parity. */                                                        \
    usartStopbits1,        /* 1 stop bit. */                                                       \
    false,                 /* Do not disable majority vote. */                                     \
    false,                 /* Not USART PRS input mode. */                                         \
    0,                     /* PRS channel 0. */                                                    \
    false,                 /* Auto CS functionality enable/disable switch */                       \
    false,                 /* No CS invert. */                                                     \
    0,                     /* Auto CS Hold cycles. */                                              \
    0,                     /* Auto CS Setup cycles. */                                             \
    usartHwFlowControlNone /* No HW flow control. */                                               \
  }

/**************************************************************************//**
 * @brief
 *    Initial
 *****************************************************************************/

// Receive data buffer
uint8_t buffer[BUFLEN];

// Current position ins buffer
uint32_t inpos = 0;
uint32_t outpos = 0;

// CRC
uint8_t CRC_led;
uint8_t CRC_crsensor;

// Mảng giá trị độ sáng dimming đèn theo %
uint8_t pwm_lut[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
    100
};

// Receive data characters
uint8_t key;
uint8_t ctrl_led;
uint8_t ctrl_dimming;
uint16_t val;
uint8_t dimming;

// Define messages transmit
uint8_t message_led[LENGTH_AUTO + LENGTH_VALUE_LED];
uint8_t message_crsensor[LENGTH_AUTO + LENGTH_VALUE_CRSENSOR];
uint8_t message_synctime[LENGTH_AUTO + LENGTH_SYNCTIME];

// True while receiving data (waiting for CR or BUFLEN characters)
bool receive = true;

// Định nghĩa biến sl_pwm_led0 ở đây để nó trở thành biến toàn cục
sl_pwm_instance_t sl_pwm_led0;

/**************************************************************************//**
 * @brief
 *    SYSCLK initialization
 *****************************************************************************/
void SYSCLK_Init(void) {
  // Freq of sysclk is 80MHz
  CMU_HFRCODPLLBandSet(cmuHFRCODPLLFreq_80M0Hz);
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLL);
}

/**************************************************************************//**
 * @brief
 *    SYSTICK initialization
 *****************************************************************************/
void SysTick_Init(uint32_t ticks) {
    // Thiết lập SysTick Reload Register với số ticks cần đếm
    SysTick->LOAD = ticks - 1;

    // Đặt nguồn clock cho SysTick (VD: HCLK)
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

    // Bật SysTick timer
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    // Bật ngắt SysTick
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

/**************************************************************************//**
 * @brief
 *    CMU initialization
 *****************************************************************************/
void initCMU(void)
{
  // Enable clock to GPIO and USART0
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_USART0, true);
}

/**************************************************************************//**
 * @brief
 *    GPIO initialization
 *****************************************************************************/
void initGPIO(void)
{
  // Configure the USART TX pin to the board controller as an output
  GPIO_PinModeSet(TX_PORT, TX_PIN, gpioModePushPull, 0);

  // Configure the USART RX pin to the board controller as an input
  GPIO_PinModeSet(RX_PORT, RX_PIN, gpioModeInput, 0);

//  GPIO_PinModeSet(M0_PORT, M0_PIN, gpioModePushPull, 0);
//  GPIO_PinModeSet(M1_PORT, M1_PIN, gpioModePushPull, 0);

  /*
   * Configure the BCC_ENABLE pin as output and set high.  This enables
   * the virtual COM port (VCOM) connection to the board controller and
   * permits serial port traffic over the debug connection to the host
   * PC.
   *
   * To disable the VCOM connection and use the pins on the kit
   * expansion (EXP) header, comment out the following line.
   */
 // GPIO_PinModeSet(BSP_BCC_ENABLE_PORT, BSP_BCC_ENABLE_PIN, gpioModePushPull, 1);
  // Configure the LED0
  //GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);
}

/**************************************************************************//**
 * @brief
 *    USART0 initialization
 *****************************************************************************/
void initUSART0(void)
{
  // Default asynchronous initializer (115.2 Kbps, 8N1, no flow control)
  USART_InitAsync_TypeDef init = USART_INITASYNC_SET;

  // Route USART0 TX and RX to the board controller TX and RX pins
  GPIO->USARTROUTE[0].TXROUTE = (BSP_BCC_TXPORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
      | (BSP_BCC_TXPIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].RXROUTE = (BSP_BCC_RXPORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
      | (BSP_BCC_RXPIN << _GPIO_USART_RXROUTE_PIN_SHIFT);

  // Enable RX and TX signals now that they have been routed
  GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;

  // Configure and enable USART0
  USART_InitAsync(USART0, &init);

  // Enable NVIC USART sources
  NVIC_ClearPendingIRQ(USART0_RX_IRQn);
  NVIC_EnableIRQ(USART0_RX_IRQn);
  NVIC_ClearPendingIRQ(USART0_TX_IRQn);
  NVIC_EnableIRQ(USART0_TX_IRQn);

  // Configure PIR
  GPIO_PinModeSet(PIR_PORT, PIR_PIN, gpioModeInputPullFilter, 1);
}

/**************************************************************************//**
 * @brief
 *    Receive - Transmit
 *****************************************************************************/

// Create struct

struct VALUE_LED
{
  uint32_t TIMESTAMP;
  uint8_t LED_STATE;
  uint8_t LED_DIMMING;
  uint16_t CURRENT_SENSOR;
};

struct VALUE_CURRENT_SENSOR
{
  uint32_t TIMESTAMP;
  uint8_t WARNING;
};

struct VALUE_TIMEMARK
{
  uint8_t TIMEMARK_1;
  uint8_t TIMEMARK_2;
  uint8_t TIMEMARK_3;
  uint8_t TIMEMARK_4;
};

// Initial struct

struct VALUE_LED vl_led =
    {
        .TIMESTAMP = 0x01020304,
        .LED_STATE = 0,
        .LED_DIMMING = 5,
        .CURRENT_SENSOR = 64000
    };

struct VALUE_CURRENT_SENSOR vl_crsensor =
    {
        .TIMESTAMP = 0x0506071a,
        .WARNING = 1
    };
struct VALUE_TIMEMARK vl_timemark =
    {
        .TIMEMARK_1 = 0,
        .TIMEMARK_2 = 0,
        .TIMEMARK_3 = 0,
        .TIMEMARK_4 = 0
    };

// Functions

uint8_t check_LED_STATE (GPIO_Port_TypeDef port, unsigned int pin) {
  uint8_t led_state;
  if (vl_led.LED_DIMMING > pwm_lut[0])
      led_state = 1;
  else {
      led_state = 0;
   }
  return led_state;
}

static uint8_t CALCRC(uint8_t *data, int length)
{
  short csum = 0;
  for (size_t i = 0; i < length; i++) {
      csum += (short)data[i];
  }
  csum = 255 - (csum % 255);
  return (uint8_t)csum;
}

/**************************************************************************//**
 * @brief
 *    The USART0 receive interrupt saves incoming characters.
 *****************************************************************************/

void USART0_RX_IRQHandler(void)
{
  // Get the character just received
  buffer[inpos] = USART0->RXDATA;

  // Exit loop on new line or buffer full
  if ((buffer[inpos] != 0x0D) && (inpos < BUFLEN))
    inpos++;
  else
    receive = false;   // Stop receiving on CR

//  if (buffer[3] == 0x41)
//    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, !vl_led.LED_STATE);
//  else {
//    GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, vl_led.LED_STATE);
//  }
  key = buffer[0];
  if (key == 0x04)
    {
    ctrl_led = buffer[1];
    }
  else if (key == 0x05)
    ctrl_dimming = buffer[1];
  else if (key == 0x06)
      {
        vl_timemark.TIMEMARK_1 = buffer[1];
        vl_timemark.TIMEMARK_2 = buffer[2];
        vl_timemark.TIMEMARK_3 = buffer[3];
        vl_timemark.TIMEMARK_4 = buffer[4];
      }
}

/**************************************************************************//**
 * @brief
 *    Define messages for key 1->6
 *****************************************************************************/

void key_1()
{
  vl_led.LED_STATE = check_LED_STATE(LED_PORT, LED_PIN);
  vl_led.LED_DIMMING = dimming;
  vl_led.CURRENT_SENSOR = val;

  // For Key == 1
    message_led[0] = ADDH;
    message_led[1] = ADDL;
    message_led[2] = CHAN;
    message_led[3] = SRC_SYNC1;
    message_led[4] = SRC_SYNC2;
    message_led[5] = SRC_ADDR_H;
    message_led[6] = SRC_ADDR_L;
    message_led[7] = key;
    message_led[8] = LENGTH_VALUE_LED;

    memcpy(&message_led[9], &vl_led, LENGTH_VALUE_LED);

    message_led[17] = CALCRC(&message_led[9], LENGTH_VALUE_LED);
}
void key_2()
{
  // FOR Key == 2
   message_crsensor[0] = ADDH;
   message_crsensor[1] = ADDL;
   message_crsensor[2] = CHAN;
   message_crsensor[3] = SRC_SYNC1;
   message_crsensor[4] = SRC_SYNC2;
   message_crsensor[5] = SRC_ADDR_H;
   message_crsensor[6] = SRC_ADDR_L;
   message_crsensor[7] = key;
   message_crsensor[8] = LENGTH_VALUE_CRSENSOR;

   memcpy(&message_crsensor[9], &vl_crsensor, LENGTH_VALUE_CRSENSOR - 1);

   message_crsensor[13] = vl_crsensor.WARNING;
   message_crsensor[14] = CALCRC(&message_crsensor[9], LENGTH_VALUE_CRSENSOR);
}

void key_3()
{
  // FOR Key == 3
  message_synctime[0] = ADDH;
  message_synctime[1] = ADDL;
  message_synctime[2] = CHAN;
  message_synctime[3] = SRC_SYNC1;
  message_synctime[4] = SRC_SYNC2;
  message_synctime[5] = SRC_ADDR_H;
  message_synctime[6] = SRC_ADDR_L;
  message_synctime[7] = 0x03;
  message_synctime[8] = LENGTH_SYNCTIME;
  message_synctime[9] = 0x12;
}

// Define messages receive

void key_4()
{
  if (ctrl_led == 0x01)
    {
    sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[100]);
    dimming = pwm_lut[100];
    }
  else if (ctrl_led == 0x00)
    {
    sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[0]);
    dimming = pwm_lut[0];
    }
}

void key_5()
{
  sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[ctrl_dimming]);
}

/**************************************************************************//**
 * @brief
 *    The USART0 transmit interrupt outputs characters.
 *****************************************************************************/
void USART0_TX_IRQHandler(void)
{
    key_1();
    key_2();

    if(key == 0x01) {
        if(outpos < LENGTH_AUTO + LENGTH_VALUE_LED)
              USART0->TXDATA = message_led[outpos++];
          else
          {
            receive = true;   // Go back into receive when all is sent
            USART_IntDisable(USART0, USART_IEN_TXBL);
          }
    }
    else if (key == 0x02) {
        if(outpos < LENGTH_AUTO + LENGTH_VALUE_CRSENSOR)
              USART0->TXDATA = message_crsensor[outpos++];
        else
          {
            receive = true;   // Go back into receive when all is sent
            USART_IntDisable(USART0, USART_IEN_TXBL);
          }
    }
    else
      {
        receive = true;   // Go back into receive when all is sent
        USART_IntDisable(USART0, USART_IEN_TXBL);
      }
}

void check_PIR()
{
  sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[10]);
     // Đọc trạng thái của cảm biến PIR
     if (GPIO_PinInGet(PIR_PORT, PIR_PIN)){
         // Bật đèn LED 100%
         sl_pwm_set_duty_cycle(&sl_pwm_led0, LED_DIMMING_PIR_ON);
         dimming = LED_DIMMING_PIR_ON;
     }
     else
       {
         sl_pwm_set_duty_cycle(&sl_pwm_led0, LED_DIMMING_PIR_OFF);
         dimming = LED_DIMMING_PIR_OFF;
         if (key == 0x04)
           key_4();
         if (key == 0x05)
           key_5();
       }
}

int main(void)
{
  uint32_t i;
   SYSCLK_Init();
    CHIP_Init();
    Delay_Init();
    // Khởi tạo và cấu hình SysTick timer (VD: 1ms)
    SysTick_Init(SystemCoreClock / 1000);
    // Init_I2C();
    // BH1750_Init(0x46,buf,1);
    //CMU_ClockEnable(cmuClock_GPIO, true);
      initCMU();
      initGPIO();
      initUSART0();

      uint8_t buf[1] = {0x10};
      Init_I2C();
      BH1750_Init(0x46,buf,1);

    // Enable PWM output
    sl_pwm_led0 = (sl_pwm_instance_t) {
        .timer    = TIMER0,
        .channel  = 0,
        .port     = gpioPortC,
        .pin      = 0,
        .location = 0,
    };

    sl_pwm_config_t pwm_led0_config = {
        .frequency = 10000,
        .polarity  = PWM_ACTIVE_HIGH,
    };




//    // Enable transmit buffer level interrupt
//    USART_IntEnable(USART0, USART_IEN_TXBL);
//    if (!receive)
//      {
//        for (outpos = 0; outpos < LENGTH_AUTO + LENGTH_SYNCTIME; outpos++)
//              USART0->TXDATA = message_synctime[outpos];
//      }
//    else
//      {
//        receive = true;   // Go back into receive when all is sent
//        USART_IntDisable(USART0, USART_IEN_TXBL);
//      }





    // Initialize PWM
    sl_pwm_init(&sl_pwm_led0, &pwm_led0_config);

    sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[0]);

    // Enable PWM output
    sl_pwm_start(&sl_pwm_led0);

    Switch_Mode(MODE_0_NORMAL);
    USART_IntEnable(USART0, USART_IEN_RXDATAV);

while(1)
  {
     uint8_t buff[2] = {0,1};
     BH1750_Multi_Read(0x46, buff);
     val = ((buff[0] << 8) | buff[1]) / 1.2;

     if(val>500){
         GPIO_PinOutClear(LED_PORT, LED_PIN);
     }
     else
       {
         check_PIR();
       }
     if (receive == false)
     {
         // Disable receive data valid interrupt
         USART_IntDisable(USART0, USART_IEN_RXDATAV);

         // Enable transmit buffer level interrupt
         USART_IntEnable(USART0, USART_IEN_TXBL);

         while(receive == false) {}

         // Reset buffer indices
         inpos = outpos = 0;
         // Zero out buffer
         for (i = 0; i < BUFLEN; i++)
            buffer[i] = 0;
          // Enable receive data valid interrupt
         USART_IntEnable(USART0, USART_IEN_RXDATAV);
       }
     }
}



int time_count = 0;
void SysTick_Handler(void)
{
  time_count++;
}




///**************************************************************************//**
// * @brief
// *    Main function
// *****************************************************************************/
//int main(void)
//{
////  uint32_t i;
////  // Chip errata
////  CHIP_Init();
////
////  // Initialize GPIO and USART0
////  initCMU();
////  initGPIO();
////  initUSART0();
////
////  Switch_Mode(MODE_0_NORMAL);
////  USART_IntEnable(USART0, USART_IEN_RXDATAV);
//
//  CHIP_Init();
//      Delay_Init();
//      // Khởi tạo và cấu hình SysTick timer (VD: 1ms)
//      SysTick_Init(SystemCoreClock / 1000);
//      // Init_I2C();
//      // BH1750_Init(0x46,buf,1);
//      CMU_ClockEnable(cmuClock_GPIO, true);
//      GPIO_PinModeSet(PIR_PORT, PIR_PIN, gpioModeInputPullFilter, 1);
//      // Enable PWM output
//      sl_pwm_led0 = (sl_pwm_instance_t) {
//          .timer    = TIMER0,
//          .channel  = 0,
//          .port     = gpioPortC,
//          .pin      = 0,
//          .location = 0,
//      };
//
//      sl_pwm_config_t pwm_led0_config = {
//          .frequency = 10000,
//          .polarity  = PWM_ACTIVE_HIGH,
//      };
//
//      // Initialize PWM
//      sl_pwm_init(&sl_pwm_led0, &pwm_led0_config);
//
//      sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[10]);
//
//      // Enable PWM output
//      sl_pwm_start(&sl_pwm_led0);
//  while (1)
//  {
//      sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[10]);
//      if (GPIO_PinInGet(PIR_PORT, PIR_PIN)){
//              // Bật đèn LED 100%
//              sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[100]);
//              // Đợi một khoảng thời gian
//      }
//      else
//        {
//              sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[10]);
//         }
////    if (receive == false)
////    {
////            // Disable receive data valid interrupt
////            USART_IntDisable(USART0, USART_IEN_RXDATAV);
////
////            // Enable transmit buffer level interrupt
////            USART_IntEnable(USART0, USART_IEN_TXBL);
////
////            while(receive == 0) {}
////
////            // Reset buffer indices
////            inpos = outpos = 0;
////            // Zero out buffer
////            for (i = 0; i < BUFLEN; i++)
////               buffer[i] = 0;
////             // Enable receive data valid interrupt
////            USART_IntEnable(USART0, USART_IEN_RXDATAV);
////      }
//  }
//
////  while(1) {
////      // Zero out buffer
////      for (i = 0; i < BUFLEN; i++)
////        buffer[i] = 0;
////
////      USART_IntEnable(USART0, USART_IEN_RXDATAV);
////      USART0_RX_IRQHandler();
////      USART_IntDisable(USART0, USART_IEN_RXDATAV);
////
////      USART_IntEnable(USART0, USART_IEN_TXBL);
////      USART0_TX_IRQHandler();
////
////      inpos = outpos = 0;
////  }
//}
//





