#include "delay.h"

volatile u32 xitong_haomiao;           //2^32/1000/3600/24=49.71��Ḵλ
		   
	   
static   u8  fac_us=0;							     //us��ʱ������	
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//�ж�ʱ��time  =  ( SysTick->LOAD + 1 ) / f			f = AHB��AHB/8	    ��9000-1+1��/9M=1ms
void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8  9M ��������1Ϊ1/9000000��
	fac_us=SystemCoreClock/8000000;				      //9  
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
	SysTick->LOAD=fac_us*1000-1; 						    //ÿ1/1000s�ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK    
}	

   								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;					//LOAD��ֵ	    	 
	ticks=nus*fac_us; 							  //��Ҫ�Ľ�����	  		 
	tcnt=0;
	told=SysTick->VAL;        					//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;		//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;				//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}	
}

void delay_ms(u16 nms)
{	 		  	  
	 delay_us((u32)(nms*1000));					//��ͨ��ʽ��ʱ  
}

void SysTick_Handler(void)
{	
     xitong_haomiao++;
 
}
