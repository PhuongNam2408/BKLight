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

#define MQTT_TOPIC_GATEWAY_ALIVE	"Gateway_Alive"
#define MQTT_TOPIC_NODE_NOT_ALIVE	"Node_Dead"

#define MQTT_TOPIC_FAKE_SYNCTIME	"NODE_Fake_time"

//20 phut
#define NODE_TIME_OUT	(20*60)

#define NODE_FAULT_LOST_CONNECTION	0
#define NODE_FAULT_MIN_CURRENT	1
#define NODE_FAULT_MAX_CURRENT	2
#define NODE_FAULT_NONE	0xFF
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
	uint16_t current_sensor;
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
	uint8_t time1_hour;
	uint8_t time1_minute;
	uint8_t time2_hour;
	uint8_t time2_minute;
	uint8_t time3_hour;
	uint8_t time3_minute;
	uint8_t time4_hour;
	uint8_t time4_minute;
}MQTT_LED_Control_SetTime_t;

void MQTT_Init();
void MQTT_Transmit(uint8_t *topic, uint8_t *payload);
void MQTT_LED_Data_Transmit(MQTT_LED_Data_t LED_Data);
void MQTT_Task_Receive(void);
void Error_Handler(char *name_fail);
void MQTT_Send_GW_Alive(void);
void MQTT_Send_Node_Not_Alive(uint16_t node_addr, uint8_t fault);



#endif /* MQTT_H_ */
