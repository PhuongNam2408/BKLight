#include "lora.h"
#include "uart.h"
#include "mqtt.h"
#include <time.h>

int global_fd;
int global_fd_flag = 0;

/* Biến quan trọng nhất, quản lý trạng thái của tất cả các đèn */
lora_end_node_t lora_end_node[NUM_END_NODE];

extern volatile uint32_t UART_RxCount;
extern uint8_t UART_Rx_buffer[UART_MAX_NUM_BYTE];

Lora_Configuration_t global_configuration;

int main()
{
	LoRa_Init();

	printf("----------------------------------------\n");

	printf(("HEAD BIN: 0x%x\n"), global_configuration.HEAD); 
	printf("\n");
	printf("AddH HEX: 0x%x\n", global_configuration.ADDH);  
	printf("AddL HEX: 0x%x\n", global_configuration.ADDL); 
	printf("Chan DEC: %d\n", global_configuration.CHAN);  
	printf("\n");
	printf("Speed HEX: 0x%x\n", global_configuration.SPED);
	printf("Option HEX 0x%x\n", global_configuration.OPTION);
	printf("----------------------------------------\n");
	fflush(stdout);

	MQTT_Init();

	int count = 0;

	MQTT_LED_Data_t hello;
	hello.node_addr = 2;
	hello.timestamp = (uint32_t) time(NULL);
	hello.on_off = 0x4;
	hello.dimming = 0x3;
	hello.current_sensor = 0x42;

	while(1)
	{
		Task_UART_Rx();
		Task_UART_Tx();
		MQTT_Task_Receive();
		if(count > 1000)
		{
			MQTT_LED_Data_Transmit(hello);
			hello.timestamp = (uint32_t) time(NULL);
			count=0;
		}
		count++;
		delay(10);
	}
	return 0;
}
