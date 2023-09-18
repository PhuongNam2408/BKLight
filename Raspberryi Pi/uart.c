/*
 * nam_uart.c
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#include "uart.h"
#include "lora.h"
#include <time.h>
#include "aes.h"

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




void LORA_Send_Synctime(uint32_t timestamp, uint8_t fake, uint16_t fake_addr)
{
	/* Phần data không encrypt */
	uint8_t synctime_send[100];
	if(fake == 0)
	{
		synctime_send[0] = (uint8_t) (source_address >> 8);
		synctime_send[1] = (uint8_t) (source_address & 0xFF);
		synctime_send[2] = (uint8_t) LORA_CHANNEL;
	}
	else if (fake == 1)
	{
		synctime_send[0] = (uint8_t) (fake_addr >> 8);
		synctime_send[1] = (uint8_t) (fake_addr & 0xFF);
		synctime_send[2] = (uint8_t) LORA_CHANNEL;
	}

	/* Phần data có encrypt */
	uint8_t data_aes[100];
	data_aes[0] = GATE_WAY_SYNC1;
	data_aes[1] = GATE_WAY_SYNC2;
	data_aes[2] = (uint8_t) (uint8_t) (GATE_WAY_ADDR >> 8);
	data_aes[3] = (uint8_t) (uint8_t) (GATE_WAY_ADDR & 0xFF);
	data_aes[4] = KEY_SYNCTIME;
	data_aes[5] = LENGTH_SYNCTIME;
	memcpy(&data_aes[6], &timestamp, LENGTH_SYNCTIME);
	data_aes[6+LENGTH_SYNCTIME] = CalCRC(&data_aes[6], LENGTH_SYNCTIME);

	uint16_t out_len = AES_encode(data_aes, &synctime_send[3], 7+LENGTH_SYNCTIME);

	UART_Add_To_TxQueue(synctime_send, 3+out_len);
}

void LORA_Send_Control_OnOff(MQTT_LED_Control_OnOff_t on_off_struct)
{
	/* Phần data không encrypt */
	uint8_t on_off_send[100];
	on_off_send[0] = (uint8_t) (on_off_struct.node_addr >> 8);
	on_off_send[1] = (uint8_t) (on_off_struct.node_addr & 0xFF);
	on_off_send[2] = (uint8_t) LORA_CHANNEL;

	/* Phần data có encrypt */
	uint8_t data_aes[100];
	data_aes[0] = GATE_WAY_SYNC1;
	data_aes[1] = GATE_WAY_SYNC2;
	data_aes[2] = (uint8_t) (uint8_t) (GATE_WAY_ADDR >> 8);
	data_aes[3] = (uint8_t) (uint8_t) (GATE_WAY_ADDR & 0xFF);
	data_aes[4] = KEY_CONTROL_ONOFF;
	data_aes[5] = LENGTH_CONTROL_ONOFF;
	memcpy(&data_aes[6], &on_off_struct.on_off, LENGTH_CONTROL_ONOFF);
	data_aes[6+LENGTH_CONTROL_ONOFF] = CalCRC(&data_aes[6], LENGTH_CONTROL_ONOFF);

	uint16_t out_len = AES_encode(data_aes, &on_off_send[3], 7+LENGTH_CONTROL_ONOFF);

	UART_Add_To_TxQueue(on_off_send, 3+out_len);
}

void LORA_Send_Control_Dimming(MQTT_LED_Control_Dimming_t dimming_struct)
{
	/* Phần data không encrypt */
	uint8_t dimming_send[100];
	dimming_send[0] = (uint8_t) (dimming_struct.node_addr >> 8);
	dimming_send[1] = (uint8_t) (dimming_struct.node_addr & 0xFF);
	dimming_send[2] = (uint8_t) LORA_CHANNEL;

	/* Phần data có encrypt */
	uint8_t data_aes[100];
	data_aes[0] = GATE_WAY_SYNC1;
	data_aes[1] = GATE_WAY_SYNC2;
	data_aes[2] = (uint8_t) (uint8_t) (GATE_WAY_ADDR >> 8);
	data_aes[3] = (uint8_t) (uint8_t) (GATE_WAY_ADDR & 0xFF);
	data_aes[4] = KEY_CONTROL_DIMMING;
	data_aes[5] = LENGTH_CONTROL_DIMMING;
	memcpy(&data_aes[6], &dimming_struct.dimming, LENGTH_CONTROL_DIMMING);
	data_aes[6+LENGTH_CONTROL_DIMMING] = CalCRC(&data_aes[6], LENGTH_CONTROL_DIMMING);

	uint16_t out_len = AES_encode(data_aes, &dimming_send[3], 7+LENGTH_CONTROL_DIMMING);

	UART_Add_To_TxQueue(dimming_send, 3+out_len);
}

void LORA_Send_Control_Set_Time(MQTT_LED_Control_SetTime_t settime_struct)
{
	/* Phần data không encrypt */
	uint8_t settime_send[100];
	settime_send[0] = (uint8_t) (settime_struct.node_addr >> 8);
	settime_send[1] = (uint8_t) (settime_struct.node_addr & 0xFF);
	settime_send[2] = (uint8_t) LORA_CHANNEL;

	/* Phần data có encrypt */
	uint8_t data_aes[100];
	data_aes[0] = GATE_WAY_SYNC1;
	data_aes[1] = GATE_WAY_SYNC2;
	data_aes[2] = (uint8_t) (uint8_t) (GATE_WAY_ADDR >> 8);
	data_aes[3] = (uint8_t) (uint8_t) (GATE_WAY_ADDR & 0xFF);
	data_aes[4] = KEY_CONTROL_SETTIME;
	data_aes[5] = LENGTH_CONTROL_SETTIME;
	memcpy(&data_aes[6], &settime_struct.time1_hour, LENGTH_CONTROL_SETTIME);
	data_aes[6+LENGTH_CONTROL_SETTIME] = CalCRC(&data_aes[6], LENGTH_CONTROL_SETTIME);

	uint16_t out_len = AES_encode(data_aes, &settime_send[3], 7+LENGTH_CONTROL_SETTIME);

	UART_Add_To_TxQueue(settime_send, 3+out_len);
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
			//printf("addh\n");
			fflush(stdout);
			break;

		case ADDL:
			source_address |= rx_byte;
			read_state = KEY;
			//printf("addl\n");
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
			//printf("key\n");
			fflush(stdout);
			break;

		case LENGTH:
			length = rx_byte;
			//printf("length\n");
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
			//printf("value %d\n", data_count);
			fflush(stdout);
			if(data_count >= length)
			{
				read_state = CRC;
			}
			break;

		case CRC:
			//printf("crc\n");
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
			
			//printf("node %d\n", source_address);
			//fflush(stdout);
								lora_end_node[i].timestamp = (value[3] << 24) | (value[2] << 16) | (value[1] << 8) | (value[0]);
			//printf("lora_end_node[i].timestamp %d\n",lora_end_node[i].timestamp );
								lora_end_node[i].led_on_off = value[4];
			//printf("lora_end_node[i].led_on_off %d\n",lora_end_node[i].led_on_off );
								lora_end_node[i].led_dimming = value[5];
			//printf("lora_end_node[i].led_dimming %d\n",lora_end_node[i].led_dimming );
								lora_end_node[i].led_current = (value[7] << 8) | value[6];
			//printf("lora_end_node[i].led_current %d\n",lora_end_node[i].led_current );
			//fflush(stdout);
								
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
					LORA_Send_Synctime((uint32_t)time(NULL), 0, 0);
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
		// Disable receive data valid interrupt
		piLock(0);
		/* Giải mã tín hiệu nhận được */
		uint8_t parse_buffer[100];
		AES_decode(UART_Rx_buffer, parse_buffer, UART_RxCount);
		
		for(int i=0; i < UART_RxCount; i++)
		{
			UART_Parse_Data(parse_buffer[i]);
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
		/* Tìm kiếm header */
		int header_2nd = 0;
		for(int i=3; i < UART_tx_index-2; i++)
		{
			if(LORA_ADDRESS_VALID(UART_TxQueue[i]<<8 | UART_TxQueue[i+1]) &&
			UART_TxQueue[i+2] == LORA_CHANNEL)
			
			{
				header_2nd = i;
				break;
			}
		}

		if(header_2nd == 0)
		{
			for(int i=0; i < UART_tx_index; i++)
			{
				serialPutchar(global_fd, UART_TxQueue[i]);
			}
			UART_tx_index = 0;
			memset(UART_TxQueue, 0, UART_MAX_NUM_BYTE);
		}
		else
		{
			printf("header_address: %d %d %d\n", header_2nd, UART_TxQueue[1], UART_TxQueue[20]);
			//chỉ truyền duy nhất 1 bản tin
			for(int i=0; i < header_2nd; i++)
			{
				serialPutchar(global_fd, UART_TxQueue[i]);
			}

			//Đẩy dữ liệu của buffer lên
			UART_tx_index -= header_2nd;
			for(int i=0; i < UART_tx_index; i++)
			{
				UART_TxQueue[i] = UART_TxQueue[header_2nd+i];
			}
		}
		
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
