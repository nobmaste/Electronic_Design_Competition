#include "config.h"
#include "Gpio.h"


void TaskMark1(void)
{
  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	SysTickDelayMs(500);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	SysTickDelayMs(500);
  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	SysTickDelayMs(500);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	SysTickDelayMs(500);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	SysTickDelayMs(1000);
}

void TaskMark2(void)
{
  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	SysTickDelayMs(100);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	SysTickDelayMs(100);
  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	SysTickDelayMs(100);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	SysTickDelayMs(100);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	SysTickDelayMs(1000);
}


void LEDGpioInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_13 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}

void Switch_Control_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6  | GPIO_Pin_7| GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8);

}

void AD_637_H(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PIN_637B | PIN_637A ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(PORT_AD637,PIN_637A | PIN_637B);

}

void SwitchAD_On(void)
{
	GPIO_SetBits(PORT_AD,PIN_AD);
}
void SwitchAD_Off(void)
{
	GPIO_ResetBits(PORT_AD,PIN_AD);
}

//开关A
void SwitchA_On(void)
{
	GPIO_SetBits(PORT_A,PIN_A);
}
void SwitchA_Off(void)
{
	GPIO_ResetBits(PORT_A,PIN_A);
}
//开关B
void SwitchB_On(void)
{
	GPIO_SetBits(PORT_B,PIN_B);
}
void SwitchB_Off(void)
{
	GPIO_ResetBits(PORT_B,PIN_B);
}
//开关C
void SwitchC_On(void)
{
	GPIO_SetBits(PORT_C,PIN_C);
}
void SwitchC_Off(void)
{
	GPIO_ResetBits(PORT_C,PIN_C);
}
//开关D
void SwitchD_On(void)
{
	GPIO_SetBits(PORT_D,PIN_D);
}
void SwitchD_Off(void)
{
	GPIO_ResetBits(PORT_D,PIN_D);
}

void reset(void)
{
				SwitchAD_On();
				SwitchA_On();
				SysTickDelayMs(5);
				SwitchC_Off();
				SysTickDelayMs(5);
				SwitchD_On();			
				SysTickDelayMs(5);	
				SwitchB_Off();
				SysTickDelayMs(5);
}



