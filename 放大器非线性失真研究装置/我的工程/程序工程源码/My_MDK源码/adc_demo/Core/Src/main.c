/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "arm_math.h"
#include "arm_const_structs.h"

#include <string.h>
#define RXBUFFERSIZE  256     //最大接收字节数
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t temp[100]={0};
uint16_t res_buffer[FFT_LENGTH];
	/*fft变量定义*/
float fft_inputbuf[FFT_LENGTH*2];	//FFT输入数组
float fft_outputbuf[FFT_LENGTH];	//FFT输出数组
unsigned int i;
arm_cfft_radix4_instance_f32 scfft;//FFT结构体初始化
double THD;
int THD_Tx;

	/*usart变量定义*/
char RxBuffer[RXBUFFERSIZE];   //接收数据
uint8_t aRxBuffer;			//接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0;		//接收缓冲计数
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */	
	HAL_TIM_Base_Start(&htim3);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, 256);
	arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);//初始化scfft结构体，设定FFT相关参数
  while (1)
  {
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*传输完成回调*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc==(&hadc1))
	{
		HAL_ADC_Stop_DMA(&hadc1);
		for(i=0;i<FFT_LENGTH;i++)
		{
			res_buffer[i]=temp[i];
		}
//		for(i=0;i<FFT_LENGTH;i++)
//		{
//			printf("%d\r\n",res_buffer[i]);
//		}

		for(i=0;i<FFT_LENGTH;i++)
		{
			fft_inputbuf[2*i]=res_buffer[i];
			fft_inputbuf[2*i+1]=0;//虚部全部为0
		}
		arm_cfft_radix4_f32(&scfft,fft_inputbuf);	//FFT计算（基4）
		arm_cmplx_mag_f32(fft_inputbuf,fft_outputbuf,FFT_LENGTH);

		/*归一化*/
//		printf("fft_outputbuf[0]:%f\r\n",fft_outputbuf[0]*3.3/4096/1024);
//		for(i=1;i<FFT_LENGTH;i++)
//			{
//				printf("fft_outputbuf[%d]:%f\r\n",i,fft_outputbuf[i]*3.3/4096/512);
//			}
		fft_outputbuf[0]=fft_outputbuf[0]*3.3/4096/1024;
		for(i=1;i<FFT_LENGTH;i++)
			{
				fft_outputbuf[i]=fft_outputbuf[i]*3.3/4096/512;
			}
			/*THD计算*/
			THD = sqrt(fft_outputbuf[20]*fft_outputbuf[20]+fft_outputbuf[31]*fft_outputbuf[31]+fft_outputbuf[41]*fft_outputbuf[41]+fft_outputbuf[51]*fft_outputbuf[51])/fft_outputbuf[10];
			THD_Tx=THD*100000;
			printf("x0.val=%d\xff\xff\xff",THD_Tx);
			//printf("THD: %f\r\n",THD);
			//HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
 
	if(Uart1_Rx_Cnt >= 255)  //溢出判断
	{
		Uart1_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
		//HAL_UART_Transmit(&huart1, (uint8_t *)"数据溢出", 10,0xFFFF); 	        
	}
	else
	{
		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存
		
		if(RxBuffer[Uart1_Rx_Cnt-1] == 0x01)
			{
				Mode1_Off;
				Mode2_Off;
				Mode3_Off;
				Mode4_Off;
				//HAL_Delay(200);
				HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
			}
			if(RxBuffer[Uart1_Rx_Cnt-1] == 0x02)
			{
				Mode1_On;
				Mode2_Off;
				Mode3_Off;
				Mode4_Off;
				//HAL_Delay(200);
				HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
			}
			if(RxBuffer[Uart1_Rx_Cnt-1] == 0x03)
			{
				Mode1_Off;
				Mode2_On;
				Mode3_Off;
				Mode4_Off;
				//HAL_Delay(200);
				HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
			}
			if(RxBuffer[Uart1_Rx_Cnt-1] == 0x04)
			{
				Mode1_Off;
				Mode2_Off;
				Mode3_On;
				Mode4_Off;
				//HAL_Delay(200);
				HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
			}
			if(RxBuffer[Uart1_Rx_Cnt-1] == 0x05)
			{
				Mode1_Off;
				Mode2_Off;
				Mode3_Off;
				Mode4_On;
				//HAL_Delay(200);
				HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
			}
			if(RxBuffer[Uart1_Rx_Cnt-1] == 0x06)
			{
				HAL_ADC_Start_DMA(&hadc1, (uint32_t *)temp, FFT_LENGTH);
			}
			
		if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //判断结束位
		{
//			HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //将收到的信息发送出去
//			
//				
//            while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
			Uart1_Rx_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
		}
	}
	
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //再开启接收中断
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
