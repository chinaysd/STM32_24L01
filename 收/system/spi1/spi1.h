#ifndef __spi1_H
#define __spi1_H
#include "sys.h"


//sck   PA5
//miso  PA6
//mosi  PA7

void SPI1_Init(void);			 //��ʼ��SPI��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8   SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

