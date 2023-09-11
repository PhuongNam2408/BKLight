#include "lora.h"
#include "uart.h"
#include "mqtt.h"
#include <time.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/watchdog.h> 

int global_fd;
int global_fd_flag = 0;

/* Biến quan trọng nhất, quản lý trạng thái của tất cả các đèn */
lora_end_node_t lora_end_node[NUM_END_NODE];

extern volatile uint32_t UART_RxCount;
extern uint8_t UART_Rx_buffer[UART_MAX_NUM_BYTE];

extern volatile int MQTT_Connect_flag;
Lora_Configuration_t global_configuration;
int deviceHandle;



void Watchdog_Init(void)
{
	close(deviceHandle);
	if ((deviceHandle = open("/dev/watchdog", O_RDWR | O_NOCTTY)) < 0){ 
		printf("Error: Couldn't open watchdog device! %d\n", deviceHandle);
		Error_Handler("Couldn't open watchdog device");
	}
	// get timeout info of watchdog (try to set it to 15s before)
	int timeout = 15;
	ioctl(deviceHandle, WDIOC_SETTIMEOUT, &timeout);
	ioctl(deviceHandle, WDIOC_GETTIMEOUT, &timeout);
	printf("The watchdog timeout is %d seconds.\n\n", timeout);
}

void Watchdog_Feed(void)
{
	ioctl(deviceHandle, WDIOC_KEEPALIVE, 0);
}

void Check_Node_Alive(void)
{
	uint32_t now = time(NULL);
	for(int i = 0; i < 5; i++)
	{
		uint32_t delta_time = (now > lora_end_node[i].timestamp) ? \
		(now - lora_end_node[i].timestamp) : (lora_end_node[i].timestamp - now);
		if(delta_time > NODE_TIME_OUT)
		{
			lora_end_node[i].fault == NODE_FAULT_LOST_CONNECTION;
			MQTT_Send_Node_Not_Alive(lora_end_node[i].node_address, NODE_FAULT_LOST_CONNECTION);
		}
		else{
			printf("delta time: %d\n", delta_time);
		}
	}
}

int main()
{
	//Watchdog_Init();
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
	while(1)
	{
		if(MQTT_Connect_flag == 1)
		{
			//Watchdog_Feed();
			Task_UART_Rx();
			Task_UART_Tx();
			MQTT_Task_Receive();
			if(count > 200)
			{
				printf("transmit");
				Check_Node_Alive();
				MQTT_Send_GW_Alive();
				count=0;
			}
		}
		count++;
		delay(10);
	}
	return 0;
}
