/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2020-05-17 21:19:31
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-01 13:24:16
 * @FilePath: \FFTc:\Users\malem\Desktop\����\��·���Բ���\���\STM32_Proj\Source\Main\main.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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

	
//		AD9833_WaveSeting(1000,0,SIN_WAVE,0 );//1KHz,	Ƶ�ʼĴ���0�����Ҳ���� ,����λ0 	
//		AD9833_AmpSet(0x11, 0x05);
	printf("load\r\n");
	while(1)
	{		
//		for(int i =0;i<256;i++)
	
		printf(" %d\r\n",ADC_ConvertedValue[1]);
		
		
//		if(page==1)//Ƶ������
//		{
//		}
//		else if(page ==2)//��������
//		{
//			unsigned char Ri,Ro,Au;
//			
//			SwitchA_Off();
//			SwitchC_Off();
//			SwitchB_On();
//		}
		

	}
	
}






