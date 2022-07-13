/************************************
 * 文件名  ：adc.c
 * 描述    ：DMA方式读取ADC值应用函数库         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接： PCA0 - ADC1 
 * 库版本  ：ST3.0.0  

**********************************************************************************/
//D_value  = 3300000/4096*ADC_ConvertedValue/1000;
#include "adc.h"

#define ADC1_DR_Address    ((u32)0x4001244C)

__IO u16 ADC_ConvertedValue[2];  

/*配置采样通道端口 使能GPIO时钟	  设置ADC采样PA0端口信号*/
 void ADC1_GPIO_Config(void)
{ GPIO_InitTypeDef GPIO_InitStructure;    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		    //GPIO设置为模拟输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
}


/*配置ADC1的工作模式为MDA模式  */
 void ADC1_Mode_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能MDA1时钟
	/* DMA channel1 configuration */
  DMA_DeInit(DMA1_Channel1);  //指定DMA通道
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//设置DMA外设地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	//设置DMA内存地址，ADC转换结果直接放入该地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //外设为设置为数据传输的来源
  DMA_InitStructure.DMA_BufferSize = 2;	    //DMA缓冲区设置为1；
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);  //使能DMA通道

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//使能ADC1时钟
     
  /* ADC1 configuration */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //使用独立模式，扫描模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //无需外接触发器
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T4_CC4 ;//触发方式 ADC_ExternalTrigConv_None
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//使用数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 1;  // 只有1个转换通道
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel11 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); //通道1采样周期55.5个时钟周期
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);	 //使能ADC的DMA
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE); //使能ADC1

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //开始转换
}

void ADC1_External_T4_CC4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	TIM_OCInitTypeDef         TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/* Time Base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = 49;          
	TIM_TimeBaseStructure.TIM_Prescaler = 719;       
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/* TIM1 channel1 configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
	TIM_OCInitStructure.TIM_Pulse = 25; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
	TIM_Cmd(TIM4, DISABLE);
}



/*求最大值 n是通道次序*/
//short search (unsigned char n)
//{
//	short i,a=0;
//	a=ADC_ConvertedValue[0];
//	for(i=1;i<256;i++)
//	{
//		 if(a<ADC_ConvertedValue[i])
//			 a=ADC_ConvertedValue[i];
//	}
//	return a;
//}
//		
void DMA1_Channel1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC1))
	 	 {
	 		printf("in %d %d",ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
	    }
			 DMA_ClearFlag(DMA1_FLAG_TC1);
}

/*初始化ADC1 */
void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
	ADC1_External_T4_CC4_Init();
	TIM_Cmd(TIM4, ENABLE);
}




