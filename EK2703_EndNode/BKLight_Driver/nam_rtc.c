/*
 * nam_rtc.c
 *
 *  Created on: 3 Sep 2023
 *      Author: HP
 */
#include "nam_rtc.h"


static const uint8_t numofdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

void RTC_Init(void)
{
    CMU_ClockSelectSet(cmuClock_BURTC, cmuSelect_LFRCO);
    CMU_ClockEnable(cmuClock_BURTC, true);

    BURTC_Init_TypeDef burtcInit = BURTC_INIT_DEFAULT;
    burtcInit.clkDiv = 32768;
    //burtcInit.debugRun = true;
    BURTC_Init(&burtcInit);

    BURTC_CounterReset();

    RTCTIME settime;
    settime.year = (uint16_t)2023;
    settime.month = (uint8_t)5;
    settime.mday = (uint8_t)10;
    settime.hour = (uint8_t)1;
    settime.min = (uint8_t)2;
    settime.sec = (uint8_t)3;

    RTC_SetTime(&settime);

    BURTC_Enable(true);
}

/*------------------------------------------*/
/* Set time in calendar form                */
/*------------------------------------------*/

void RTC_SetTime(const RTCTIME* rtc)
{
  uint32_t utc;
  utc = RTC_GetTicksFromTime(rtc);
  RTC_SetTimeFromTicks(utc);

}

void RTC_SetTimeFromTicks(uint32_t ticks)
{
  /* Wait until last write operation on RTC registers has finished */
  BURTC_Stop();
  /* Change the current time */
  BURTC->CNT = ticks;
  /* Wait until last write operation on RTC registers has finished */
  BURTC_Start();
}

/*------------------------------------------*/
/* Convert time structure to timeticks      */
/*------------------------------------------*/

uint32_t RTC_GetTicksFromTime(const RTCTIME *rtc)
{
  uint32_t utc, i, y;
  y = rtc->year - 1970;
  if (y > 2106 || !rtc->month || !rtc->mday) return 0;

  utc = y / 4 * 1461; y %= 4;
  utc += y * 365 + (y > 2 ? 1 : 0);
  for (i = 0; i < 12 && i + 1 < rtc->month; i++) {
    utc += numofdays[i];
    if (i == 1 && y == 2) utc++;
  }
  utc += rtc->mday - 1;
  utc *= 86400;
  utc += rtc->hour * 3600 + rtc->min * 60 + rtc->sec;
  return utc;
}


/*------------------------------------------*/
/* Get time ticks from RTC counter          */
/*------------------------------------------*/
uint32_t RTC_GetTicksFromRTC()
{
  uint32_t timeticks;
  timeticks = BURTC_CounterGet();

  return timeticks;
}

/*------------------------------------------*/
/* Get time in calendar form                */
/*------------------------------------------*/

void RTC_GetTime(RTCTIME *rtc)
{
  uint32_t n,i,d,utc;
  utc = BURTC_CounterGet();
  /* Compute  hours */
  rtc->sec = (uint8_t)(utc % 60); utc /= 60;
  rtc->min = (uint8_t)(utc % 60); utc /= 60;
  rtc->hour = (uint8_t)(utc % 24); utc /= 24;
  rtc->wday = (uint8_t)((utc + 4) % 7);
  rtc->year = (uint16_t)(1970 + utc / 1461 * 4); utc %= 1461;
  n = ((utc >= 1096) ? utc - 1 : utc) / 365;
  rtc->year += n;
  utc -= n * 365 + (n > 2 ? 1 : 0);
  for (i = 0; i < 12; i++) {
    d = numofdays[i];
    if (i == 1 && n == 2) d++;
    if (utc < d) break;
    utc -= d;
  }
  rtc->month = (uint8_t)(1 + i);
  rtc->mday = (uint8_t)(1 + utc);
}



