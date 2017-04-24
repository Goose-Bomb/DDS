#pragma once
#include<stm32f1xx_hal.h>

void Key_Init(void);
extern void AD9834_SwitchMode(void);
extern void AD9834_WriteFreq(uint32_t, _Bool);
