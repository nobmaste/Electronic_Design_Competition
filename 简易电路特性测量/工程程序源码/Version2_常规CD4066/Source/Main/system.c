#include "config.h"
#include "system.h"


void CpuInit(void)
{
	//CPU相关设置
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择第2组中断优先级，即2位主优先级，2位次优先级
	
}

void SysInit(void)
{
	
	CpuInit();//配置系统信息
	
	
	//外设驱动初始化
	SysTickInit();//系统滴答定时器初始化
	LEDGpioInit();//LED指示灯初始化
	UsartInit();//串口初始化
	Switch_Control_Init();//模拟开关初始化
	AD_637_H();
	AD9833_Init_GPIO();//9833初始化
	ADC1_Config();
}








