#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#define uint32 unsigned int

#define MAX_TIMER 6 //利用系统滴答定时器实现软件定时器的个数

extern uint32 sysTimer[MAX_TIMER];
#define DelayTimer 							sysTimer[0]  //延时定时器





void SysTickInit(void);//系统滴答定时器初始化
void SysTickDelayMs(uint32 nms);//延时nms
uint32 GetRunTime(void);//获取系统运行时间




#endif


