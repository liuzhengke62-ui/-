#include "bsp_key.h"
#include "stm32f4xx_hal.h"

#define KEY_PORT     GPIOE
#define KEY1_PIN     GPIO_PIN_1    // PE1 → 步进按键
#define DEBOUNCE_MS  200

extern float BUCK_Iout_target;

static uint8_t Key_Read(uint16_t pin)
{
    return (HAL_GPIO_ReadPin(KEY_PORT, pin) == GPIO_PIN_RESET);
}

void Key_Scan(void)
{
    static uint32_t last_tick = 0;
    static uint8_t  k1s = 0;
    uint32_t now = HAL_GetTick();

    if (now - last_tick < DEBOUNCE_MS) return;
    last_tick = now;

    // PE1: 步进按键，每次按下 BUCK_Iout_target - 0.1A，1.0~2.0A 循环
    if (Key_Read(KEY1_PIN)) {
        if (k1s == 0) {
            k1s = 1;
            BUCK_Iout_target -= 0.1f;
            if (BUCK_Iout_target < 1.0f) {
                BUCK_Iout_target = 2.0f;
            }
        }
    } else {
        k1s = 0;
    }
}
