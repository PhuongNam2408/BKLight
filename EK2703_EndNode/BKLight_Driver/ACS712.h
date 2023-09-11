/*
 * ACS712.h
 *
 *  Created on: 11 Sep 2023
 *      Author: HP
 */

#ifndef BKLIGHT_DRIVER_ACS712_H_
#define BKLIGHT_DRIVER_ACS712_H_

#include "em_cmu.h"
#include "em_iadc.h"
#include "em_ldma.h"
#include "main.h"

// Set CLK_ADC to 10 MHz
#define CLK_SRC_ADC_FREQ    20000000  // CLK_SRC_ADC
#define CLK_ADC_FREQ        10000000  // CLK_ADC - 10 MHz max in normal mode

/*
 * Specify the IADC input using the IADC_PosInput_t typedef.  This
 * must be paired with a corresponding macro definition that allocates
 * the corresponding ABUS to the IADC.  These are...
 *
 * GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AEVEN0_ADC0
 * GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AODD0_ADC0
 * GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BEVEN0_ADC0
 * GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BODD0_ADC0
 * GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDEVEN0_ADC0
 * GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDODD0_ADC0
 *
 * ...for port A, port B, and port C/D pins, even and odd, respectively.
 */

/* Với đầu vào ACS sẽ là PB0 như ở define bên main.h */
#if  ((ACS712_OUT_PORT == gpioPortB) && (ACS712_OUT_PIN == 0))
#define IADC_INPUT_0_PORT_PIN     iadcPosInputPortBPin0;

#define IADC_INPUT_0_BUS          BBUSALLOC
#define IADC_INPUT_0_BUSALLOC     GPIO_BBUSALLOC_BEVEN0_ADC0
#endif

#define NUM_SAMPLES 1
// Use specified LDMA channel
#define IADC_LDMA_CH              0

void ACS712_Init(void);

#endif /* BKLIGHT_DRIVER_ACS712_H_ */
