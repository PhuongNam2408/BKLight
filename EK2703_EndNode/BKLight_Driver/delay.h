/*
 * dwt_delay.h
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#ifndef NAM_DRIVER_DWT_DELAY_H_
#define NAM_DRIVER_DWT_DELAY_H_

#include "em_chip.h"


void Delay_Init(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);

#endif /* NAM_DRIVER_DWT_DELAY_H_ */
