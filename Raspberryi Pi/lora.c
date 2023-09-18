#include "lora.h"
#include "uart.h"


extern int global_fd;
extern int global_fd_flag;

extern Lora_Configuration_t global_configuration;

extern lora_end_node_t lora_end_node[];

void LoRa_Init(void)
{
	/* Init Pins:
	*
	*
	*  */
	// GPIO Mode set
	if (wiringPiSetup () == -1)
	{
		Error_Handler;
	}
	pinMode(LORA_M0_PIN, OUTPUT);
	pinMode(LORA_M1_PIN, OUTPUT);
	pinMode(LORA_AUX_PIN, INPUT);

	digitalWrite(LORA_M0_PIN, LOW);
	digitalWrite(LORA_M1_PIN, LOW);
	digitalWrite(LORA_AUX_PIN, HIGH);

 	LoRa_getConfiguration(&global_configuration);

	global_configuration.ADDH = (uint8_t) (GATE_WAY_ADDR >> 8);
	global_configuration.ADDL = (uint8_t) (GATE_WAY_ADDR | 0xFF);

	global_configuration.SPED.airDataRate = AIR_DATA_RATE_101_192;
	global_configuration.SPED.uartParity = MODE_00_8N1;
	global_configuration.SPED.uartBaudRate = UART_BPS_115200;

	global_configuration.CHAN = LORA_CHANNEL;

	global_configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
	global_configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
	global_configuration.OPTION.wirelessWakeupTime = WAKE_UP_250;
	global_configuration.OPTION.fec = FEC_1_ON;
	global_configuration.OPTION.transmissionPower = POWER_20;

	LoRa_setConfiguration(global_configuration, WRITE_CFG_PWR_DWN_SAVE);

	for(int i = 0; i < NUM_END_NODE; i++)
	{
		lora_end_node[i].node_address = i+1;
		lora_end_node[i].fault = NODE_FAULT_NONE;
	}

	UART_Init();
}

void LoRa_setMode(MODE_TYPE mode) {

  delay(40);
  switch (mode)
  {
    case MODE_0_NORMAL:
      // Mode 0 | normal operation
      digitalWrite(LORA_M0_PIN, LOW);
      digitalWrite(LORA_M1_PIN, LOW);
    break;
    case MODE_1_WAKE_UP:
      digitalWrite(LORA_M0_PIN, HIGH);
      digitalWrite(LORA_M1_PIN, LOW);
    break;
    case MODE_2_POWER_SAVING:
      digitalWrite(LORA_M0_PIN, LOW);
      digitalWrite(LORA_M1_PIN, HIGH);
    break;
    case MODE_3_PROGRAM:
      // Mode 3 | Setting operation
      digitalWrite(LORA_M0_PIN, HIGH);
      digitalWrite(LORA_M1_PIN, HIGH);
    break;
    default:
      break;
  }

  // data sheet says 2ms later control is returned, let's give just a bit more time
  // these modules can take time to activate pins
  delay(40);
}



void LoRa_getConfiguration(Lora_Configuration_t *config)
{
	piLock(0);
	LoRa_setMode(MODE_3_PROGRAM);
	uint8_t command_buff[3] = {READ_CONFIGURATION, READ_CONFIGURATION, READ_CONFIGURATION};
	uint8_t *temp = (uint8_t *) config;

	serialClose(global_fd);
	if ((global_fd = serialOpen ("/dev/ttyAMA0", LORA_BAUD_RATE_CONFIG)) < 0)
	{
		Error_Handler("serialOpen");
	}
	for(int i=0; i < 3; i++)
	{
		serialPutchar(global_fd, command_buff[i]);
	}
	for(int i=0; i < 6;i++)
	{
		temp[i] = serialGetchar(global_fd);
	}
	serialClose(global_fd);
	global_fd = serialOpen ("/dev/ttyAMA0", LORA_BAUD_RATE_NORMAL);	
	piUnlock(0);
	LoRa_setMode(MODE_0_NORMAL);
}


void LoRa_setConfiguration(Lora_Configuration_t config, PROGRAM_COMMAND save_type)
{
	piLock(0);	

	uint8_t *temp = (uint8_t *)&config;
	LoRa_setMode(MODE_3_PROGRAM);

	switch(save_type)
	{
		case WRITE_CFG_PWR_DWN_SAVE:
		case WRITE_CFG_PWR_DWN_LOSE:
	{
		config.HEAD = save_type;
		serialClose(global_fd);
		if ((global_fd = serialOpen ("/dev/ttyAMA0", LORA_BAUD_RATE_CONFIG)) < 0)
		{
			Error_Handler("serialOpen");
		}
		for(int i=0; i < sizeof(Lora_Configuration_t); i++)
		{
			serialPutchar(global_fd, temp[i]);
		}
			delay(50);
			serialClose(global_fd);

			global_fd = serialOpen ("/dev/ttyAMA0", LORA_BAUD_RATE_NORMAL);	
	}
		break;
	case READ_CONFIGURATION:
	case READ_MODULE_VERSION:
	case WRITE_RESET_MODULE:
		Error_Handler("serialOpen");
	}
	piUnlock(0);
  LoRa_setMode(MODE_0_NORMAL);
}

FixedMessage_t fixed_message; 
void LoRa_sendFixedMessage(uint8_t ADDH, uint8_t ADDL, uint8_t Channel, uint8_t *message)
{
	uint16_t size = strlen((char *)message);
	fixed_message.ADDH = ADDH;
	fixed_message.ADDL = ADDL;
	fixed_message.CHAN = Channel;
	memcpy(fixed_message.message, message, size);
	UART_Add_To_TxQueue((uint8_t *)&fixed_message, size+3);
}
















