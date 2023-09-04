/*
 * nam_uart.h
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */


#include "string.h"
#include "stdint.h"
#include "mqtt.h"

// Size of the buffer for received data
#define UART_MAX_NUM_BYTE 200

#ifndef UART_H_
#define UART_H_

void UART_Init(void);
void Task_UART_Tx(void);
void Task_UART_Rx(void);
void UART_Add_To_TxQueue(uint8_t* data, uint16_t length);
uint8_t CalCRC(uint8_t *data, int length);
void LORA_Send_Control_OnOff(MQTT_LED_Control_OnOff_t on_off_struct);
void LORA_Send_Control_Dimming(MQTT_LED_Control_Dimming_t dimming_struct);
void LORA_Send_Control_Set_Time(MQTT_LED_Control_SetTime_t settime_struct);

#endif /* UART_H_ */
