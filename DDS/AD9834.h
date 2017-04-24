#pragma once
#include<stm32f1xx_hal.h>

#define SCLK1		GPIOA->BSRR = GPIO_PIN_8
#define SCLK0		GPIOA->BRR = GPIO_PIN_8
#define FSYNC1		GPIOA->BSRR = GPIO_PIN_11
#define FSYNC0		GPIOA->BRR = GPIO_PIN_11

#define FSELECT1	GPIOC->BSRR = GPIO_PIN_6
#define FSELECT0	GPIOC->BRR = GPIO_PIN_6
#define PSELECT1	GPIOC->BSRR = GPIO_PIN_7
#define PSELECT0	GPIOC->BRR = GPIO_PIN_7
#define RESET1		GPIOC->BSRR = GPIO_PIN_8
#define RESET0		GPIOC->BRR = GPIO_PIN_8
#define SDATA1		GPIOC->BSRR = GPIO_PIN_9
#define SDATA0		GPIOC->BRR = GPIO_PIN_9


void Delay_us(uint32_t);
void WriteReg(uint16_t);
void AD9834_Init(void);
void AD9834_WriteFreq(uint32_t, _Bool);
void AD9834_SwitchMode(void);