/*
 * LoRa_E32.c
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#include "LoRa_E32.h"
#include "lora_data_frame.h"

void LoRa_E32_Init()
{
  /* Init Pins:
   *
   * Tx -> D4
   * Rx -> D5
   * M0 -> C2
   * M1 -> C3
   *
   *  */

    // Enable clock to GPIO and USART0
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_USART0, true);

    // GPIO Mode set
    GPIO_PinModeSet(LORA_TX_PORT, LORA_TX_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(LORA_RX_PORT, LORA_RX_PIN, gpioModeInput, 0);
    GPIO_PinModeSet(LORA_M0_PORT, LORA_M0_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(LORA_M1_PORT, LORA_M1_PIN, gpioModePushPull, 0);

    // Default asynchronous initializer (115.2 Kbps, 8N1, no flow control)
    USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;

    // Route USART0 TX and RX to the board controller TX and RX pins
    GPIO->USARTROUTE[0].TXROUTE = (LORA_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
        | (LORA_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
    GPIO->USARTROUTE[0].RXROUTE = (LORA_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
        | (LORA_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);

    // Enable RX and TX signals now that they have been routed
    GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;

    init.baudrate = LORA_BAUD_RATE_NORMAL;

    // Configure and enable USART0
    USART_InitAsync(USART0, &init);

    // Enable NVIC USART sources
    NVIC_ClearPendingIRQ(USART0_RX_IRQn);
    NVIC_EnableIRQ(USART0_RX_IRQn);

    USART_IntEnable(USART0, USART_IEN_RXDATAV);
}

void LoRa_setMode(MODE_TYPE mode) {

  Delay_ms(40);
  switch (mode)
  {
    case MODE_0_NORMAL:
      // Mode 0 | normal operation
      GPIO_PinOutClear(LORA_M0_PORT, LORA_M0_PIN);
      GPIO_PinOutClear(LORA_M1_PORT, LORA_M1_PIN);
    break;
    case MODE_1_WAKE_UP:
      GPIO_PinOutSet(LORA_M0_PORT, LORA_M0_PIN);
      GPIO_PinOutClear(LORA_M1_PORT, LORA_M1_PIN);
    break;
    case MODE_2_POWER_SAVING:
      GPIO_PinOutClear(LORA_M0_PORT, LORA_M0_PIN);
      GPIO_PinOutSet(LORA_M1_PORT, LORA_M1_PIN);
    break;
    case MODE_3_PROGRAM:
      // Mode 3 | Setting operation
      GPIO_PinOutSet(LORA_M0_PORT, LORA_M0_PIN);
      GPIO_PinOutSet(LORA_M1_PORT, LORA_M1_PIN);
    break;
    default:
      break;
  }
  // data sheet says 2ms later control is returned, let's give just a bit more time
  // these modules can take time to activate pins
  Delay_ms(40);
}

void LoRa_sendStruct(uint8_t *send_buffer, uint16_t size)
{
  if (size > LORA_MAX_SIZE_PACKET + 2){
      Error_Handler();
  }
  UART_Transmit(send_buffer, size);
}

void LoRa_readStruct(uint8_t *read_buffer, uint16_t size)
{
  for(int i=0; i < size; i++){
      read_buffer[i] = USART_Rx(USART0);
  }
}


void LoRa_getConfiguration(Lora_Configuration_t *config)
{
  USART_IntDisable(USART0, USART_IEN_RXDATAV);
  LoRa_setMode(MODE_3_PROGRAM);

  uint8_t command_buff[3] = {READ_CONFIGURATION, READ_CONFIGURATION, READ_CONFIGURATION};

  /* Đổi baudrate */
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  init.baudrate = LORA_BAUD_RATE_CONFIG;
  // Configure and enable USART0
  USART_InitAsync(USART0, &init);

  LoRa_sendStruct(command_buff, 3);
  LoRa_readStruct((uint8_t *)config, sizeof(Lora_Configuration_t));

  init.baudrate = LORA_BAUD_RATE_NORMAL;
  // Configure and enable USART0
  USART_InitAsync(USART0, &init);

  USART_IntEnable(USART0, USART_IEN_RXDATAV);
  LoRa_setMode(MODE_0_NORMAL);
}


void LoRa_setConfiguration(Lora_Configuration_t config, PROGRAM_COMMAND save_type)
{
  USART_IntDisable(USART0, USART_IEN_RXDATAV);

  LoRa_setMode(MODE_3_PROGRAM);

  /* Đổi baudrate */
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  init.baudrate = LORA_BAUD_RATE_CONFIG;
  // Configure and enable USART0
  USART_InitAsync(USART0, &init);

  switch(save_type)
  {
    case WRITE_CFG_PWR_DWN_SAVE:
    case WRITE_CFG_PWR_DWN_LOSE:
    {
      config.HEAD = save_type;
      LoRa_sendStruct((uint8_t *)&config, sizeof(Lora_Configuration_t));
      LoRa_readStruct((uint8_t *)&config, sizeof(Lora_Configuration_t));
    }
      break;
    case READ_CONFIGURATION:
    case READ_MODULE_VERSION:
    case WRITE_RESET_MODULE:
      Error_Handler();
  }

  init.baudrate = LORA_BAUD_RATE_NORMAL;
  // Configure and enable USART0
  USART_InitAsync(USART0, &init);

  USART_IntEnable(USART0, USART_IEN_RXDATAV);
  LoRa_setMode(MODE_0_NORMAL);
}


void LoRa_sendFixedMessage(uint8_t ADDH, uint8_t ADDL, uint8_t Channel, uint8_t *message)
{
  uint16_t size = strlen((char *)message);
  FixedMessage_t *fixed_message = (FixedMessage_t *) malloc(sizeof(FixedMessage_t) + 4*size);
  fixed_message->ADDH = ADDH;
  fixed_message->ADDL = ADDL;
  fixed_message->CHAN = Channel;

  memcpy(fixed_message->message, message, size);

  UART_Add_To_TxQueue((uint8_t *)fixed_message, size+3);
  free(fixed_message);
}


void LoRa_sendBroadcastFixedMessage(uint8_t Channel, uint8_t *message)
{
  LoRa_sendFixedMessage(BROADCAST_ADDRESS, BROADCAST_ADDRESS, Channel, message);
}


/* Mã hóa AES
#define AES_KEY    0x3A5C742E

unsigned long LoRa_encrypt(unsigned long data)
{

}
unsigned long LoRa_decrypt(unsigned long data)
{

}
*/



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  while (1)
  {
      GPIO_PinOutToggle(gpioPortA, 7);
      Delay_ms(200);
  }
  /* USER CODE END Error_Handler_Debug */
}








