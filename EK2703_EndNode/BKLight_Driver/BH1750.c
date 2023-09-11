#include "BH1750.h"
#include <stdio.h>
#include "em_i2c.h"
//#include "bsp.h"

/** Return codes for single Controller mode transfer function. */

void Init_I2C(void)
{
  // Enable clocks to the I2C and GPIO
  CMU_ClockEnable(cmuClock_I2C0, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Use default settings
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  // GPIO configuration
  GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAndPullUpFilter, 1);
  GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAndPullUpFilter, 1);

  // Route I2C pins to GPIO
  GPIO->I2CROUTE[0].SDAROUTE = (GPIO->I2CROUTE[0].SDAROUTE & ~_GPIO_I2C_SDAROUTE_MASK)
                        | (I2C_SDA_PORT << _GPIO_I2C_SDAROUTE_PORT_SHIFT
                        | (I2C_SDA_PIN << _GPIO_I2C_SDAROUTE_PIN_SHIFT));
  GPIO->I2CROUTE[0].SCLROUTE = (GPIO->I2CROUTE[0].SCLROUTE & ~_GPIO_I2C_SCLROUTE_MASK)
                        | (I2C_SCL_PORT << _GPIO_I2C_SCLROUTE_PORT_SHIFT
                        | (I2C_SCL_PIN << _GPIO_I2C_SCLROUTE_PIN_SHIFT));
  GPIO->I2CROUTE[0].ROUTEEN = GPIO_I2C_ROUTEEN_SDAPEN | GPIO_I2C_ROUTEEN_SCLPEN;

  // Initialize and Enable the I2C
  I2C_Init(I2C0, &i2cInit);

}


/**
  * @brief Transmits in master mode an amount of data
  * @param SlaveAddress Địa chỉ của device, nhớ để ở dạng dịch trái 1
  *         (Chi tiết ở trong I2C_TransferSeq_TypeDef)
  * @param txBuff Con trỏ trỏ đến địa chỉ của data buffer
  * @param numBytes Số lượng byte muốn truyền (Buộc khác 0)
  * @retval none
  * @note
  */
void BH1750_Init(uint16_t SlaveAddress, uint8_t *txBuff, uint16_t numBytes)
{
  // Transfer structure
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef result;

  // Initialize I2C transfer
  i2cTransfer.addr          = SlaveAddress;
  i2cTransfer.flags         = I2C_FLAG_WRITE;
  i2cTransfer.buf[0].data   = txBuff;
  i2cTransfer.buf[0].len    = numBytes + 1;
  i2cTransfer.buf[1].data   = NULL;
  i2cTransfer.buf[1].len    = 0;

  result = I2C_TransferInit(I2C0, &i2cTransfer);

  // Send data
  while (result == i2cTransferInProgress) {
    result = I2C_Transfer(I2C0);
  }

  if (result != i2cTransferDone) {
    //infinite while loop to indicate I2C transmission problem

  }
}


/**
  * @brief Receive in master mode an Double byte of data
  * @param SlaveAddress Địa chỉ của device, nhớ để ở dạng dịch trái 1
  *         (Chi tiết ở trong I2C_TransferSeq_TypeDef)
  * @param rxBuff Con trỏ trỏ đến địa chỉ của data buffer
  * @retval none
  * @note
  */
void BH1750_Multi_Read(uint16_t SlaveAddress, uint8_t *rxBuff)
{
// Transfer structure
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef transferStatus;
  uint8_t rxData[2];

  i2cTransfer.addr = SlaveAddress;
  i2cTransfer.flags = I2C_FLAG_READ;
  i2cTransfer.buf[0].data = rxData;
  i2cTransfer.buf[0].len = 2;

  transferStatus = I2C_TransferInit(I2C0, &i2cTransfer);
  while (transferStatus == i2cTransferInProgress) {
    transferStatus = I2C_Transfer(I2C0);
  }

  if (transferStatus == i2cTransferDone) {
    rxBuff[0] = rxData[0];
    rxBuff[1] = rxData[1];
  }
  else {
  //infinite while loop to indicate I2C transmission problem
   // Error_Handler();
  }
}
