#ifndef MQTT_H_
#define MQTT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "MQTTAsync.h"
#include <unistd.h>

#if defined(_WRS_KERNEL)
#include <OsWrapper.h>
printf("Toi la WRS KERNEL\n");
fflush(stdout);
#endif

#define ADDRESS		"ssl://xemdoan2408.duckdns.org:1234"
#define CLIENTID	"RaspberryPi"
#define QOS			1
#define TIMEOUT		10000L

#define MQTT_PAYLOAD_MAX_NUM	400


#define MQTT_TOPIC_LED_DATA		"LED_Data"

#define MQTT_TOPIC_CONTROL_ONOFF	"LED_Control/On_off"
#define MQTT_TOPIC_CONTROL_DIMMING	"LED_Control/Dimming"
#define MQTT_TOPIC_CONTROL_TIMER	"LED_Control/Set_Time"

typedef struct 
{
	char topic[100];
	char payload[MQTT_PAYLOAD_MAX_NUM];
}MQTT_Message;

typedef struct 
{
	uint16_t node_addr;
	uint32_t timestamp;
	uint8_t on_off;
	uint8_t dimming;
	uint8_t current_sensor;
}MQTT_LED_Data_t;

typedef struct
{
	uint16_t node_addr;
	uint8_t on_off;
}MQTT_LED_Control_OnOff_t;

typedef struct
{
	uint16_t node_addr;
	uint8_t dimming;
}MQTT_LED_Control_Dimming_t;

typedef struct
{
	uint16_t node_addr;
	uint8_t time;
	uint8_t on_off;
	uint8_t dimming; 
}MQTT_LED_Control_SetTime_t;

void MQTT_Init();
void MQTT_Transmit(uint8_t *topic, uint8_t *payload);
void MQTT_LED_Data_Transmit(MQTT_LED_Data_t LED_Data);
void MQTT_Task_Receive(void);

#endif /* MQTT_H_ */
