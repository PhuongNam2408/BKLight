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

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_msc.h"
#include "em_wdog.h"
#include "LoRa_E32.h"
#include "PWM.h"
#include "delay.h"
#include "BH1750.h"
#include "nam_rtc.h"
#include "main.h"
#include "lora_data_frame.h"
#include "ACS712.h"


/**************************************************************************//**
 * @brief
 *    Declare function
 *****************************************************************************/


void SYSCLK_Init(void);
void SysTick_Init(uint32_t ticks);
uint8_t check_LED_STATE (GPIO_Port_TypeDef port, unsigned int pin);

void check_PIR(void);
static void PWM_Init(void);
static void PIR_Init(void);
static void Nam_Init(void);
static void Update_time(void);
static void Task_Read_Sensor(void);
static void Task_Control_Led(void);

/**************************************************************************//**
 * @brief
 *    Initial
 *****************************************************************************/

/* Biến nằm trong chương trình, 1 tick = 1ms */
uint32_t tick_count = 0;

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
uint16_t BH1750_val;
uint8_t dimming;


// True while receiving data (waiting for CR or BUFLEN characters)
bool receive = true;

// Định nghĩa biến sl_pwm_led0 ở đây để nó trở thành biến toàn cục
sl_pwm_instance_t sl_pwm_led0;

extern uint32_t ACS712_Buffer[];

End_Node_Data_t vl_led = {
  .timestamp = 0,
  .led_state = 0,
  .led_dimming = 5,
  .current_sensor = 64000
};

/*************** Các Biến quan trọng nhất của file ****************/
End_Node_Data_t node_data;

Sensor_value_t Sensor_value;

RTCTIME node_time;

RTCTIME node_gmt_plus_7_time;

/* Chứa 4 mốc thời gian ứng với các giá trị default */
Time_Mark_t node_time_mark =
    {   .Time_Mark_1_hour = 18,
        .Time_Mark_1_minute = 00,
        .Time_Mark_2_hour = 22,
        .Time_Mark_2_minute = 30,
        .Time_Mark_3_hour = 02,
        .Time_Mark_3_minute = 30,
        .Time_Mark_4_hour = 06,
        .Time_Mark_4_minute = 00
    };

time_state_t node_time_state;
uint8_t led_state_default;
uint8_t led_dimming_default;

int main(void)
{
  SYSCLK_Init();
  CHIP_Init();
  Delay_Init();
  // Khởi tạo và cấu hình SysTick timer (VD: 1ms)
  SysTick_Init(SystemCoreClock / 1000);
  LoRa_E32_Init();
  Init_I2C();
  uint8_t bh1750_init_val[1] = {0x10};
  BH1750_Init(0x46,bh1750_init_val,1);

  PWM_Init();
  PIR_Init();
  RTC_Init();

  Nam_Init();

  while(1)
  {
     /* Cập nhật RTC */
     Update_time();

     Task_Read_Sensor();

     Task_Control_Led();

     LORA_Send_End_Node_Data(node_data);
     //Task_UART_Rx();
     Task_UART_Tx();
     Delay_ms(2000);
   }
}



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


uint8_t check_LED_STATE (GPIO_Port_TypeDef port, unsigned int pin) {
  uint8_t led_state;
  if (vl_led.led_dimming > pwm_lut[0])
      led_state = 1;
  else {
      led_state = 0;
   }
  return led_state;
}



/**************************************************************************//**
 * @brief
 *    PWM Init
 *****************************************************************************/
static void PWM_Init(void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(PWM_LED_PORT, PWM_LED_PIN, gpioModePushPull, 0);

  // Enable PWM output
  sl_pwm_led0 = (sl_pwm_instance_t) {
      .timer    = TIMER0,
      .channel  = 0,
      .port     = PWM_LED_PORT,
      .pin      = PWM_LED_PIN,
      .location = 0,
  };

  sl_pwm_config_t pwm_led0_config = {
      .frequency = 10000,
      .polarity  = PWM_ACTIVE_HIGH,
  };

// Initialize PWM
  sl_pwm_init(&sl_pwm_led0, &pwm_led0_config);

  sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[0]);

  // Enable PWM output
  sl_pwm_start(&sl_pwm_led0);

}


void check_PIR()
{
  // Đọc trạng thái của cảm biến PIR
  if (GPIO_PinInGet(PIR_OUT_PORT, PIR_OUT_PIN)){
    // Bật đèn LED 100%
    sl_pwm_set_duty_cycle(&sl_pwm_led0, LED_DIMMING_PIR_ON);
    dimming = LED_DIMMING_PIR_ON;
  }
  else
  {
    sl_pwm_set_duty_cycle(&sl_pwm_led0, LED_DIMMING_PIR_OFF);
    dimming = LED_DIMMING_PIR_OFF;
//    if (key == 0x04)
//
//    if (key == 0x05)

  }
}

static void PIR_Init(void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(PIR_OUT_PORT, PIR_OUT_PIN, gpioModeInput, 0);
}


uint8_t synctime_flag = 0;
static void Nam_Init(void)
{
  /* Đưa LoRa về cấu hình mặc định */
  Lora_Configuration_t Lora_Config;

  LoRa_getConfiguration(&Lora_Config);

  Lora_Config.ADDH = (uint8_t) (END_NODE_ADDR >> 8);
  Lora_Config.ADDL = (uint8_t) (END_NODE_ADDR & 0xFF);

  Lora_Config.SPED.airDataRate = AIR_DATA_RATE_101_192;
  Lora_Config.SPED.uartParity = MODE_00_8N1;
  Lora_Config.SPED.uartBaudRate = UART_BPS_115200;

  Lora_Config.CHAN = LORA_CHANNEL;

  Lora_Config.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
  Lora_Config.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
  Lora_Config.OPTION.wirelessWakeupTime = WAKE_UP_250;
  Lora_Config.OPTION.fec = FEC_1_ON;
  Lora_Config.OPTION.transmissionPower = POWER_20;

  LoRa_setConfiguration(Lora_Config, WRITE_CFG_PWR_DWN_SAVE);
  LoRa_getConfiguration(&Lora_Config);

   synctime: LORA_Send_Synctime();
  Task_UART_Tx();
  uint32_t prev_time = tick_count;
  while(synctime_flag == 0){
      Delay_ms(10);
      Task_UART_Rx();
      /* Sau 100ms không nhận được => request lại 1 lần nữa */
      if(tick_count - prev_time > 1000 ){
          goto synctime;
      }
  }
}

static void Update_time(void)
{
  RTC_GetTime(&node_time);
  node_data.timestamp = RTC_GetTicksFromTime(&node_time);

  /* Sử dụng GMT+7 làm thời gian so sánh */
  node_gmt_plus_7_time = node_time;
  // Add 7 hours to the copied time to get GMT+7 time
  node_gmt_plus_7_time.hour += 7;

   // Handle wrapping around to the next day if necessary
   if (node_gmt_plus_7_time.hour >= 24) {
       node_gmt_plus_7_time.hour -= 24;
       node_gmt_plus_7_time.mday += 1; // Increment the day

       // Check if the day exceeds the number of days in the current month
       int days_in_month;
       switch (node_gmt_plus_7_time.month) {
           case 3: case 5: case 8: case 10: // April, June, September, November have 30 days
               days_in_month = 30;
               break;
           case 1: // February has 28 or 29 days (account for leap years)
               days_in_month = (node_gmt_plus_7_time.year % 4 == 0 &&
                               (node_gmt_plus_7_time.year % 100 != 0 || node_gmt_plus_7_time.year % 400 == 0)) ? 29 : 28;
               break;
           default: // All other months have 31 days
               days_in_month = 31;
               break;
       }

       // Check if the day exceeds the number of days in the month
       if (node_gmt_plus_7_time.mday > days_in_month) {
           node_gmt_plus_7_time.mday = 1; // Set day to 1
           node_gmt_plus_7_time.month += 1;  // Increment the month

           // Check if the month exceeds December (11)
           if (node_gmt_plus_7_time.month > 11) {
               node_gmt_plus_7_time.month = 0; // Set month to January
               node_gmt_plus_7_time.year += 1; // Increment the year
           }
       }
   }
}

static void Task_Read_Sensor(void)
{
  /* Đọc cảm biến ánh sáng */
  uint8_t temp_buff[2] = {0,1};
  BH1750_Multi_Read(0x46, temp_buff);
  Sensor_value.BH1750 = ((temp_buff[0] << 8) | temp_buff[1]) / 1.2;

  /* Đọc cảm biến chuyển động */
  Sensor_value.PIR = GPIO_PinInGet(PIR_OUT_PORT, PIR_OUT_PIN);

  /* Đọc cảm biến dòng điện */
  Sensor_value.ACS712 = (uint16_t) ((ACS712_Buffer[0]*3.3/4095) - 2.5)*1000;
}

static void Task_Control_Led(void)
{
  /**************************************************************************/
  /************* Update giá trị default của LED theo Time mark **************/
  /**************************************************************************/
  //Khoảng 1: Sáng mạnh nhất: dimming = 100%
  if(((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min) >=
      (node_time_mark.Time_Mark_1_hour*60 + node_time_mark.Time_Mark_1_minute))
      &&
      ((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min) <
      (node_time_mark.Time_Mark_2_hour*60 + node_time_mark.Time_Mark_2_minute)))
  {

      led_state_default = LED_STATE_DEFAULT_1;
      led_dimming_default = LED_DIMMING_DEFAULT_1;
      node_time_state = TIME_STATE_1;
  }
  //Khoảng 2: Ít sáng hơn: dimming = 70%
  else if((((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min) >=
      (node_time_mark.Time_Mark_2_hour*60 + node_time_mark.Time_Mark_2_minute))
      &&
      (((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min) < 24*60)))
      ||
      (((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min)  >= 0)
      &&
      ((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min) <
      (node_time_mark.Time_Mark_3_hour*60 + node_time_mark.Time_Mark_3_minute))))
  {
      led_state_default = LED_STATE_DEFAULT_2;
      led_dimming_default = LED_DIMMING_DEFAULT_2;
      node_time_state = TIME_STATE_2;
  }
  //Khoảng 3: Ít sáng hơn nữa: dimming = 30%
  else if(((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min) >=
      (node_time_mark.Time_Mark_3_hour*60 + node_time_mark.Time_Mark_3_minute))
      &&
      ((node_gmt_plus_7_time.hour*60 + node_gmt_plus_7_time.min) <
      (node_time_mark.Time_Mark_4_hour*60 + node_time_mark.Time_Mark_4_minute)))
  {

      led_state_default = LED_STATE_DEFAULT_3;
      led_dimming_default = LED_DIMMING_DEFAULT_3;
      node_time_state = TIME_STATE_3;
  }
  //Khoảng 4: Trời đã sáng => không cần đèn
  else{
      led_state_default = LED_STATE_DEFAULT_4;
      led_dimming_default = LED_DIMMING_DEFAULT_4;
      node_time_state = TIME_STATE_4;
  }


  /**************************************************************************/
  /*************     Điều khiển LED: trạng thái và dimming     **************/
  /**************************************************************************/
  node_data.led_state = led_state_default;
  node_data.led_dimming = led_dimming_default;
  /* Trời trong khoảng thời gian ban ngày */
  if(node_time_state == TIME_STATE_4){
      static uint32_t temp_bh1750_time = 0;

      //Trời đột ngột tối, để kích hoạt cần đột ngột tối trong khoảng thời gian tương đối
      if(Sensor_value.BH1750 <= BH1750_LIGHT_THRESHOLD){
          if(temp_bh1750_time == 0){
              temp_bh1750_time = node_data.timestamp;
          }
          if(node_data.timestamp - temp_bh1750_time > BH1750_TIME_ON_THRESHOLD){
              //Đã đạt đủ thời gian => Bật đèn maximum
              node_data.led_state = 1;
              node_data.led_dimming = 100;
          }
      }
      else{
          temp_bh1750_time = 0;
      }
  }
  else{
      /* Có chuyển động */
      if(Sensor_value.PIR == 1){
          node_data.led_state = 1;
          node_data.led_dimming = 100;
      }
      else{
          node_data.led_state = led_state_default;
          node_data.led_dimming = led_dimming_default;
      }
  }

  /**************************************************************************/
  /*************   Đưa ra ngoài chân: trạng thái và dimming    **************/
  /**************************************************************************/
  if(node_data.led_state == 0){
      GPIO_PinOutClear(PWM_LED_PORT, PWM_LED_PIN);
  }
  else if (node_data.led_state == 1){
      sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_lut[node_data.led_dimming]);
  }

}

void SysTick_Handler(void)
{
  tick_count++;
}







