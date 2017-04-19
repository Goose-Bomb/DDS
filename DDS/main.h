#pragma once
#include <stm32f1xx_hal.h>

extern void LCD1602_Init(void);
extern void LCD1602_ShowStr(uint8_t*);
extern void AD9834_Init(void);
extern void AD9834_WriteFreq(uint32_t, _Bool);

void GPIO_Init(void);
void SystemClock_Config(void);
