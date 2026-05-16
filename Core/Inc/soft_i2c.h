#ifndef SOFT_I2C_H
#define SOFT_I2C_H

#include "stm32f4xx_hal.h"

void Soft_I2C_Init(void);
void Soft_I2C_WriteCmd(uint8_t addr, uint8_t cmd);
void Soft_I2C_WriteData(uint8_t addr, uint8_t data);

#endif
