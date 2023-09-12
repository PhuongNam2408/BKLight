/*
 * main.h
 *
 *  Created on: 8 Sep 2023
 *      Author: HP
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_



/**************************************************************************//**
 * @brief
 *    Define
 *****************************************************************************/

// Size of the buffer for received data
#define BUFLEN  80

// Define VALUE
#define GATEWAY_ADDH          0xFF
#define GATEWAY_ADDL          0xFF


// Define pwm_lut
#define LED_DIMMING_PIR_ON  pwm_lut[100]
#define LED_DIMMING_PIR_OFF pwm_lut[0]

// Define LED control state
#define LED_CONTROL_ON      pwm_lut[100]
#define LED_CONTROL_OFF     pwm_lut[0]



#define PWM_LED_PORT  gpioPortA
#define PWM_LED_PIN   4

#define PIR_OUT_PORT  gpioPortC
#define PIR_OUT_PIN   1

#define BH1750_SDA_PORT  gpioPortB
#define BH1750_SDA_PIN    5
#define BH1750_SCL_PORT  gpioPortB
#define BH1750_SCL_PIN   4

#define ACS712_OUT_PORT  gpioPortB
#define ACS712_OUT_PIN   0

/* Các giá trị default dựa vào timemark. 1 2 3 4 tương ứng với các khoảng sáng từ cao đến thấp */
#define LED_STATE_DEFAULT_1     1
#define LED_DIMMING_DEFAULT_1   100
#define LED_STATE_DEFAULT_2     1
#define LED_DIMMING_DEFAULT_2   70
#define LED_STATE_DEFAULT_3     1
#define LED_DIMMING_DEFAULT_3   30
#define LED_STATE_DEFAULT_4     0
#define LED_DIMMING_DEFAULT_4   0

/* Chu kỳ cập nhật dữ liệu Node, đơn vị: giây */
#define TRANSMIT_NODE_DATA_CYCLE_TIME 5

/* Thời gian tối đa 1 lệnh ở trên Sever chiếm quyền điều khiển LED, đơn vị: giây */
#define SEVER_CONTROL_TIME  10

/* Trạng thái thời gian tại các khoảng dựa vào timmark*/
typedef enum
{
  TIME_STATE_1,
  TIME_STATE_2,
  TIME_STATE_3,
  TIME_STATE_4
}time_state_t;

/**************************************************************************//**
 * @brief
 *    Receive - Transmit
 *****************************************************************************/

// Create struct

typedef struct
{
  uint16_t ACS712;  //Cảm biến dòng điện, đơn vị là mA
  uint16_t BH1750;  //Cảm biến ánh sáng, đơn vị là lx
  uint8_t PIR;  //Cảm biến chuyển động. 1: có người; 0: không có người
}Sensor_value_t;

typedef struct
{
  uint8_t Time_Mark_1_hour;
  uint8_t Time_Mark_1_minute;
  uint8_t Time_Mark_2_hour;
  uint8_t Time_Mark_2_minute;
  uint8_t Time_Mark_3_hour;
  uint8_t Time_Mark_3_minute;
  uint8_t Time_Mark_4_hour;
  uint8_t Time_Mark_4_minute;
}Time_Mark_t;


#endif /* SRC_MAIN_H_ */
