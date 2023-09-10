#ifndef LORA_DATA_FRAME_H_
#define LORA_DATA_FRAME_H_

#include <stdint.h>

typedef enum
{
	SYNC1 = 0,
	SYNC2,
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
	uint8_t fault;
}lora_end_node_t;

#define NUM_END_NODE	5

#define LORA_CHANNEL	15

#define	GATE_WAY_ADDR	0xFFFF

#define GATE_WAY_SYNC1	0x47
#define GATE_WAY_SYNC2	0x57

#define END_NODE_SYNC1	0x45
#define END_NODE_SYNC2	0x4E

#define	KEY_END_NODE_DATA	0x01
#define KEY_CURRENT_WARNING	0x02
#define	KEY_SYNCTIME	0x03
#define	KEY_CONTROL_ONOFF	0x04
#define	KEY_CONTROL_DIMMING	0x05
#define	KEY_CONTROL_SETTIME	0x06

#define LORA_KEY_VALID(key) (	\
	(key) == KEY_END_NODE_DATA	\
	|| (key) == KEY_CURRENT_WARNING	\
	|| (key) == KEY_SYNCTIME	\
	|| (key) == KEY_CONTROL_ONOFF	\
	|| (key) == KEY_CONTROL_DIMMING	\
	|| (key) == KEY_CONTROL_SETTIME)


#define	LENGTH_END_NODE_DATA	8
#define	LENGTH_CURRENT_WARNING	5
#define	LENGTH_SYNCTIME	4
#define	LENGTH_CONTROL_ONOFF	1
#define	LENGTH_CONTROL_DIMMING	1
#define	LENGTH_CONTROL_SETTIME	8

#define LORA_LENGTH_VALID(length) (	\
	(length) == LENGTH_END_NODE_DATA	\
	|| (length) == LENGTH_SYNCTIME	\
	|| (length) == LENGTH_CONTROL_ONOFF	\
	|| (length) == LENGTH_CONTROL_DIMMING	\
	|| (length) == LENGTH_CONTROL_SETTIME)



#endif /* LORA_H_DATA_FRAME_ */