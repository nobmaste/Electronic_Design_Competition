/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2020-05-17 21:19:31
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-01 13:24:16
 * @FilePath: \FFTc:\Users\malem\Desktop\任务\电路特性测量\暑假\STM32_Proj\Source\Main\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#define  MAIN_CONFIG


#include "config.h"
#include "stm32f10x.h"

char page = 2;
unsigned char mode=1 ;

short val0,val1,val2,val3;

extern __IO u16 ADC_ConvertedValue[2];	 
int main(void)
{

	
	SysInit();

	
//		AD9833_WaveSeting(1000,0,SIN_WAVE,0 );//1KHz,	频率寄存器0，正弦波输出 ,初相位0 	
//		AD9833_AmpSet(0x11, 0x05);
	printf("load\r\n");
	while(1)
	{		
//		for(int i =0;i<256;i++)
	
		printf(" %d\r\n",ADC_ConvertedValue[1]);
		
		
//		if(page==1)//频幅特性
//		{
//		}
//		else if(page ==2)//基础测量
//		{
//			unsigned char Ri,Ro,Au;
//			
//			SwitchA_Off();
//			SwitchC_Off();
//			SwitchB_On();
//		}
		

	}
	
}






