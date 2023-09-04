#include "lora.h"
#include "uart.h"
#include "mqtt.h"

int global_fd;
int global_fd_flag = 0;

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

	uint8_t test_buffer[30] = "Xin chao, toi la Raspberrypi 0\n";
	int count = 0;
	while(1)
	{
		Task_UART_Rx();
		Task_UART_Tx();
		delay(1000);
	}
	return 0;
}
