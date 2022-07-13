#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"


#define uint8 unsigned char

#define USART1_BAUD         115200
#define USART1_RX_BUF_SIZE  256


void UsartInit(void);
void UsartSendString(USART_TypeDef* USARTx,uint8 *str);//�����ַ���
unsigned char Usart1_RecProcess(void);//����1������


#endif



