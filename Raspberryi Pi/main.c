#include "lora.h"
#include "uart.h"
#include "mqtt.h"
#include <time.h>
#include <sys/ioctl.h>
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
	Watchdog_Init();

	int count = 0;

	MQTT_LED_Data_t hello;
	hello.node_addr = 2;
	hello.timestamp = (uint32_t) time(NULL);
	hello.on_off = 0x4;
	hello.dimming = 0x3;
	hello.current_sensor = 0x42;

	while(1)
	{
		if(MQTT_Connect_flag == 1)
		{
			Watchdog_Feed();
			Task_UART_Rx();
			Task_UART_Tx();
			MQTT_Task_Receive();
			if(count > 1000)
			{
				MQTT_LED_Data_Transmit(hello);
				hello.timestamp = (uint32_t) time(NULL);
				Watchdog_Init();
				count=0;
			}
		}
		count++;
		delay(10);
	}
	return 0;
}
