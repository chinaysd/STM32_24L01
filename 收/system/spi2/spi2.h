#ifndef __SPI2_H
#define __SPI2_H
#include "sys.h"


//sck   PB13
//miso  PB14
//mosi  PB15
 				  	    													  
void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8   SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

