#include "control.h"
/*������ʧ��*/
void No_Distortion(void)
{
	Mode1_Off;
	Mode2_Off;
	Mode3_Off;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*����ʧ��*/
void Top_Distortion(void)
{
	Mode1_On;
	Mode2_Off;
	Mode3_Off;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*�ײ�ʧ��*/
void Base_Distortion(void)
{
	Mode1_Off;
	Mode2_On;
	Mode3_Off;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*˫��ʧ��*/
void Both_Distortion(void)
{
	Mode1_Off;
	Mode2_Off;
	Mode3_On;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*��Խʧ��*/
void Cross_Distortion(void)
{
	Mode1_Off;
	Mode2_Off;
	Mode3_Off;
	Mode4_On;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}

