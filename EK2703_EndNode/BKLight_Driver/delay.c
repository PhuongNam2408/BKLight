/*
 * dwt_delay.c
 *
 *  Created on: 19 Aug 2023
 *      Author: HP
 */

#include <delay.h>


/**************************************************************************//**
 * @brief
 *
 *****************************************************************************/
void Delay_Init(void)
{
  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }
}

/**************************************************************************//**
 * @brief
 *
 *****************************************************************************/
void Delay_us(uint32_t us) // microseconds
{
    uint32_t startTick = DWT->CYCCNT,
             delayTicks = us * (SystemCoreClock/1000000);

    while (DWT->CYCCNT - startTick < delayTicks);
}

/**************************************************************************//**
 * @brief
 *
 *****************************************************************************/
void Delay_ms(uint32_t ms) // microseconds
{
    uint32_t startTick = DWT->CYCCNT,
             delayTicks = ms * (SystemCoreClock/1000);

    while (DWT->CYCCNT - startTick < delayTicks);
}
