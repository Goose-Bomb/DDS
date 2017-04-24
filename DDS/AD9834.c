#include "AD9834.h"

union
{
	uint16_t VALUE;		//START WITH DB0 TO DB15 (F~U~C~K THE Datasheet)
	struct {
		_Bool			: 1;
		_Bool MODE		: 1;
		_Bool			: 1;
		_Bool DIV2		: 1;
		_Bool SIGN_PIB	: 1;
		_Bool OPBITEN	: 1;
		_Bool SLEEP12	: 1;
		_Bool SLEEP1	: 1;
		_Bool RESET		: 1;
		_Bool PIN_SW	: 1;
		_Bool PSEL		: 1;
		_Bool FSEL		: 1;
		_Bool HLB		: 1;
		_Bool B28		: 1;
		uint16_t		: 2;
	} BITS;
} Com_Data;

union
{
	uint16_t VALUE;
	struct {	
		uint16_t REG	: 14;
		uint16_t ADDR	: 2;
	} BITS;
} Freq_Data;


void AD9834_Init(void)
{
	RESET1;
	Delay_us(1);

	PSELECT0;
	FSELECT0;
	Delay_us(1);

	FSYNC1;
	Delay_us(1);
	SCLK0;
	Delay_us(1);

	Com_Data.VALUE = 0x0000;

	Com_Data.BITS.B28 = 1;
	Com_Data.BITS.FSEL = 0;
	Com_Data.BITS.PSEL = 0;
	Com_Data.BITS.PIN_SW = 0;
//	Com_Data.BITS.OPBITEN = 1;
//	Com_Data.BITS.SIGN_PIB = 1;
	Com_Data.BITS.MODE = 0;

	WriteReg(Com_Data.VALUE);

	WriteReg(0xC000); //œ‡Œªºƒ¥Ê∆˜÷√¡„
	RESET0;
}


void AD9834_WriteFreq(uint32_t freq, _Bool REG_SW) //HZ
{
	freq *= 3.57914f;

	Freq_Data.BITS.ADDR = 0x01 << REG_SW; //FREQ0 ~ [0 : 1], FREQ1 ~ [1 : 0]

	Freq_Data.BITS.REG = freq & 0x3FFF;
	WriteReg(Freq_Data.VALUE);

	Freq_Data.BITS.REG = (freq & 0x0FFFC000) >> 14;
	WriteReg(Freq_Data.VALUE);
}

void AD9834_SwitchMode(void)
{
	Com_Data.BITS.MODE = !Com_Data.BITS.MODE;
	WriteReg(Com_Data.VALUE);
}

void WriteReg(uint16_t data)
{
	FSYNC0;
	for (uint8_t i = 0; i < 16; ++i)
	{
		SCLK1;
		if (data & 0x8000) SDATA1;
		else SDATA0;
		Delay_us(1);
		SCLK0;
		Delay_us(1);
		data <<= 1;
	}

	SCLK1;
	FSYNC1;
}

void Delay_us(uint32_t us)
{
	uint32_t tickstart = 0;
	uint32_t tickNum = 0;
	uint32_t tickMax = SysTick->LOAD;
	uint32_t delay_usvalue = (SysTick->LOAD / 1000) * us;

	tickstart = SysTick->VAL;

	for (;;)
	{
		uint32_t cur_tick = SysTick->VAL;
		if (cur_tick > tickstart)
		{
			tickNum = tickstart + (tickMax - cur_tick);
		}
		else
		{
			tickNum = tickstart - cur_tick;
		}

		if (tickNum > delay_usvalue)
		{
			break;
		}
	}
}