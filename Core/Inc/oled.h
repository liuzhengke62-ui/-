#ifndef OLED_H
#define OLED_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowString(uint8_t x, uint8_t col, char *str);
void OLED_ShowNumber(uint8_t x, uint8_t col, int32_t num);
void OLED_ShowFloat(uint8_t x, uint8_t col, float val, uint8_t decimals);

#endif
