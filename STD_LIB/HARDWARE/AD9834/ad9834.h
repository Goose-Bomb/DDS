#ifndef __AD9834_H
#define __AD9834_H		
#include "sys.h"	 
#include "stdlib.h"
//一下是对控制引脚的宏定义
#define SCLK    PAout(8)
#define FSYNC   PAout(11)
#define SDA     PCout(9)
#define FSELECT PCout(6)
//函数声明
void AD9834_IO_Init(void);
void write_reg(int data);
void write_ad9834(unsigned long freq);
void FSK_mode(unsigned long freq_low,unsigned long freq_high);
#endif

