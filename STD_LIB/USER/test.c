#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "AD9834.h"
int main(void)
{	
  double freq = 30000000;   //�趨DDS���Ƶ��Ϊ10K
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);			//��ʱ��ʼ��
//	uart_init(72,38400); 	//����1��ʼ��Ϊ38400
  AD9834_IO_Init();   //����AD9834ͨ�ŵ����ų�ʼ��
  write_ad9834(freq);  //���ô˺����Ϳ��Կ���AD9834�����Ƶ�� Ƶ��Ϊfreq
	while(1) 
	{		
    delay_ms(1000);
	}											    
}	



