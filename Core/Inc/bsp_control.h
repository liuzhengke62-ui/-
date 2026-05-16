#ifndef __BSP_CONTROL_H
#define __BSP_CONTROL_H

#include <stdint.h>

extern uint16_t pwm_duty;

extern float buck_I_Kp;
extern float buck_I_Ki;

extern float buck_I_integral;

void BUCK_Current_Control(float fact_number, float Hope_number, float Kp, float Ki);

#endif
