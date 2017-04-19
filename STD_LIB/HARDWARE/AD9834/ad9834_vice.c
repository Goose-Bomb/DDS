
//====================AD9834.c======================//
#include "AD9834.h"

/****************************************************************

函数名称: AD9834_Write_16Bits

功 能: 向AD9834写入16为数据

参 数: data -- 要写入的16位数据

返回值 : 无

*****************************************************************/

void AD9834_Write_16Bits(unsigned int data)

{

    unsigned char i = 0;

    AD9834_SCLK_SET;

    AD9834_FSYNC_CLR;

    for (i = 0; i < 16; i++)
    {
		if (data & 0x8000)
		{
			AD9834_SDATA_SET;
		}
		else
		{
			AD9834_SDATA_CLR;
		}
		AD9834_SCLK_CLR;

		data <<= 1;

		AD9834_SCLK_SET;
    }

    AD9834_FSYNC_SET;
}

/***********************************************************************************

函数名称：AD9834_Select_Wave

功 能：软件为控制，

--------------------------------------------------

IOUT正弦波 ，SIGNBITOUT方波 ，写FREQREG0 ，写PHASE0

ad9834_write_16bit(0x2028) 一次性写FREQREG0

ad9834_write_16bit(0x0038) 单独改写FREQREG0的LSB

ad9834_write_16bit(0x1038) 单独改写FREQREG0的MSB

--------------------------------------------------

IOUT三角波 ，写PHASE0

ad9834_write_16bit(0x2002) 一次性写FREQREG0

ad9834_write_16bit(0x0002) 单独改写FREQREG0的LSB

ad9834_write_16bit(0x1008) 单独改写FREQREG0的MSB

参 数：initdata -- 要输入的命令

返回值 ：无

************************************************************************************/

void AD9834_Select_Wave(unsigned int initdata)

{

    AD9834_FSYNC_SET;

    AD9834_SCLK_SET;

    AD9834_RESET_SET;

    AD9834_RESET_SET;

    AD9834_RESET_CLR;

    AD9834_Write_16Bits(initdata);
}

/****************************************************************

函数名称: Init_AD9834

功 能: 初始化AD9834控制引脚

参 数: 无

返回值 : 无

*****************************************************************/

void Init_AD9834()

{

    RCC->AHB1ENR |= 1 << 2; //使能PORTA时钟
    GPIO_Set(GPIOA, 1 << 0, 1, 0, 2, 0);
    GPIO_Set(GPIOA, 1 << 1, 1, 0, 2, 0);
    GPIO_Set(GPIOA, 1 << 2, 1, 0, 2, 0);
    GPIO_Set(GPIOA, 1 << 3, 1, 0, 2, 0);
    GPIO_Set(GPIOA, 1 << 4, 1, 0, 2, 0);
}

/****************************************************************

函数名称: AD9834_Set_Freq

功 能: 设置频率值

参 数: freq_number -- 要写入的平率寄存器(FREQ_0或FREQ_1)

freq -- 频率值 (Freq_value(value)=Freq_data(data)*FCLK/2^28)

返回值 : 无

*****************************************************************/

void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq)

{

    unsigned long FREQREG = (unsigned long)(268435456.0 / AD9834_SYSTEM_COLCK * freq);

    unsigned int FREQREG_LSB_14BIT = (unsigned int)FREQREG;

    unsigned int FREQREG_MSB_14BIT = (unsigned int)(FREQREG >> 14);

    if (freq_number == FREQ_0)

    {

	FREQREG_LSB_14BIT &= ~(1U << 15);

	FREQREG_LSB_14BIT |= 1 << 14;

	FREQREG_MSB_14BIT &= ~(1U << 15);

	FREQREG_MSB_14BIT |= 1 << 14;
    }

    else

    {

	FREQREG_LSB_14BIT &= ~(1 << 14);

	FREQREG_LSB_14BIT |= 1U << 15;

	FREQREG_MSB_14BIT &= ~(1 << 14);

	FREQREG_MSB_14BIT |= 1U << 15;
    }

    AD9834_Write_16Bits(FREQREG_LSB_14BIT);

    AD9834_Write_16Bits(FREQREG_MSB_14BIT);
}