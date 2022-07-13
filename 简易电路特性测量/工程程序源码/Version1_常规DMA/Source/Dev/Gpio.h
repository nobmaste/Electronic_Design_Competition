#ifndef __GPIO_H__
#define __GPIO_H__

//模拟引脚开关定义
#define PORT_A	GPIOA
#define PIN_A	GPIO_Pin_4

#define PORT_B	GPIOA
#define PIN_B	GPIO_Pin_5

#define PORT_C	GPIOA
#define PIN_C	GPIO_Pin_6

#define PORT_D	GPIOA
#define PIN_D	GPIO_Pin_7

void TaskMark1(void); //Led控制代码
void TaskMark2(void); //Led控制代码
void LEDGpioInit(void);

void Switch_Control_Init(void);
//开关控制
void SwitchA_On(void);
void SwitchA_Off(void);

void SwitchB_On(void);
void SwitchB_Off(void);

void SwitchC_On(void);
void SwitchC_Off(void);

void SwitchD_On(void);
void SwitchD_Off(void);

#endif



