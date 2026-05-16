#include <stdint.h>


float buck_I_Kp = 2.0f;
float buck_I_Ki = 0.5f;     
float buck_I_integral = 0.0f;
uint16_t pwm_duty = 0;

#define DUTY_MAX  1800.0f
#define DUTY_MIN  210.0f

void BUCK_Current_Control(float fact_number, float Hope_number, float Kp, float Ki)
{
    float error;
    float duty_f;

    error = Hope_number - fact_number;

    buck_I_integral += error;

    // 积分限幅：确保 Ki * integral 能覆盖整个输出范围
    float integ_max = DUTY_MAX / Ki;
    float integ_min = -(DUTY_MAX / Ki);  // 允许负方向也有足够余量
    if (buck_I_integral > integ_max) buck_I_integral = integ_max;
    else if (buck_I_integral < integ_min) buck_I_integral = integ_min;

    duty_f = Kp * error + Ki * buck_I_integral;

    // 输出限幅
    if (duty_f > DUTY_MAX) duty_f = DUTY_MAX;
    else if (duty_f < DUTY_MIN) duty_f = DUTY_MIN;

    pwm_duty = (uint16_t)duty_f;
}