#include "config.h"
#include "SysTick.h"

uint32 sysTimer[MAX_TIMER];//�����ʱ������
static uint32 g_iRunTimer = 0;//����ϵͳȫ������ʱ��



void SysTickInit(void)
{
	uchar i;
	for(i = 0;i < MAX_TIMER; i++)
		sysTimer[i] = 0;
	
	SysTick_Config(72000000/1000);//ÿ��1ms��һ��ϵͳ�δ��ж���Ӧ��������Ƶ72M
	
}

void SysTick_Handler(void) 
{
	uint8 i;
	for(i = 0;i < MAX_TIMER; i++)
	  if(sysTimer[i])
			sysTimer[i]--;
		
	if(g_iRunTimer++ == 0XFFFFFFFF)//���ɼ�50������
		 g_iRunTimer = 0;
	
}


void SysTickDelayMs(uint32 nms)
{
	CPU_INT_ENABLE();//��CPU�ж�
	
	DelayTimer = nms;
	while(DelayTimer);//�ȴ���ʱʱ�����
}


uint32 GetRunTime(void)
{
	
	uint32 RunTime;
	
	CPU_INT_DISABLE();//���ж�
	RunTime = g_iRunTimer;
	CPU_INT_ENABLE();//���ж�
	
	return RunTime;
}


