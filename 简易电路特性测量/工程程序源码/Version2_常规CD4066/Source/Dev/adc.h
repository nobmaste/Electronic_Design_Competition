#ifndef __ADC_H
#define	__ADC_H


#include "config.h"

uint16 Get_Adc(uint8 ch);
void ADC1_Config(void);
uint16 Get_Adc_Average(uint8 ch);


#endif /* __ADC_H */

