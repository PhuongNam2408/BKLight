/*
 * nam_uart.c
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#include "nam_uart.h"
#include "LoRa_E32.h"
#include "nam_rtc.h"
#include "main.h"

// Receive data buffer
uint8_t UART_Rx_buffer[UART_MAX_NUM_BYTE];

// Current position ins buffer
__IO uint32_t UART_RxCount = 0;

uint8_t UART_TxQueue[UART_MAX_NUM_BYTE];
volatile uint8_t UART_tx_index = 0;

/* Các biến sử dụng cho hàm Parse */
static uint16_t source_address;
static read_state_t read_state;
static uint8_t key, length, crc, data_count;
static uint8_t value[LORA_MAX_SIZE_PACKET];

extern Time_Mark_t node_time_mark;

extern End_Node_Data_t node_data;

extern uint8_t Sever_Control;
extern uint32_t sever_control_tick;
extern uint8_t led_state_Sever;
extern uint8_t led_dimming_Sever;

/**************************************************************************//**
 * @brief
 *    USART0 initialization
 *****************************************************************************/
void init_USART0(void)
{

}

/**************************************************************************//**
 * @brief
 *    The USART0 receive interrupt saves incoming characters.
 *****************************************************************************/
void USART0_RX_IRQHandler(void)
{
  // Get the character just received
  UART_Rx_buffer[UART_RxCount++] = USART0->RXDATA;
}



uint8_t CalCRC(uint8_t *data, int length)
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
 *    The USART0 transmit interrupt outputs characters.
 *****************************************************************************/
void UART_Transmit(uint8_t *TxBuffer, uint16_t length)
{
  // Output received characters
  for (int i = 0; i < length; i++)
    USART_Tx(USART0, TxBuffer[i]);
}



void UART_Add_To_TxQueue(uint8_t* data, uint16_t length)
{
  if(UART_tx_index + length + 1 < UART_MAX_NUM_BYTE)
  {
    for (int i=UART_tx_index; i < UART_tx_index + length; i++)
    {
      UART_TxQueue[i] = data[i-UART_tx_index];
    }
    UART_tx_index += length;
  }
  else
  {
    Error_Handler();
  }
}

void LORA_Send_End_Node_Data(End_Node_Data_t node_data_t)
{
  uint8_t node_data_send[100];
  node_data_send[0] = (uint8_t) (GATE_WAY_ADDR >> 8);
  node_data_send[1] = (uint8_t) (GATE_WAY_ADDR & 0xFF);
  node_data_send[2] = (uint8_t) LORA_CHANNEL;
  node_data_send[3] = END_NODE_SYNC1;
  node_data_send[4] = END_NODE_SYNC2;
  node_data_send[5] = (uint8_t) (END_NODE_ADDR >> 8);
  node_data_send[6] = (uint8_t) (END_NODE_ADDR & 0xFF);
  node_data_send[7] = KEY_END_NODE_DATA;
  node_data_send[8] = LENGTH_END_NODE_DATA;

  memcpy(&node_data_send[9], &node_data_t, LENGTH_END_NODE_DATA);
  node_data_send[9+LENGTH_END_NODE_DATA] = CalCRC(&node_data_send[9], LENGTH_END_NODE_DATA);

  UART_Add_To_TxQueue(node_data_send, 10+LENGTH_END_NODE_DATA);
}

void LORA_Send_Synctime(void)
{
  uint8_t synctime_send[100];

  synctime_send[0] = (uint8_t) (GATE_WAY_ADDR >> 8);
  synctime_send[1] = (uint8_t) (GATE_WAY_ADDR & 0xFF);
  synctime_send[2] = (uint8_t) LORA_CHANNEL;
  synctime_send[3] = END_NODE_SYNC1;
  synctime_send[4] = END_NODE_SYNC2;
  synctime_send[5] = (uint8_t) (END_NODE_ADDR >> 8);
  synctime_send[6] = (uint8_t) (END_NODE_ADDR & 0xFF);
  synctime_send[7] = KEY_SYNCTIME;
  synctime_send[8] = 0;

  synctime_send[9+0] = CalCRC(&synctime_send[9], 0);

  UART_Add_To_TxQueue(synctime_send, 10+0);
}

extern uint8_t synctime_flag;
uint32_t timestamp_rcv;
void UART_Parse_Data(uint8_t rx_byte)
{
  switch (read_state)
  {
    case SYNC1:
      if(rx_byte == GATE_WAY_SYNC1)
      {
        read_state = SYNC2;
      }
      break;
    case SYNC2:
      if(rx_byte == GATE_WAY_SYNC2)
      {
        read_state = ADDH;
      }
      else
      {
        read_state = SYNC1;
      }
      break;
    case ADDH:
      source_address = rx_byte << 8;
      read_state = ADDL;
      break;

    case ADDL:
      source_address |= rx_byte;
      read_state = KEY;
      break;

    case KEY:
      key = rx_byte;
      if(LORA_KEY_VALID(key) == 0)
      {
        read_state = SYNC1;
      }
      else
      {
        read_state = LENGTH;
      }
      break;

    case LENGTH:
      length = rx_byte;
      if(length == 0)
      {
        read_state = CRC;
      }
      else if(LORA_LENGTH_VALID(length) == 0)
      {
        read_state = SYNC1;
      }
      else
      {
        data_count = 0;
        read_state = VALUE;
      }
      break;

    case VALUE:
      value[data_count++] = rx_byte;
      if(data_count >= length)
      {
        read_state = CRC;
      }
      break;

    case CRC:
      crc = rx_byte;
      read_state = SYNC1;
      if(crc == CalCRC(value, length))
      {
        switch (key)
        {
        case KEY_SYNCTIME:
          /* Nhận timestamp */
          timestamp_rcv = (value[3] << 24) | (value[2] << 16) | (value[1] << 8) | (value[0]);

          /* Set timestamp */
          RTC_SetTimeFromTicks(timestamp_rcv);
          synctime_flag = 1;
          break;

        case KEY_CONTROL_SETTIME:
          node_time_mark.Time_Mark_1_hour = value[0];
          node_time_mark.Time_Mark_1_minute = value[1];
          node_time_mark.Time_Mark_2_hour = value[2];
          node_time_mark.Time_Mark_2_minute = value[3];
          node_time_mark.Time_Mark_3_hour = value[4];
          node_time_mark.Time_Mark_3_minute = value[5];
          node_time_mark.Time_Mark_4_hour = value[6];
          node_time_mark.Time_Mark_4_minute = value[7];
          break;

        case KEY_CONTROL_ONOFF:
          //Cập nhật trạng thái bị Sever điều khiển
          Sever_Control = 1;
          sever_control_tick = node_data.timestamp;

          led_state_Sever = value[0];
          led_dimming_Sever = node_data.led_dimming;
          break;

        case KEY_CONTROL_DIMMING:
          //Cập nhật trạng thái bị Sever điều khiển
          Sever_Control = 1;
          sever_control_tick = node_data.timestamp;

          led_state_Sever = node_data.led_state;
          led_dimming_Sever = value[0];
          break;

        default:
          break;
        }
      }
      break;
    default:
      break;
  }
}

/**************************************************************************//**
 * @brief
 *    Task UART Transmit
 *****************************************************************************/
void Task_UART_Rx(void)
{
  if(UART_RxCount > 0){
    // Disable receive data valid interrupt
    USART_IntDisable(USART0, USART_IEN_RXDATAV);

    for(int i=0; i < UART_RxCount; i++)
    {
      UART_Parse_Data(UART_Rx_buffer[i]);
    }

    // Reset buffer indices
    UART_RxCount = 0;

    // Enable receive data valid interrupt
    USART_IntEnable(USART0, USART_IEN_RXDATAV);
  }
}

void UART_Transmit_Buffer(void)
{
  if(UART_tx_index > 0){
      UART_Transmit(UART_TxQueue, UART_tx_index);
      UART_tx_index = 0;
  }
}
void Task_UART_Tx(void)
{
  /**************************************************************************/
  /**** Update node_data lên gateway. Theo chu kỳ hoặc theo sự thay đổi *****/
  /**************************************************************************/
  //Chu kỳ
  static uint32_t uart_tx_time = 0;
  if(uart_tx_time == 0){
      uart_tx_time = node_data.timestamp;
  }
  /* Sau Cycle time, data sẽ được đẩy lên gateway */
  if(node_data.timestamp - uart_tx_time > TRANSMIT_NODE_DATA_CYCLE_TIME){
      LORA_Send_End_Node_Data(node_data);
      uart_tx_time = node_data.timestamp;
  }
  //Sự thay dổi giá trị
  static End_Node_Data_t node_data_before = {.timestamp = 0};
  if(node_data_before.timestamp == 0){
      node_data_before = node_data;
  }
  if(node_data_before.led_dimming != node_data.led_dimming ||
      node_data_before.led_state != node_data.led_state)
  {
      LORA_Send_End_Node_Data(node_data);
      node_data_before = node_data;
  }
  UART_Transmit_Buffer();
}













