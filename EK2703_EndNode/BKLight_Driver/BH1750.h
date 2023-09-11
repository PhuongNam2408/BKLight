/*
 * BH1750.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Personal
 */
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"

#ifndef BH1750_BH1750_H_
#define BH1750_BH1750_H_

#define I2C_SCL_PORT  gpioPortB
#define I2C_SCL_PIN   4

#define I2C_SDA_PORT  gpioPortB
#define I2C_SDA_PIN   5

#define BH1750_LIGHT_THRESHOLD  500

/* Thời gian giữ trạng thái liên tục để kích hoạt sự chuyển trạng thái ngày/đêm */
#define BH1750_TIME_ON_THRESHOLD  5 //5s: để demo => cho thấp thời gian phải chờ

void Init_I2C(void);
void BH1750_Init(uint16_t SlaveAddress, uint8_t *txBuff, uint16_t numBytes);
void BH1750_Multi_Read(uint16_t SlaveAddress, uint8_t *rxBuff);

#endif /* BH1750_BH1750_H_ */
