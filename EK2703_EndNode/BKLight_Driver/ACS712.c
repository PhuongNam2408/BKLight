/*
 * ACS712.c
 *
 *  Created on: 11 Sep 2023
 *      Author: HP
 */

#include "ACS712.h"

/*******************************************************************************
 ***************************   GLOBAL VARIABLES   *******************************
 ******************************************************************************/

/// Globally declared LDMA link descriptor
LDMA_Descriptor_t descriptor;

// Buffer to store IADC samples
uint32_t ACS712_Buffer[NUM_SAMPLES];

void ACS712_Init(void)
{

  /********************* Init ADC *********************/
  // Declare initialization structures
  IADC_Init_t init_adc = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitScan_t initScan = IADC_INITSCAN_DEFAULT;

  // Scan table structure
  IADC_ScanTable_t scanTable = IADC_SCANTABLE_DEFAULT;

  CMU_ClockEnable(cmuClock_IADC0, true);

  // Shutdown between conversions to reduce current
  init_adc.warmup = iadcWarmupNormal;

  // Set the HFSCLK prescale value here
  init_adc.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

  /*
   * Configuration 0 is used by both scan and single conversions by
   * default.  Use internal bandgap as the reference and specify the
   * reference voltage in mV.
   *
   * Resolution is not configurable directly but is based on the
   * selected oversampling ratio (osrHighSpeed), which defaults to
   * 2x and generates 12-bit results.
   */
  initAllConfigs.configs[0].reference = iadcCfgReferenceVddx;
  initAllConfigs.configs[0].osrHighSpeed = iadcCfgOsrHighSpeed2x;
  initAllConfigs.configs[0].analogGain = iadcCfgAnalogGain1x;

  /*
   * CLK_SRC_ADC must be prescaled by some value greater than 1 to
   * derive the intended CLK_ADC frequency.
   *
   * Based on the default 2x oversampling rate (OSRHS)...
   *
   * conversion time = ((4 * OSRHS) + 2) / fCLK_ADC
   *
   * ...which results in a maximum sampling rate of 833 ksps with the
   * 2-clock input multiplexer switching time is included.
   */
  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                                                     CLK_ADC_FREQ,
                                                                     0,
                                                                     iadcCfgModeNormal,
                                                                     init_adc.srcClkPrescale);

  /*
   * Trigger continuously once scan is started.  Note that
   * initScan.start = false by default, so conversions must be started
   * manually with IADC_command(IADC0, iadcCmdStartScan).
   *
   * Set the SCANFIFODVL flag when scan FIFO holds 2 entries.  In this
   * example, the interrupt associated with the SCANFIFODVL flag in
   * the IADC_IF register is not used.
   *
   * Enable DMA wake-up to save the results when the specified FIFO
   * level is hit.
   */
  initScan.triggerAction = iadcTriggerActionContinuous;
  initScan.dataValidLevel = iadcFifoCfgDvl2;
  initScan.fifoDmaWakeup = true;

  /*
   * Configure entries in the scan table.  CH0 is single-ended from
   * input 0; CH1 is single-ended from input 1.
   */
  scanTable.entries[0].posInput = IADC_INPUT_0_PORT_PIN;
  scanTable.entries[0].negInput = iadcNegInputGnd;
  scanTable.entries[0].includeInScan = true;


  // Initialize IADC
  IADC_init(IADC0, &init_adc, &initAllConfigs);

  // Initialize scan
  IADC_initScan(IADC0, &initScan, &scanTable);

  // Allocate the analog bus for ADC0 inputs
  GPIO->IADC_INPUT_0_BUS |= IADC_INPUT_0_BUSALLOC;


  /***************** Init DMA *******************/
  // Declare LDMA init structs
  LDMA_Init_t init_dma = LDMA_INIT_DEFAULT;

  // Initialize LDMA with default configuration
  LDMA_Init(&init_dma);

  // Trigger LDMA transfer on IADC scan completion
  LDMA_TransferCfg_t transferCfg =
    LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_IADC0_IADC_SCAN);

  /*
   * Set up a linked descriptor to save scan results to the
   * user-specified buffer.  By linking the descriptor to itself
   * (the last argument is the relative jump in terms of the number of
   * descriptors), transfers will run continuously until firmware
   * otherwise stops them.
   */
  descriptor =
    (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_WORD(&(IADC0->SCANFIFODATA), ACS712_Buffer, NUM_SAMPLES, 0);

  /*
   * Start the transfer.  The LDMA request and interrupt after saving
   * the specified number of IADC conversion results.
   */
  LDMA_StartTransfer(IADC_LDMA_CH, (void*)&transferCfg, (void*)&descriptor);

  /****************** Start ADC ******************/
  // Start scan
  IADC_command(IADC0, iadcCmdStartScan);

}

void LDMA_IRQHandler(void)
{
  // Clear interrupt flags
  LDMA_IntClear(1 << IADC_LDMA_CH);

  /*
   * Toggle GPIO to signal LDMA transfer is complete.  The low/high
   * time will be NUM_SAMPLES divided by the sampling rate, the
   * calculations for which are explained above.  For the example
   * defaults (1024 samples and a sampling rate of 833 ksps), the
   * low/high time will be around 1.23 ms, subject to FSRCO tuning
   * accuracy.
   */
  //GPIO_PinOutToggle(gpioPortA, 7);
}

