#ifndef _CONTROL_H
#define _CONTROL_H

#include "main.h"
#include "dma.h"
#include "gpio.h"
#include "stdio.h"
#include "adc.h"

/*����ʧ��*/
#define Mode1_On  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#define Mode1_Off HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
/*�ײ�ʧ��*/
#define Mode2_On  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
#define Mode2_Off HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
/*˫��ʧ��*/
#define Mode3_On  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
#define Mode3_Off HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
/*��Խʧ��*/
#define Mode4_On  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
#define Mode4_Off HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

extern uint16_t temp[100];

#endif

