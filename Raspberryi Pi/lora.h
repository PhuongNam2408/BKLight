/*
 * LoRa_E32.h
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#ifndef LORA_H_
#define LORA_H_

#include "wiringPi.h"
#include "wiringSerial.h"
#include "lora_data_frame.h"


#include <errno.h>
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <stdint.h>

#define LORA_AUX_PIN	7	
#define LORA_M0_PIN	8
#define LORA_M1_PIN 	9

#define LORA_MAX_SIZE_PACKET 58

#define BROADCAST_ADDRESS 0xFF

#define LORA_BAUD_RATE_CONFIG 9600
#define LORA_BAUD_RATE_NORMAL 115200

typedef struct  {
	uint8_t airDataRate : 3; //bit 0-2
	uint8_t uartBaudRate: 3; //bit 3-5
	uint8_t uartParity:   2; //bit 6-7
}Speed_t;

typedef struct  {
	uint8_t transmissionPower  : 2; //bit 0-1
	uint8_t fec          : 1; //bit 2
	uint8_t wirelessWakeupTime : 3; //bit 3-5
	uint8_t ioDriveMode      : 1; //bit 6
	uint8_t fixedTransmission  : 1; //bit 7
}Option_t;

typedef struct {
	uint8_t HEAD;
	uint8_t ADDH;
	uint8_t ADDL;
	Speed_t SPED;
	uint8_t CHAN;
	Option_t OPTION;
}Lora_Configuration_t;

typedef struct
{
	uint8_t ADDH;
	uint8_t ADDL;
	uint8_t CHAN;
	uint8_t message[];
}FixedMessage_t;

typedef enum
{
	MODE_0_NORMAL     = 0,
	MODE_1_WAKE_UP    = 1,
	MODE_2_POWER_SAVING   = 2,
	MODE_3_SLEEP      = 3,
	MODE_3_PROGRAM    = 3,
	MODE_INIT       = 0xFF
}MODE_TYPE;

typedef enum
{
	WRITE_CFG_PWR_DWN_SAVE    = 0xC0,
	READ_CONFIGURATION    = 0xC1,
	WRITE_CFG_PWR_DWN_LOSE  = 0xC2,
	READ_MODULE_VERSION     = 0xC3,
	WRITE_RESET_MODULE      = 0xC4
}PROGRAM_COMMAND;

typedef enum
{
	MODE_00_8N1 = 0b00,
	MODE_01_8O1 = 0b01,
	MODE_10_8E1 = 0b10,
	MODE_11_8N1 = 0b11
}E32_UART_PARITY;

typedef enum
{
	UART_BPS_1200 = 0b000,
	UART_BPS_2400 = 0b001,
	UART_BPS_4800 = 0b010,
	UART_BPS_9600 = 0b011,
	UART_BPS_19200 = 0b100,
	UART_BPS_38400 = 0b101,
	UART_BPS_57600 = 0b110,
	UART_BPS_115200 = 0b111
}UART_BPS_TYPE;

typedef enum
{
	UART_BPS_RATE_1200 = 1200,
	UART_BPS_RATE_2400 = 2400,
	UART_BPS_RATE_4800 = 4800,
	UART_BPS_RATE_9600 = 9600,
	UART_BPS_RATE_19200 = 19200,
	UART_BPS_RATE_38400 = 38400,
	UART_BPS_RATE_57600 = 57600,
	UART_BPS_RATE_115200 = 115200
}UART_BPS_RATE;

typedef enum
{
	AIR_DATA_RATE_000_03 = 0b000,
	AIR_DATA_RATE_001_12 = 0b001,
	AIR_DATA_RATE_010_24 = 0b010,
	AIR_DATA_RATE_011_48 = 0b011,
	AIR_DATA_RATE_100_96 = 0b100,
	AIR_DATA_RATE_101_192 = 0b101,
	AIR_DATA_RATE_110_192 = 0b110,
	AIR_DATA_RATE_111_192 = 0b111
}AIR_DATA_RATE;

typedef enum
{
	FT_TRANSPARENT_TRANSMISSION = 0b0,
	FT_FIXED_TRANSMISSION = 0b1
}FIDEX_TRANSMISSION;

typedef enum
{
	IO_D_MODE_OPEN_COLLECTOR = 0b0,
	IO_D_MODE_PUSH_PULLS_PULL_UPS = 0b1
}IO_DRIVE_MODE;

typedef enum
{
	WAKE_UP_250 = 0b000,
	WAKE_UP_500 = 0b001,
	WAKE_UP_750 = 0b010,
	WAKE_UP_1000 = 0b011,
	WAKE_UP_1250 = 0b100,
	WAKE_UP_1500 = 0b101,
	WAKE_UP_1750 = 0b110,
	WAKE_UP_2000 = 0b111
}WIRELESS_WAKE_UP_TIME;

typedef enum
{
FEC_0_OFF = 0b0,
FEC_1_ON = 0b1
}FORWARD_ERROR_CORRECTION_SWITCH;

typedef enum
{
	POWER_20 = 0b00,
	POWER_17 = 0b01,
	POWER_14 = 0b10,
	POWER_10 = 0b11
}TRANSMISSION_POWER;


void LoRa_Init(void);
void LoRa_getConfiguration(Lora_Configuration_t *config);
void LoRa_setConfiguration(Lora_Configuration_t config, PROGRAM_COMMAND save_type);
void LoRa_sendFixedMessage(uint8_t ADDH, uint8_t ADDL, uint8_t Channel, uint8_t *message);
void LoRa_sendBroadcastFixedMessage(uint8_t Channel, uint8_t *message);


#endif /* LORA_H_ */
