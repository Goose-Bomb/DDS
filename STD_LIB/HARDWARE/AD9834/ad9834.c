#include "ad9834.h"
#include "delay.h"
/*******AD9834驱动***********/
//调用 AD9834_IO_Init(void);
//     write_ad9834(float freq);
//即可完成基本的频率输出，如要调制或者三角波，方波
//需要改变control寄存器的几个参赛，都在define里
//想要了解，可以参考AD9834的芯片手册
/****************************/
//晶振频率 75M

#define  FSEL    0   //频率寄存器的选择
#define  PIN     0    //选择功能控制的方式
#define  SLEEP   0  // 休眠模式，由两个位组成
#define  MODE    1   //选择三角波或者正弦波

unsigned long FDATA;

//寄存器的值

void AD9834_IO_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟	   	 
	RCC->APB2ENR|=1<<4;    //使能PORTC时钟	
//对PC6\7\8\9  PA[8,11] 进行操作
	GPIOA->CRH&=0XFFFF0FF0;	//PA8 11设置成输推挽输出	  
	GPIOA->CRH|=0X00003003; 			 

	GPIOC->CRL&=0X00FFFFFF;	//PC6 7设置成输出
	GPIOC->CRL|=0X33000000;   
  GPIOC->CRH&=0XFFFFFF00;	//PC8 9设置成输出
	GPIOC->CRH|=0X00000033;   
  
  FSYNC = 1; //初始化
  delay_us(1);
	SCLK= 0;
	delay_us(1);
}

void write_reg(int data)
{
int x = 0 ;
FSYNC = 0; //FSYNC 拉低
SCLK = 1; 
for(x=0;x<16;x++)
	{
	SCLK = 1;
	SDA = ((data<<x)&0x8000)>>15;
	delay_us(1);
	SCLK = 0;
 	delay_us(1);	
	}
SCLK = 1;
delay_us(1);
FSYNC = 1; //FSYNC 拉高
}


//freq :频率值 单位 ：HZ
void write_ad9834(unsigned long freq)
{ 
int control_latch =0;
int FLSB = 0X4000;
int FMSB = 0x4000;
int Platch = 0xC000;
int RESET_DONE = 0x2030; //0x2030使能了方波   0x2012使能了三角波

//先算好寄存器的值
 FDATA = (freq*3.579139);
 control_latch = 0x2110|((FSEL&0X01)<<11)|((PIN&0X01)<<9)|((SLEEP&0X03)<<6)|((MODE&0X01)<<1);
 FLSB = FLSB | (FDATA&0x3fff);
 FMSB = FMSB | ((FDATA&0x0FFFC000)>>14);
//写入寄存器的值
	  write_reg(control_latch);
		delay_us(1);
		write_reg(FLSB);
		delay_us(1);
		write_reg(FMSB);
		delay_us(1);
		write_reg(Platch);
		delay_us(1);
		write_reg(RESET_DONE);	
}

//2FSK调制  //设置完成后，可以通过FSELECT脚选择频率
void FSK_mode(unsigned long freq_low,unsigned long freq_high)
{
 unsigned long FDATA1,FDATA2;
int control_latch =0;
int FLSB = 0X4000; //15：14【0：1】第一个频率寄存器的地址
int FMSB = 0x4000;
int Platch = 0xC000;
int RESET_DONE = 0x2030; //0x2030使能了方波   0x2012使能了三角波
	
	
 //先算好寄存器的值
 FDATA1 = (freq_low*3.579139);
 FDATA2 = (freq_high*3.579139);
	
 control_latch = 0x2100;
 FLSB = FLSB | (FDATA1&0x3fff);
 FMSB = FMSB | ((FDATA1&0xFFFC000)>>14);
//写入第一个寄存器的值
	  write_reg(control_latch);
		delay_us(1);
		write_reg(FLSB);
		delay_us(1);
		write_reg(FMSB);
		delay_us(1);
		write_reg(Platch);
		delay_us(1);
		write_reg(0x2000);	
//写入第二个寄存器的值
   control_latch = 0x2900;
   FLSB = 0X8000; //15：14【1：0】第二个频率寄存器的地址
   FMSB = 0x8000;
   FLSB = FLSB | (FDATA2&0x3fff);
   FMSB = FMSB | ((FDATA2&0xFFFC000)>>14);
	 write_reg(control_latch);
		delay_us(1);
		write_reg(FLSB);
		delay_us(1);
		write_reg(FMSB);
		delay_us(1);
		write_reg(Platch);
		delay_us(1);
		write_reg(0x2800);
		write_reg(0x2A30);//要设置调制功能的关键就在这个控制寄存器的设置
}
