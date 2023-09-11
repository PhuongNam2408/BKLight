/*
 * nam_uart.c
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#include "uart.h"
#include "lora.h"
#include <time.h>

// Receive data buffer
uint8_t UART_Rx_buffer[UART_MAX_NUM_BYTE];

// Current position ins buffer
volatile uint32_t UART_RxCount = 0;

uint8_t UART_TxQueue[UART_MAX_NUM_BYTE];
volatile uint8_t UART_tx_index = 0;

extern int global_fd;

/* Flag sử dụng để reset số lần đọc file AMA0 */
extern int global_fd_flag;

extern lora_end_node_t lora_end_node[];

/* Các biến sử dụng cho hàm Parse */
static uint16_t source_address;
static read_state_t read_state;
static uint8_t key, length, crc, data_count;
static uint8_t value[LORA_MAX_SIZE_PACKET];

/**************************************************************************//**
 * @brief
 *    The USART0 receive interrupt saves incoming characters.
 *****************************************************************************/
PI_THREAD (UART_Rx_Thread)
{
	while(1)
	{
		if(digitalRead(16) == 0)
		{
			piLock(0);
			int rx_thread_count = 0;
			printf("start thread %d", UART_RxCount);
			while(serialDataAvail(global_fd) == 0);
			loop: while(serialDataAvail(global_fd))
			{
				UART_Rx_buffer[UART_RxCount++] = serialGetchar(global_fd);
			}
			rx_thread_count++;
			if(rx_thread_count < 1000)
			{
				goto loop;
			}
			printf("end thread %d", UART_RxCount);
			global_fd_flag = 1;
			piUnlock(0);
		}
	}
}


/**************************************************************************//**
 * @brief
 *    USART0 initialization
 *****************************************************************************/
void UART_Init(void)
{
	piThreadCreate(UART_Rx_Thread);
	global_fd = serialOpen("/dev/ttyAMA0", LORA_BAUD_RATE_NORMAL);
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
	Error_Handler("UART_Add_To_TxQueue");
  }
}




static void LORA_Send_Synctime(void)
{
	uint32_t time_now = (uint32_t) time(NULL);

	uint8_t synctime_send[100];
	synctime_send[0] = (uint8_t) (source_address >> 8);
	synctime_send[1] = (uint8_t) (source_address & 0xFF);
	synctime_send[2] = (uint8_t) LORA_CHANNEL;
	synctime_send[3] = GATE_WAY_SYNC1;
	synctime_send[4] = GATE_WAY_SYNC2;
	synctime_send[5] = (uint8_t) (GATE_WAY_ADDR >> 8);
	synctime_send[6] = (uint8_t) (GATE_WAY_ADDR & 0xFF);
	synctime_send[7] = KEY_SYNCTIME;
	synctime_send[8] = LENGTH_SYNCTIME;

	memcpy(&synctime_send[9], &time_now, LENGTH_SYNCTIME);
	synctime_send[9+LENGTH_SYNCTIME] = CalCRC(&synctime_send[9], LENGTH_SYNCTIME);

	UART_Add_To_TxQueue(synctime_send, 10+LENGTH_SYNCTIME);
}

void LORA_Send_Control_OnOff(MQTT_LED_Control_OnOff_t on_off_struct)
{
	uint8_t on_off_send[100];
	on_off_send[0] = (uint8_t) (on_off_struct.node_addr >> 8);
	on_off_send[1] = (uint8_t) (on_off_struct.node_addr & 0xFF);
	on_off_send[2] = (uint8_t) LORA_CHANNEL;
	on_off_send[3] = GATE_WAY_SYNC1;
	on_off_send[4] = GATE_WAY_SYNC2;
	on_off_send[5] = (uint8_t) (GATE_WAY_ADDR >> 8);
	on_off_send[6] = (uint8_t) (GATE_WAY_ADDR & 0xFF);
	on_off_send[7] = KEY_CONTROL_ONOFF ;
	on_off_send[8] = LENGTH_CONTROL_ONOFF;

	memcpy(&on_off_send[9], &on_off_struct.on_off, LENGTH_CONTROL_ONOFF);
	on_off_send[9+LENGTH_CONTROL_ONOFF] = CalCRC(&on_off_send[9], LENGTH_CONTROL_ONOFF);

	UART_Add_To_TxQueue(on_off_send, 10+LENGTH_CONTROL_ONOFF);
}

void LORA_Send_Control_Dimming(MQTT_LED_Control_Dimming_t dimming_struct)
{
	uint8_t dimming_send[100];
	dimming_send[0] = (uint8_t) (dimming_struct.node_addr >> 8);
	dimming_send[1] = (uint8_t) (dimming_struct.node_addr & 0xFF);
	dimming_send[2] = (uint8_t) LORA_CHANNEL;
	dimming_send[3] = GATE_WAY_SYNC1;
	dimming_send[4] = GATE_WAY_SYNC2;
	dimming_send[5] = (uint8_t) (GATE_WAY_ADDR >> 8);
	dimming_send[6] = (uint8_t) (GATE_WAY_ADDR & 0xFF);
	dimming_send[7] = KEY_CONTROL_DIMMING ;
	dimming_send[8] = LENGTH_CONTROL_DIMMING;

	memcpy(&dimming_send[9], &dimming_struct.dimming, LENGTH_CONTROL_DIMMING);
	dimming_send[9+LENGTH_CONTROL_DIMMING] = CalCRC(&dimming_send[9], LENGTH_CONTROL_DIMMING);

	UART_Add_To_TxQueue(dimming_send, 10+LENGTH_CONTROL_DIMMING);
}

void LORA_Send_Control_Set_Time(MQTT_LED_Control_SetTime_t settime_struct)
{
	uint8_t settime_send[100];
	settime_send[0] = (uint8_t) (settime_struct.node_addr >> 8);
	settime_send[1] = (uint8_t) (settime_struct.node_addr & 0xFF);
	settime_send[2] = (uint8_t) LORA_CHANNEL;
	settime_send[3] = GATE_WAY_SYNC1;
	settime_send[4] = GATE_WAY_SYNC2;
	settime_send[5] = (uint8_t) (GATE_WAY_ADDR >> 8);
	settime_send[6] = (uint8_t) (GATE_WAY_ADDR & 0xFF);
	settime_send[7] = KEY_CONTROL_SETTIME;
	settime_send[8] = LENGTH_CONTROL_SETTIME;

	memcpy(&settime_send[9], &settime_struct.time1_hour, LENGTH_CONTROL_SETTIME);
	settime_send[9+LENGTH_CONTROL_SETTIME] = CalCRC(&settime_send[9], LENGTH_CONTROL_SETTIME);

	UART_Add_To_TxQueue(settime_send, 10+LENGTH_CONTROL_SETTIME);
}

void UART_Parse_Data(uint8_t rx_byte)
{
	switch (read_state)
	{
		case SYNC1:
			if(rx_byte == END_NODE_SYNC1)
			{
				read_state = SYNC2;
			}
			break;
		case SYNC2:
			if(rx_byte == END_NODE_SYNC2)
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
			printf("addh\n");
			fflush(stdout);
			break;

		case ADDL:
			source_address |= rx_byte;
			read_state = KEY;
			printf("addl\n");
			printf("addr: %d\n", source_address);
			fflush(stdout);
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
			printf("key\n");
			fflush(stdout);
			break;

		case LENGTH:
			length = rx_byte;
			printf("length\n");
			fflush(stdout);
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
			printf("value %d\n", data_count);
			fflush(stdout);
			if(data_count >= length)
			{
				read_state = CRC;
			}
			break;

		case CRC:
			printf("crc\n");
			fflush(stdout);
			crc = rx_byte;
			read_state = SYNC1;
			if(crc == CalCRC(value, length))
			{
				switch (key)
				{
				case KEY_END_NODE_DATA:
					if(length == LENGTH_END_NODE_DATA)
					{
						for(int i = 0; i < NUM_END_NODE; i++)
						{
							if(lora_end_node[i].node_address == source_address)
							{
								/* Cho node sống lại */
								if(lora_end_node[i].fault == NODE_FAULT_LOST_CONNECTION)
								{
									lora_end_node[i].fault = NODE_FAULT_NONE;
								}
			
			printf("node %d\n", source_address);
			fflush(stdout);
								lora_end_node[i].timestamp = (value[3] << 24) | (value[2] << 16) | (value[1] << 8) | (value[0]);
			printf("lora_end_node[i].timestamp %d\n",lora_end_node[i].timestamp );
								lora_end_node[i].led_on_off = value[4];
			printf("lora_end_node[i].led_on_off %d\n",lora_end_node[i].led_on_off );
								lora_end_node[i].led_dimming = value[5];
			printf("lora_end_node[i].led_dimming %d\n",lora_end_node[i].led_dimming );
								lora_end_node[i].led_current = (value[7] << 8) | value[6];
			printf("lora_end_node[i].led_current %d\n",lora_end_node[i].led_current );
			fflush(stdout);
								
								//Send_MQTT
								MQTT_LED_Data_t LED_Data;
								LED_Data.node_addr = lora_end_node[i].node_address;
								LED_Data.timestamp = lora_end_node[i].timestamp;
								LED_Data.on_off = lora_end_node[i].led_on_off;
								LED_Data.dimming = lora_end_node[i].led_dimming;
								LED_Data.current_sensor = lora_end_node[i].led_current;

								MQTT_LED_Data_Transmit(LED_Data);
							}
						}
					}
					break;
				case KEY_CURRENT_WARNING:
					if(length == LENGTH_CURRENT_WARNING)
					{
						for(int i = 0; i < NUM_END_NODE; i++)
						{
							if(lora_end_node[i].node_address == source_address)
							{
								lora_end_node[i].timestamp = (value[3] << 24) | (value[2] << 16) | (value[1] << 8) | (value[0]);
								lora_end_node[i].fault = value[4];
								if(lora_end_node[i].fault == NODE_FAULT_MIN_CURRENT)
								{
									MQTT_Send_Node_Not_Alive(lora_end_node[i].node_address, NODE_FAULT_MIN_CURRENT);
								}
								else if(lora_end_node[i].fault == NODE_FAULT_MAX_CURRENT)
								{
									MQTT_Send_Node_Not_Alive(lora_end_node[i].node_address, NODE_FAULT_MAX_CURRENT);
								}
								printf("node %d\n", source_address);
								printf("lora_end_node[i].timestamp %d\n",lora_end_node[i].timestamp);
								printf("lora_end_node[i].fault %d\n",lora_end_node[i].fault);
							}
						}
					}
					break;
				case KEY_SYNCTIME:
					LORA_Send_Synctime();
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



uint8_t CalCRC(uint8_t *data, int length)
{
	short csum = 0;
	for (size_t i = 0; i < length; i++)
	{
		csum += (short)data[i];
	}
	csum = 255 - (csum % 255);
	return (uint8_t)csum;
}


/**************************************************************************//**
 * @brief
 *    Task UART Transmit
 *****************************************************************************/
void Task_UART_Rx(void)
{
	if(UART_RxCount > 0){

		for(int i=0; i < UART_RxCount; i++)
		{
			UART_Parse_Data(UART_Rx_buffer[i]);
		}

		// Reset buffer indices
		UART_RxCount = 0;

		// Enable receive data valid interrupt
		piUnlock(0);
	}
}

void Task_UART_Tx(void)
{
	piLock(0);
	if(UART_tx_index > 0)
	{
		for(int i=0; i < UART_tx_index; i++)
		{
			serialPutchar(global_fd, UART_TxQueue[i]);
		}
		UART_tx_index = 0;
		global_fd_flag = 1;
  	}
	
	if(global_fd_flag != 0)
	{
		/* Reset Serial File */
		serialClose(global_fd); 
		global_fd = serialOpen("/dev/ttyAMA0", LORA_BAUD_RATE_NORMAL);
		global_fd_flag = 0;
	}
	piUnlock(0);
}
