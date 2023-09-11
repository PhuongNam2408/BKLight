/*
 * nam_uart.h
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#include "em_gpio.h"
#include "em_usart.h"
#include "string.h"
#include "em_cmu.h"
#include "lora_data_frame.h"

// Size of the buffer for received data
#define UART_MAX_NUM_BYTE 200

#ifndef NAM_DRIVER_NAM_UART_H_
#define NAM_DRIVER_NAM_UART_H_

void UART_Transmit(uint8_t *TxBuffer, uint16_t length);
void Task_UART_Tx(void);
void Task_UART_Rx(void);
void init_USART0(void);
void UART_Add_To_TxQueue(uint8_t* data, uint16_t length);
uint8_t CalCRC(uint8_t *data, int length);
void LORA_Send_End_Node_Data(End_Node_Data_t node_data_t);
void LORA_Send_Synctime(void);

#endif /* NAM_DRIVER_NAM_UART_H_ */
