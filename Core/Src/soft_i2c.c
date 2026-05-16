#include "soft_i2c.h"

#define SCL_PIN  GPIO_PIN_3
#define SDA_PIN  GPIO_PIN_5
#define I2C_PORT GPIOB

#define SCL_H()  HAL_GPIO_WritePin(I2C_PORT, SCL_PIN, GPIO_PIN_SET)
#define SCL_L()  HAL_GPIO_WritePin(I2C_PORT, SCL_PIN, GPIO_PIN_RESET)
#define SDA_H()  HAL_GPIO_WritePin(I2C_PORT, SDA_PIN, GPIO_PIN_SET)
#define SDA_L()  HAL_GPIO_WritePin(I2C_PORT, SDA_PIN, GPIO_PIN_RESET)

static void I2C_Delay(void) {
    // F407 @ 168MHz，约 1us
    for (volatile int i = 0; i < 20; i++);
}

static void I2C_Start(void) {
    SDA_H(); SCL_H(); I2C_Delay();
    SDA_L(); I2C_Delay();
    SCL_L(); I2C_Delay();
}

static void I2C_Stop(void) {
    SDA_L(); SCL_H(); I2C_Delay();
    SDA_H(); I2C_Delay();
}

static void I2C_WriteByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        if (byte & 0x80) SDA_H();
        else             SDA_L();
        byte <<= 1;
        I2C_Delay();
        SCL_H(); I2C_Delay();
        SCL_L(); I2C_Delay();
    }
    // 等待 ACK（不校验，直接放掉）
    SDA_H();
    SCL_H(); I2C_Delay();
    SCL_L(); I2C_Delay();
}

void Soft_I2C_Init(void) {
    // 引脚已在 CubeIDE 里配置为 Open-Drain + Pull-up
    // 这里只需拉高总线，确保空闲状态
    SDA_H();
    SCL_H();
}

void Soft_I2C_WriteCmd(uint8_t addr, uint8_t cmd) {
    __disable_irq();       // 软 I2C 不能被中断打断，否则时序错乱
    I2C_Start();
    I2C_WriteByte(addr);  // 设备地址
    I2C_WriteByte(0x00);  // 控制字节：命令模式
    I2C_WriteByte(cmd);
    I2C_Stop();
    __enable_irq();
}

void Soft_I2C_WriteData(uint8_t addr, uint8_t data) {
    __disable_irq();       // 软 I2C 不能被中断打断，否则时序错乱
    I2C_Start();
    I2C_WriteByte(addr);  // 设备地址
    I2C_WriteByte(0x40);  // 控制字节：数据模式
    I2C_WriteByte(data);
    I2C_Stop();
    __enable_irq();
}
