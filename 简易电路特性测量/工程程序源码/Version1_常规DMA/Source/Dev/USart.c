#include "config.h"
#include "USart.h"


uint8   g_USART1_RxBuf[USART1_RX_BUF_SIZE];//串口接收缓冲区
uint16 	g_USART1_RecPos = 0;//存放当前串口接收数据存放的位置
extern char page;

void UsartInit(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9 ;  //TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10 ;  //RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = USART1_BAUD;  
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);//初始化串口1
	
	//串口1中断初始化
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);//使能串口1
	
  USART_ClearFlag(USART1, USART_FLAG_TC  );//清发送完成标志位
	
}


//为能够调用printf函数从选定的串口打印输出，重定义fputc函数，本例子使用串口1
int fputc(int ch,FILE *f)
{
	
	USART_SendData(USART1, (uint8)ch);
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
	
	return (ch);

}

static void UsartSendByte(USART_TypeDef* USARTx,uint8 ch)
{
	
	USART_SendData(USARTx, (uint8)ch);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)== RESET);
}


void UsartSendString(USART_TypeDef* USARTx,uint8 *str)
{
	uint32 pos = 0;
	while(*(str+pos)!='\0')
	{
		UsartSendByte(USARTx,*(str+pos));
		pos ++;
		
	}

}




//USART1_IRQHandler,串口1中断回调函数
void USART1_IRQHandler(void)
{
	uint8 RecCh;
	if( USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!=RESET )				// 串口接收数据 
	{		
		//Usart1RecTimer = 10;
		RecCh =(uint8)USART_ReceiveData(USART1);
		//g_USART1_RxBuf[g_USART1_RecPos++] =RecCh;

		if(RecCh ==0x01)
		{
			page =1;//频幅特性
		}
		else if (RecCh ==0x00)
		{
			page = 2;//基础测量
		}
		
		
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
	if( USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET ) 				// 串口溢出错误
	{
			USART_ClearFlag(USART1, USART_FLAG_ORE);
	}
}



//unsigned char Usart1_RecProcess(void)
//{
//	if(Usart1RecTimer) return FALSE;
//	if(!g_USART1_RecPos) return FALSE;
//	
//	g_USART1_RxBuf[g_USART1_RecPos]='\0';
//	
//	//收包处理
//	if(strstr((char *)g_USART1_RxBuf,"anlyze")!= NULL)
//	{
//		printf("t1.txt=\"测试中\"\xff\xff\xff");
//	}
//	else if(strstr((char *)g_USART1_RxBuf,"send")!= NULL)
//	{
//			UsartSendString(USART1,"send_test_succeed\r\n");
//	}
//	//memset(g_USART1_RxBuf,0,USART1_RX_BUF_SIZE);
//	g_USART1_RecPos = 0;
//	
//	

//	return TRUE;
//}
