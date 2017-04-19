#pragma once
#include<stm32f1xx_hal.h>

#define MODE_WRITE		GPIOC->BRR = GPIO_PIN_10
#define WRITE_COM		GPIOC->BRR = GPIO_PIN_11
#define WRITE_DATA		GPIOC->BSRR = GPIO_PIN_11
#define ENABLE			GPIOC->BSRR = GPIO_PIN_12
#define DISABLE			GPIOC->BRR = GPIO_PIN_12

#define DATA_OUT		GPIOB->ODR

void LCD1602_Init(void);
void LCD1602_ShowStr(uint8_t*);
void SendData(uint8_t);
void SendCom(uint8_t);