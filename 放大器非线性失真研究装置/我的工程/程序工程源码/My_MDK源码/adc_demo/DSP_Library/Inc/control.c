#include "control.h"
/*无明显失真*/
void No_Distortion(void)
{
	Mode1_Off;
	Mode2_Off;
	Mode3_Off;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*顶部失真*/
void Top_Distortion(void)
{
	Mode1_On;
	Mode2_Off;
	Mode3_Off;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*底部失真*/
void Base_Distortion(void)
{
	Mode1_Off;
	Mode2_On;
	Mode3_Off;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*双向失真*/
void Both_Distortion(void)
{
	Mode1_Off;
	Mode2_Off;
	Mode3_On;
	Mode4_Off;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}
/*交越失真*/
void Cross_Distortion(void)
{
	Mode1_Off;
	Mode2_Off;
	Mode3_Off;
	Mode4_On;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
}

