/*
 * nam_rtc.h
 *
 *  Created on: 3 Sep 2023
 *      Author: HP
 */

#ifndef RTC_NAM_RTC_H_
#define RTC_NAM_RTC_H_

#include "em_burtc.h"
#include "em_cmu.h"

typedef struct {
  uint16_t  year; /* 1970..2106 */
  uint8_t   month;  /* 1..12 */
  uint8_t   mday; /* 1..31 */
  uint8_t   hour; /* 0..23 */
  uint8_t   min;  /* 0..59 */
  uint8_t   sec;  /* 0..59 */
  uint8_t   wday; /* 0..6 (Sun..Sat) */
} RTCTIME;


void RTC_Init(void);

void RTC_GetTime(RTCTIME *rtc);

void RTC_SetTime(const RTCTIME* rtc);

void RTC_SetTimeFromTicks(uint32_t ticks);

uint32_t RTC_GetTicksFromTime(const RTCTIME *rtc);




#endif /* RTC_NAM_RTC_H_ */
