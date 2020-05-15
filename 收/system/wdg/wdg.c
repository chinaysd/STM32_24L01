#include "wdg.h"



//独立看门狗   //Tout=[2^prer)×rlr]/10000s  prer:3位0-8 rlr:12位1-4096
void IWDG_Init(u8 prer,u16 rlr)    //IWDG_Init(5,625);//Tout=(2^6*625)/10000s=2s
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	IWDG_SetPrescaler(prer);                       //设置IWDG预分频值:设置IWDG预分频值为64
	IWDG_SetReload(rlr);                           //设置IWDG重装载值
	IWDG_ReloadCounter();                          //按照IWDG重装载寄存器的值重装载IWDG计数器
	IWDG_Enable();                                 //使能IWDG
}
//喂独立看门狗
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();	//重载计数值									   
}




/*//一般不用

//保存WWDG计数器的设置值,默认为最大. 
u8 WWDG_CNT=0x7f; 
//初始化窗口看门狗 	
//tr   :T[6:0],计数器值 0-127
//wr   :W[5:0],窗口值 0-64
//fprer:分频系数（WDGTB）,仅最低2位有效 
//Fwwdg=(4096*2^fprer)*(上：tr-wr   下：tr-0x3f)/PCLK1(36Mhz)

void WWDG_Init(u8 tr,u8 wr,u32 fprer)//Fwwdg=(4096*2^fprer)*(上：tr-wr   下：tr-0x3f)/PCLK1(36Mhz)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //WWDG时钟使能
	WWDG_CNT=tr&WWDG_CNT;                                 //初始化WWDG_CNT.   
	WWDG_SetPrescaler(fprer);                             //设置IWDG预分频值
	WWDG_SetWindowValue(wr);                              //设置窗口值
	WWDG_Enable(WWDG_CNT);	                              //使能看门狗 ,设置 counter .                  
	WWDG_ClearFlag();                                     //清除提前唤醒中断标志位 
	WWDG_NVIC_Init();                                     //初始化窗口看门狗 NVIC
	WWDG_EnableIT();                                      //开启窗口看门狗中断
} 
//重设置WWDG计数器的值
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);//使能看门狗 ,	设置 counter .	 
}

void WWDG_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = WWDG_IRQHandler_NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	 
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
//窗口看门狗中断服务程序
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(WWDG_CNT);	  //当禁掉此句后,窗口看门狗将产生复位
	WWDG_ClearFlag();	  //清除提前唤醒中断标志位
}

*/
