#define  MAIN_CONFIG


#include "config.h"
#include "stm32f10x.h"
#include "task.h"
//#define Ri 7500
//#define Ro 1500


char page = 2;

bool puase=1;

int main(void)
{


		SysInit();
		SwitchAD_On();
	
	  GPIO_SetBits(PORT_AD637,PIN_637A);
		GPIO_SetBits(PORT_AD637,PIN_637B);
	
		AD9833_WaveSeting(10,0,SIN_WAVE,0 );//1KHz,	频率寄存器0，正弦波输出 ,初相位0 	
		AD9833_AmpSet(0x11, 0x08);
				
				
					
	while(1)
	{		
							
		
		switch(page){
    case 1  :
       task_data_F();
				
       break; /* 频幅曲线 */
		
    case 2  :
				//AD9833_WaveSeting(1000,0,SIN_WAVE,0 );//1KHz,	频率寄存器0，正弦波输出 ,初相位0
       task_Basic_Print();
				//SysTickDelayMs(500);
       break; /* 简易测量 */
		
		case 3  :
       task_analyze();
				//printf("t1.txt=\"R1 open\"\xff\xff\xff");
		//SysTickDelayMs(1000);
       break; /* 故障分析 */

    default : /* 可选的 */
       break;
		}

	}
	
	
}






