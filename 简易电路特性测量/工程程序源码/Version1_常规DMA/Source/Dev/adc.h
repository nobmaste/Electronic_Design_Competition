#ifndef __ADC_H
#define	__ADC_H


#include "config.h"
void ADC1_Init(void);
short search (unsigned char n);
void DMA1_Channel1_IRQHandler(void);
void ADC1_External_T4_CC4_Init(void);
 void ADC1_Mode_Config(void);
  void ADC1_GPIO_Config(void);




#endif /* __ADC_H */

