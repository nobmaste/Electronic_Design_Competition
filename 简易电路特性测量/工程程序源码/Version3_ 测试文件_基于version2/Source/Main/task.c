#include "task.h"
#include "config.h"
/*-----sampling-------*/
short dir_V;
float Zi,Zo,Au;
short val_B,val_C,val_D;
float Iin,Iou;
/*----analyze_mark-----*/
short mark_dc,mark_ac;
/*---------------------*/
static int hz=1000;
bool flag=0;

bool Au_falg=0;


extern char page;

void task_Basic_Print(void)
{
		
//静态
			SwitchAD_Off();
			SwitchA_On();
			SwitchC_Off();
			SwitchD_On();				
			SwitchB_Off();
			SysTickDelayMs(400);
			
			dir_V=Get_Adc_Average(2);
			//printf("n9.val=%d\xff\xff\xff",(int)(3300000/4096*dir_V/1000));
			printf("n9.val=%d\xff\xff\xff",dir_V);
			printf("t14.txt=\"直流工作\"\xff\xff\xff");
			
		
		//交流
				/*开关复位*/
				reset();//A、D on,B、C off
			SysTickDelayMs(500);
			dir_V=Get_Adc_Average(2);
			//printf("n6.val=%d\xff\xff\xff",(int)(3300000/4096*dir_V/1000));
			printf("n6.val=%d\xff\xff\xff",dir_V);
			
			/*输入阻抗分析*/
				
				/*B点采样*/
				SwitchA_Off();
				SwitchB_On();
				SysTickDelayMs(400);//300
				val_B = Get_Adc_Average(0);
				if(page == 2)
				printf("n3.val=%d\xff\xff\xff",val_B);//输入电压B
				//printf("n3.val=%d\xff\xff\xff",(int)(3300000/4096*val_B/1000));//输入电压B	
				
				/*C点采样*/
				SysTickDelayMs(10);
				SwitchB_Off();
				SwitchC_On();
				printf("t14.txt=\"交流输入采样\"\xff\xff\xff");
				SysTickDelayMs(300);//280
				val_C = Get_Adc_Average(0);
				if(page == 2)
				printf("n5.val=%d\xff\xff\xff",val_C);//输入电压C
				//printf("n5.val=%d\xff\xff\xff",(int)(3300000/4096*val_C/1000));//输入电压C
				
								
				Zi=((float)val_C/(val_B-val_C))*Ri;//输入阻抗
				printf("n0.val=%d\xff\xff\xff",(int)Zi);//输入阻抗	
				
				SysTickDelayMs(10);
				SwitchA_On();
				//SwitchC_Off();
				SysTickDelayMs(120);
				val_C = Get_Adc_Average(0);
				SysTickDelayMs(10);
				
			/*输出阻抗分析*/
				SwitchC_Off();
				SysTickDelayMs(220);				
				
				val_D=Get_Adc_Average(1);
				Iou = (3.3/4096*(float)(val_D))/Ro;
				if(page == 2)
					//printf("n8.val=%d\xff\xff\xff",(int)(3300000/4096*val_D/1000));//采样输出电压
					printf("n8.val=%d\xff\xff\xff",val_D);//采样输出电压
				
				SysTickDelayMs(10);	
				SwitchD_Off();
				SysTickDelayMs(200);
				val_D=Get_Adc_Average(1);
				SysTickDelayMs(50);	

				if(page == 2)
					//printf("n4.val=%d\xff\xff\xff",(int)(3300000/4096*val_D/1000));//输出电压
					printf("n4.val=%d\xff\xff\xff",val_D);//输出电压
				
				Zo=(3300000/4096*(float)(val_D)/1000)/Iou/1000;//输出阻抗
				printf("t14.txt=\"交流输出采样工作\"\xff\xff\xff");
			/*增益*/
				Au=((float)(val_D/Vi_AcOrigin));		
					
				printf("n1.val=%d\xff\xff\xff",(int)Zo);//输出阻抗				
				
				printf("n2.val=%d\xff\xff\xff",(int)Au);	//增益
	}

	
	void sampling(void)
{
			//静态
			SwitchAD_Off();
			SwitchA_On();
			SwitchC_Off();
			SwitchD_On();				
			SwitchB_Off();
			SysTickDelayMs(400);
			
			dir_V=Get_Adc_Average(2);
			printf("n1.val=%d\xff\xff\xff",dir_V);
			mark_dc=dir_V;
		
		//交流
				/*开关复位*/
				reset();//A、D on,B、C off
			SysTickDelayMs(500);
			dir_V=Get_Adc_Average(2);
			mark_ac=dir_V;
			printf("n2.val=%d\xff\xff\xff",dir_V);
			
			/*输入阻抗分析*/
				
				/*B点采样*/
				SwitchA_Off();
				SwitchB_On();
				SysTickDelayMs(300);
				val_B = Get_Adc_Average(0);
				
				/*C点采样*/
				SysTickDelayMs(10);
				SwitchB_Off();
				SwitchC_On();
				SysTickDelayMs(280);
				val_C = Get_Adc_Average(0);
				
								
				Zi=((float)val_C/(val_B-val_C))*Ri;//输入阻抗
				printf("n0.val=%d\xff\xff\xff",(int)Zi);//输入阻抗	
				
				SysTickDelayMs(10);
				SwitchA_On();
				//SwitchC_Off();
				SysTickDelayMs(120);
				val_C = Get_Adc_Average(0);
				SysTickDelayMs(10);
				
			/*输出阻抗分析*/
				SwitchC_Off();
				SysTickDelayMs(220);				
				
				val_D=Get_Adc_Average(1);
				Iou = (3.3/4096*(float)(val_D))/Ro;
				SysTickDelayMs(10);	
				SwitchD_Off();
				SysTickDelayMs(200);
				val_D=Get_Adc_Average(1);
				SysTickDelayMs(50);	

				
			/*增益*/
				Au=((float)(val_D/Vi_AcOrigin));		
								
				
				printf("n3.val=%d\xff\xff\xff",(int)Au);	//增益
					
}

void sampling_F(void)
{
	
		     //交流
				/*开关复位*/
				reset();//A、D on,B、C off

				SwitchD_Off();
				SysTickDelayMs(600);
				val_D=Get_Adc_Average(1);
				SysTickDelayMs(10);	
				
			/*增益*/
				Au=((float)(val_D/Vi_AcOrigin));		
			
}
	
	void task_data_F(void)
	{		
			/*执行逻辑*/
			if(flag==1)
			{
				printf("cle 2,0\xff\xff\xff");
				hz=1000;
				AD9833_WaveSeting(hz,0,SIN_WAVE,0 );
				SysTickDelayMs(200);				
				flag=0;
			}
			if(hz >= 300000)
			{
				flag=0;
				AD9833_WaveSeting(hz,0,SIN_WAVE,0 );
				return;
			}
			/*-------------------*/
			/*采样*/
				sampling_F();
			/*-------------------*/
			
			
				printf("n1.val=%d\xff\xff\xff",(int)Au);//增益
				
				printf("add 2,0,%d\xff\xff\xff",(int)Au);
				printf("n2.val=%d\xff\xff\xff",hz);//频率
			
				//printf("n0.val=%d\xff\xff\xff",val_D);
			
				hz+=1000;
				AD9833_WaveSeting(hz,0,SIN_WAVE,0 );//1KHz,	频率寄存器0，正弦波输出 ,初相位0 	
				SysTickDelayMs(1000);
				
				if(Au < 67 && Au_falg == 0 )
				{					
					Au_falg = 1;
					printf("n0.val=%d\xff\xff\xff",hz);
				}
				
			}
	


			
void task_analyze(void)
{
	sampling();
	/*----------数据类型定义---------*/
	 typedef struct {
                  
				 char order;
		 
         long Ri_st;//输入阻抗
         long Vd_st;//直流输出
         long Vc_st;//交流输出
				 long Au_st;//增益


    }malfunction;
		
	 unsigned char error_info =15;//错误码
		

    /*-----------------------------存储----------------------------------*/		
    /*-----------------序号、输入阻抗、直流输出、交流输出、增益------------*/
    malfunction contrast_data[14]={
    /*电阻断路*/
    {0, 13305, 3570, 3600, 5},//R1*
    {1, 1350,  1131, 1130, 26},//R2*
    {2, 1250,  0,		 0,		 4},//R3*
    {3, 10700, 3570, 3579, 5},//R4*

    /*电阻短路*/
    {4, 12000,	3360, 3366, 5},//R1
    {5, 1280,		3570, 3577, 5},//R2*
    {6, 2518,		3600, 3615, 5},//R3*
    {7, 1277,		0,		0,	  32},//R4*

    /*电容断路*/
    {8, 200000, 2216, 2220, 5},//C1*
    {9, 10000,  2220, 2220, 5},//C2*
    {10,2440,   2220, 2640, 5},//C3*

    /*电容加倍*/
    {11,2400,		2220, 2500, 88},//C1
    {12,2400,   2220, 2600, 88},//C2
    {13,2400,   2220, 2400, 88}//C3
    };
		/*-----------------------------END---------------------------------*/
		/*-------------------------记录采样数据-----------------------------*/			
    malfunction samp_val={14,Zi,mark_dc,mark_ac,Au};
	

		/*-----------------------------决策树---------------------------------*/	
		//branch_1,判断直流工作电位
		/*-----------------------------电容---------------------------------*/	
		if((samp_val.Vd_st <=2300 ) && (samp_val.Vd_st >= 2100)){   //电容问题
			//branch_2,输入阻抗判断,开路问题
				if((samp_val.Ri_st >= 180000) && (samp_val.Ri_st <= 210000)){
						error_info = 8;  //C1_open
				}
				else if((samp_val.Ri_st >= 9000) && (samp_val.Ri_st <= 11000 ) ){
						error_info = 9;  //C2_open
				}
				else if((samp_val.Ri_st >= 2300) && (samp_val.Ri_st <= 2600) ){
						error_info = 10; //C3_open
				}
				
				
				
		}
		/*-----------------------------电阻---------------------------------*/	
		else{  //电阻问题
			//branch_2,交流电位
			  if(samp_val.Vc_st<10){
					//branch_3,输入阻抗
						if((samp_val.Ri_st<1360) && (samp_val.Ri_st>1200)){
							if(samp_val.Au_st>25 && samp_val.Au_st < 36){
								error_info = 7;
							}
							else{
								error_info = 2;
							}
						}		
				}
				
			//branch_2,交流电位
				else if((samp_val.Vc_st>1050 )&& (samp_val.Vc_st<1200)){
						error_info = 1;
				}
			//branch_2,交流电位
			  else if((samp_val.Vc_st>3200) && (samp_val.Vc_st<3700)){
					//branch_3,输入阻抗
						if((samp_val.Ri_st>1100 )&& (samp_val.Ri_st<1300)){
						error_info = 5;
					}
						else if((samp_val.Ri_st>2450) && (samp_val.Ri_st< 2580)){
						error_info = 6;
					}	
						else if((samp_val.Ri_st>10000 )&& (samp_val.Ri_st<11500)){
						error_info = 3;
					}
						else if((samp_val.Ri_st>13000) && (samp_val.Ri_st< 13600)){
						error_info = 0;
					}		
//error_info=25;							
				}
				
		}
		printf("n4.val=%d\xff\xff\xff",error_info);
		
		/*-----------------------------结果打印---------------------------------*/	
		switch(error_info){
			case 0:
				printf("t1.txt=\"R1 open\"\xff\xff\xff");
			break;
			
			case 1:
				printf("t1.txt=\"R2 open\"\xff\xff\xff");
			break;
			
			case 2:
				printf("t1.txt=\"R3 open\"\xff\xff\xff");
			break;
			
			case 3:
				printf("t1.txt=\"R4 open\"\xff\xff\xff");
			break;
			
			case 4:
				printf("t1.txt=\"R1 short\"\xff\xff\xff");
			break;
			
			case 5:
				printf("t1.txt=\"R2 short\"\xff\xff\xff");
			break;
			
			case 6:
				printf("t1.txt=\"R3 short\"\xff\xff\xff");
			break;
			
			case 7:
				printf("t1.txt=\"R4 short\"\xff\xff\xff");
			break;
			
			case 8:
				printf("t1.txt=\"C1 open\"\xff\xff\xff");
			break;
			
			case 9:
				printf("t1.txt=\"C2 open\"\xff\xff\xff");
			break;
			
			case 10:
				printf("t1.txt=\"C3 open\"\xff\xff\xff");
			break;
			
			case 11:
				printf("t1.txt=\"C1 double\"\xff\xff\xff");
			break;
			
			case 12:
				printf("t1.txt=\"C2 double\"\xff\xff\xff");
			break;
			
			case 13:
				printf("t1.txt=\"C3 double\"\xff\xff\xff");
			break;
			
			case 14:
				printf("t1.txt=\"failed\"\xff\xff\xff");
			break;
			
			 default : /* 可选的 */
       break;
		}
				
}
		

