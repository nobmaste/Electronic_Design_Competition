#include "config.h"
#include "system.h"


void CpuInit(void)
{
	//CPU�������
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ѡ���2���ж����ȼ�����2λ�����ȼ���2λ�����ȼ�
	
}

void SysInit(void)
{
	
	CpuInit();//����ϵͳ��Ϣ
	
	
	//����������ʼ��
	SysTickInit();//ϵͳ�δ�ʱ����ʼ��
	LEDGpioInit();//LEDָʾ�Ƴ�ʼ��
	UsartInit();//���ڳ�ʼ��
	Switch_Control_Init();//ģ�⿪�س�ʼ��
	AD_637_H();
	AD9833_Init_GPIO();//9833��ʼ��
	ADC1_Config();
}








