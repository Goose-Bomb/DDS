#include "LCD1602.h"

void LCD1602_Init(void)
{
	MODE_WRITE;
	DISABLE;
	GPIOB->ODR = 0;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);

	SendCom(0x38);
	SendCom(0x0C);
	SendCom(0x06);
	SendCom(0x01);
}

void LCD1602_ShowStr(uint8_t * str)
{
	uint8_t i = 0;
	while (str[i])
	{
		SendData(str[i++]);
	}
}

void SendCom(uint8_t com)
{
	WRITE_COM;

	DATA_OUT = com;
	HAL_Delay(5);
	ENABLE;
	HAL_Delay(5);
	DISABLE;
}

void SendData(uint8_t data)
{
	WRITE_DATA;
	DATA_OUT = data;
	HAL_Delay(5);
	ENABLE;
	HAL_Delay(5);
	DISABLE;
}
