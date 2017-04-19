#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "AD9834.h"
int main(void)
{	
  double freq = 30000000;   //设定DDS输出频率为10K
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);			//延时初始化
//	uart_init(72,38400); 	//串口1初始化为38400
  AD9834_IO_Init();   //将与AD9834通信的引脚初始化
  write_ad9834(freq);  //调用此函数就可以控制AD9834的输出频率 频率为freq
	while(1) 
	{		
    delay_ms(1000);
	}											    
}	



