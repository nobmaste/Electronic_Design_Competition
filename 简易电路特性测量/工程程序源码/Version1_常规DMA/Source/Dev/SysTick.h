#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#define uint32 unsigned int

#define MAX_TIMER 6 //����ϵͳ�δ�ʱ��ʵ�������ʱ���ĸ���

extern uint32 sysTimer[MAX_TIMER];
#define DelayTimer 							sysTimer[0]  //��ʱ��ʱ��





void SysTickInit(void);//ϵͳ�δ�ʱ����ʼ��
void SysTickDelayMs(uint32 nms);//��ʱnms
uint32 GetRunTime(void);//��ȡϵͳ����ʱ��




#endif


