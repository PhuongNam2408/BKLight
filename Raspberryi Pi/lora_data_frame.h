#ifndef LORA_DATA_FRAME_H_
#define LORA_DATA_FRAME_H_

#include <stdint.h>

typedef enum
{
	ADDH,
	ADDL,
	KEY,
	LENGTH,
	VALUE,
	CRC,
}read_state_t;
typedef struct 
{
	uint16_t node_address; 
	uint32_t timestamp;
	uint8_t led_on_off;
	uint8_t led_dimming;
	uint16_t led_current;
}lora_end_node_t;

#define NUM_END_NODE	10

#define LORA_CHANNEL	15

#define	GATE_WAY_ADDR	0xFFFF

#define END_NODE_1_ADDR	0x0001
#define END_NODE_2_ADDR	0x0002

#define	KEY_END_NODE_DATA	0x01
#define KEY_CURRENT_WARNING	0x02
#define	KEY_SYNCTIME	0x03
#define	KEY_CONTROL_ONOFF	0x04
#define	KEY_CONTROL_DIMMING	0x05

#define	LENGTH_END_NODE_DATA	8
#define	LENGTH_SYNCTIME	4
#define	LENGTH_CONTROL_ONOFF	1
#define	LENGTH_CONTROL_DIMMING	1

#endif /* LORA_H_DATA_FRAME_ */