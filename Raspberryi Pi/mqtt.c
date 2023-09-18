#include "mqtt.h"
#include "uart.h"
#include "lora.h"
#include <time.h>

#define TOPIC	"test_topic"
#define PAYLOAD	"Hello I'm Raspberry Pi 4B!"

/* MQTT Handler */
static MQTTAsync client_handler;

volatile uint16_t MQTT_topic_tx_index = 0;

void Error_Handler(char *name_fail);

volatile int MQTT_Connect_flag = 0;
volatile int reconnect_var = 0;

volatile uint16_t MQTT_Rx_Count = 0;
MQTT_Message MQTT_Rx_Buffer[200];

extern lora_end_node_t lora_end_node[];


/* STATIC FUNCTION */
static int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message);
static void connlost(void *context, char *cause);
static void onSend(void* context, MQTTAsync_successData* response);
static void onSubscribe(void* context, MQTTAsync_successData* response);
static void onSubscribeFailure(void* context, MQTTAsync_failureData* response);
static void onConnect(void* context, MQTTAsync_successData* response);
static void onConnectFailure(void* context, MQTTAsync_failureData* response);
void onSendFailure(void* context, MQTTAsync_failureData* response);

static int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message)
{
	if(strstr(topicName, "LED_Control") != NULL || strstr(topicName, MQTT_TOPIC_FAKE_SYNCTIME) != NULL)
	{
		memcpy(MQTT_Rx_Buffer[MQTT_Rx_Count].topic, (char *)topicName, topicLen);
		memcpy(MQTT_Rx_Buffer[MQTT_Rx_Count].payload, (char *)message->payload, message->payloadlen);
		MQTT_Rx_Count++;
		printf("\n%s: %d\n", topicName, MQTT_Rx_Count);
	}

	printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
	return 1;
}

static void connlost(void *context, char *cause)
{
	MQTTAsync client;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	printf("\nConnection lost\n");
	if (cause)
		printf("     cause: %s\n", cause);
	
	if ((rc = MQTTAsync_create(&client_handler, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to create client object, return code %d\n", rc);
		Error_Handler("MQTTAsync_create");
	}
	
	printf("Reconnecting\n");
	conn_opts.keepAliveInterval = 60;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	MQTTAsync_SSLOptions ssl = MQTTAsync_SSLOptions_initializer;
	ssl.trustStore = "/home/pi/Desktop/BKLight/ca.crt";
	ssl.sslVersion = MQTT_SSL_VERSION_TLS_1_2;
	conn_opts.ssl = &ssl;
	MQTT_Connect_flag = 0;
	reconnect_var = 1;
	if ((rc = MQTTAsync_connect(client_handler, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
	}
}	


static void onSend(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	//printf("Message with token value %d delivery confirmed\n", response->token);
	
	if(reconnect_var == 1)
	{
		if ((rc = MQTTAsync_setCallbacks(client_handler, NULL, connlost, messageArrived, NULL)) != MQTTASYNC_SUCCESS)
		{
			printf("Failed to set callback, return code %d\n", rc);
		}
		reconnect_var = 0;
	}
}

static void onSubscribe(void* context, MQTTAsync_successData* response)
{
	printf("Subscribe succeeded\n");
}

static void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Subscribe failed, rc %d\n", response->code);
	Error_Handler("onubscribeFailure");
}

static void onConnect(void* context, MQTTAsync_successData* response)
{
	MQTT_Connect_flag = 1;
	int rc;
	MQTTAsync client = (MQTTAsync)context;
	printf("Get in onConnect\n");
	MQTTAsync_responseOptions resp_opts = MQTTAsync_responseOptions_initializer;
	
	MQTT_Transmit(TOPIC, PAYLOAD);
	MQTTAsync_reconnect(client_handler);
	printf("Subscribing to topic %s and %s\nfor client %s using QoS%d\n\n", "LED_Control/#",MQTT_TOPIC_FAKE_SYNCTIME, CLIENTID, QOS);
	resp_opts.onSuccess = onSubscribe;
	resp_opts.onFailure = onSubscribeFailure;
	resp_opts.context = client_handler;
	if ((rc = MQTTAsync_subscribe(client_handler, "LED_Control/#", QOS, &resp_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start subscribe, return code %d\n", rc);
	}
	if ((rc = MQTTAsync_subscribe(client_handler, MQTT_TOPIC_FAKE_SYNCTIME, QOS, &resp_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start subscribe, return code %d\n", rc);
	}
}

static void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Connect failed, rc %d\n", response ? response->code : 0);
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	if ((rc = MQTTAsync_create(&client_handler, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to create client object, return code %d\n", rc);
		Error_Handler("MQTTAsync_create");
	}
	
	printf("Reconnecting\n");
	conn_opts.keepAliveInterval = 60;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	MQTTAsync_SSLOptions ssl = MQTTAsync_SSLOptions_initializer;
	ssl.trustStore = "/home/pi/Desktop/BKLight/ca.crt";
	ssl.sslVersion = MQTT_SSL_VERSION_TLS_1_2;
	conn_opts.ssl = &ssl;
	MQTT_Connect_flag = 0;
	reconnect_var = 1;
	if ((rc = MQTTAsync_connect(client_handler, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
	}
}

void onSendFailure(void* context, MQTTAsync_failureData* response)
{
	Error_Handler("onSendFailure");
}

void MQTT_Init()
{
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	rc = MQTTAsync_disconnect(client_handler, &disc_opts);


	if ((rc = MQTTAsync_create(&client_handler, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to create client object, return code %d\n", rc);
		Error_Handler("MQTTAsync_create");
	}
	if ((rc = MQTTAsync_setCallbacks(client_handler, NULL, connlost, messageArrived, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to set callback, return code %d\n", rc);
	}
	conn_opts.keepAliveInterval = 60;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client_handler;

	MQTTAsync_SSLOptions ssl = MQTTAsync_SSLOptions_initializer;
	ssl.trustStore = "/home/pi/Desktop/BKLight/ca.crt";
	ssl.sslVersion = MQTT_SSL_VERSION_TLS_1_2;
	conn_opts.ssl = &ssl;

	/* Hàm connect sau khi thành công sẽ subcribe các topic cần thiết */

	if ((rc = MQTTAsync_connect(client_handler, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		Error_Handler("MQTTAsync_connect");
	}
}


void MQTT_Transmit(uint8_t *topic, uint8_t *payload)
{
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	int rc;

	opts.onSuccess = onSend;
	opts.onFailure = onSendFailure;
	opts.context = client_handler;
	pubmsg.payload = payload;
	pubmsg.payloadlen = (int)strlen(payload);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	if ((rc = MQTTAsync_sendMessage(client_handler, topic, &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start sendMessage, return code %d\n", rc);
		Error_Handler("MQTTAsync_sendMessage");
	}
}


void MQTT_LED_Data_Transmit(MQTT_LED_Data_t LED_Data)
{
	char buffer[MQTT_PAYLOAD_MAX_NUM];
	sprintf(buffer, "%d %d %d %d %d", LED_Data.node_addr, LED_Data.timestamp, LED_Data.on_off,\
	 							   LED_Data.dimming, LED_Data.current_sensor);
	MQTT_Transmit(MQTT_TOPIC_LED_DATA, buffer);
	
}

static void MQTT_Split_String(char *in_str, int out_array_value[], int *out_len)
{
	*out_len = 0;
	char temp[MQTT_PAYLOAD_MAX_NUM];
	memcpy(temp, in_str, strlen(in_str));
	
	// Sử dụng strtok để tách chuỗi theo dấu cách
	char* token = strtok(temp, " ");

	while (token != NULL) {
		// Thêm một số nguyên vào mảng
		(*out_len)++;
		out_array_value[*out_len - 1] = atoi(token);

		// Tiếp tục tách chuỗi
		token = strtok(NULL, " ");
	}
}

/**
  * Đây là hàm truyền tín hiệu alive của riêng Gateway(GW) lên Sever
  * 
  */
void MQTT_Send_GW_Alive(void)
{
	uint8_t temp[100];
	sprintf((char *)temp, "%d 1", time(NULL));
	MQTT_Transmit(MQTT_TOPIC_GATEWAY_ALIVE, temp);
}

/**
  * Đây là hàm truyền tín hiệu not alive của các node lên Sever
  * 
  */
void MQTT_Send_Node_Not_Alive(uint16_t node_addr, uint8_t fault)
{
	uint8_t temp[100];
	sprintf((char *)temp, "%d %d %d", time(NULL), node_addr, fault);
	MQTT_Transmit(MQTT_TOPIC_NODE_NOT_ALIVE, temp);
}


void MQTT_Task_Receive(void)
{
	while(MQTT_Rx_Count > 0)
	{
		int id = MQTT_Rx_Count - 1;
		if(strcmp(MQTT_Rx_Buffer[id].topic, MQTT_TOPIC_CONTROL_ONOFF) == 0)
		{
			int arr_temp[10], arr_len;
			MQTT_Split_String(MQTT_Rx_Buffer[id].payload, arr_temp, &arr_len);

			MQTT_LED_Control_OnOff_t on_off_send;
			on_off_send.node_addr = arr_temp[0];
			on_off_send.on_off = arr_temp[1];
			LORA_Send_Control_OnOff(on_off_send);

			char temp[100]="";
			sprintf(temp, "On_Off success. Dia chi: %d. OnOff: %d", on_off_send.node_addr,on_off_send.on_off);
			MQTT_Transmit("Control_Debug", temp);

			printf("\nonoff\n");
		
		}
		else if(strcmp(MQTT_Rx_Buffer[id].topic, MQTT_TOPIC_CONTROL_DIMMING) == 0)
		{
			int arr_temp[10], arr_len;
			MQTT_Split_String(MQTT_Rx_Buffer[id].payload, arr_temp, &arr_len);

			MQTT_LED_Control_Dimming_t dimming_send;
			dimming_send.node_addr = arr_temp[0];
			dimming_send.dimming = arr_temp[1];
			LORA_Send_Control_Dimming(dimming_send);

			char temp[100]="";
			sprintf(temp, "Dimming success. Dia chi: %d. Dimming: %d%%", dimming_send.node_addr,dimming_send.dimming);
			MQTT_Transmit("Control_Debug", temp);

			printf("\ndimming\n");
		}
		else if(strcmp(MQTT_Rx_Buffer[id].topic, MQTT_TOPIC_CONTROL_TIMER) == 0)
		{
			int arr_temp[10], arr_len;
			MQTT_Split_String(MQTT_Rx_Buffer[id].payload, arr_temp, &arr_len);

			MQTT_LED_Control_SetTime_t settime_send;
			settime_send.node_addr = arr_temp[0];
			settime_send.time1_hour = arr_temp[1];
			settime_send.time1_minute = arr_temp[2];
			settime_send.time2_hour = arr_temp[3];
			settime_send.time2_minute = arr_temp[4];
			settime_send.time3_hour = arr_temp[5];
			settime_send.time3_minute = arr_temp[6];
			settime_send.time4_hour = arr_temp[7];
			settime_send.time4_minute = arr_temp[8];
			LORA_Send_Control_Set_Time(settime_send);

			char temp[100]="";
			sprintf(temp, "Set_Time success. Dia chi: %d. Thoi gian 1: %d:%d. Thoi gian 2: %d:%d. Thoi gian 3: %d:%d. Thoi gian 4: %d:%d\n",\
			 settime_send.node_addr,settime_send.time1_hour,settime_send.time1_minute,settime_send.time2_hour,settime_send.time2_minute,\
			 settime_send.time3_hour,settime_send.time3_minute,settime_send.time4_hour,settime_send.time4_minute);
			MQTT_Transmit("Control_Debug", temp);

			printf("\nsettime\n");
		}
		else if(strcmp(MQTT_Rx_Buffer[id].topic, MQTT_TOPIC_FAKE_SYNCTIME) == 0)
		{
			int arr_temp[10], arr_len;
			MQTT_Split_String(MQTT_Rx_Buffer[id].payload, arr_temp, &arr_len);

			uint32_t fake_timestamp = arr_temp[0] - 7*60*60;

			for(int i=0; i < NUM_END_NODE; i++)
			{
				LORA_Send_Synctime(fake_timestamp, 1, lora_end_node[i].node_address);
			}
			

			char temp[100]="";
			sprintf(temp, "Synctime success. Timestamp: %d\n", fake_timestamp);
			MQTT_Transmit("Control_Debug", temp);

			printf("\nFAKE_SYNCTIME\n");
		}
		memset(&MQTT_Rx_Buffer[id], 0, sizeof(MQTT_Message));
		MQTT_Rx_Count--;
	}
}

void Error_Handler(char *name_fail)
{
	while(1)
	{
		printf("Error in %s\n", name_fail);
		fflush(stdout);
		delay(1000);
	}
}
