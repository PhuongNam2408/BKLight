#include "mqtt.h"


#define TOPIC	"test_topic"
#define PAYLOAD	"Hello I'm Raspberry Pi 4B!"

/* MQTT Handler */
static MQTTAsync client_handler;

volatile uint16_t MQTT_topic_tx_index = 0;

void Error_Handler(char *name_fail);

volatile int MQTT_Connect_flag = 0;
volatile uint16_t mqtt_topic_control_onoff_flag = 0; 
volatile uint16_t mqtt_topic_control_dimming_flag = 0; 
volatile uint16_t mqtt_topic_control_timer_flag = 0; 

volatile uint16_t MQTT_Rx_Count = 0;
MQTT_Message MQTT_Rx_Buffer[20];


extern MQTT_LED_Control_OnOff_t test_onoff;
extern MQTT_LED_Control_Dimming_t test_dimming;
extern MQTT_LED_Control_SetTime_t test_settime;

static int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message)
{
	if(strstr(topicName, "LED_Control") != NULL)
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
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	printf("\nConnection lost\n");
	printf("     cause: %s\n", cause);

	printf("Reconnecting\n");
	conn_opts.keepAliveInterval = 60;
	conn_opts.cleansession = 1;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		Error_Handler("MQTTAsync_connect");
	}
}


static void onSend(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	printf("Message with token value %d delivery confirmed\n", response->token);
	//opts.onSuccess = onDisconnect;
	//opts.onFailure = onDisconnectFailure;
	opts.context = client;
	// if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	// {
	// 	printf("Failed to start disconnect, return code %d\n", rc);
	// 	Error_Handler();
	// }
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
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	int rc;

	MQTT_Transmit(TOPIC, PAYLOAD);

	MQTT_Connect_flag = 1;

	printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n", TOPIC, CLIENTID, QOS);
	opts.onSuccess = onSubscribe;
	opts.onFailure = onSubscribeFailure;
	opts.context = client;
	if ((rc = MQTTAsync_subscribe(client, "LED_Control/#", QOS, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start subscribe, return code %d\n", rc);
		Error_Handler("MQTTAsync_subscribe");
	}
}

static void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Connect failed, rc %d\n", response ? response->code : 0);
	Error_Handler("onConnectFailure");
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
		Error_Handler("MQTTAsync_setCallbacks");
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

void MQTT_Task_Receive(void)
{
	while(MQTT_Rx_Count > 0)
	{
		int id = MQTT_Rx_Count - 1;
		if(strcmp(MQTT_Rx_Buffer[id].topic, MQTT_TOPIC_CONTROL_ONOFF) == 0)
		{
			int arr_temp[10], arr_len;
			MQTT_Split_String(MQTT_Rx_Buffer[id].payload, arr_temp, &arr_len);

			test_onoff.node_addr = arr_temp[0];
			test_onoff.on_off = arr_temp[1];
			
			char temp[100]="";
			sprintf(temp, "On_Off success\nDia chi: %d\nOnOff: %d", test_onoff.node_addr,test_onoff.on_off);
			MQTT_Transmit("Control_Debug", temp);

			printf("\nonoff\n");
		
		}
		else if(strcmp(MQTT_Rx_Buffer[id].topic, MQTT_TOPIC_CONTROL_DIMMING) == 0)
		{
			int arr_temp[10], arr_len;
			MQTT_Split_String(MQTT_Rx_Buffer[id].payload, arr_temp, &arr_len);

			test_dimming.node_addr = arr_temp[0];
			test_dimming.dimming = arr_temp[1];

			char temp[100]="";
			sprintf(temp, "Dimming success\nDia chi: %d\nDimming: %d%%", test_dimming.node_addr,test_dimming.dimming);
			MQTT_Transmit("Control_Debug", temp);

			printf("\ndimming\n");
		}
		else if(strcmp(MQTT_Rx_Buffer[id].topic, MQTT_TOPIC_CONTROL_TIMER) == 0)
		{
			int arr_temp[10], arr_len;
			MQTT_Split_String(MQTT_Rx_Buffer[id].payload, arr_temp, &arr_len);

			test_settime.node_addr = arr_temp[0];
			test_settime.time = arr_temp[1];
			test_settime.on_off = arr_temp[2];
			test_settime.dimming = arr_temp[3];

			char temp[100]="";
			sprintf(temp, "Set_Time success\nDia chi: %d\nThoi gian: %d\nOnOff: %d\nDimming: %d%%",\
			 test_settime.node_addr,test_settime.time,test_settime.on_off,test_settime.dimming);
			MQTT_Transmit("Control_Debug", temp);

			printf("\nsettime\n");
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
		sleep(10);
	}
}
