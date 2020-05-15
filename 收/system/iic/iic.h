#ifndef _IIC_H
#define _IIC_H
#include "sys.h"

//////////////////////////////////////////////////////////
#define IIC_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define IIC_GPIO                  GPIOB
#define IIC_SCL_IO                GPIO_Pin_10 //SCL
#define IIC_SDA_IO                GPIO_Pin_11 //SDA	
#define IIC_SCL                   PBout(10) 
#define IIC_SDA                   PBout(11) 	 
#define READ_SDA                  PBin (11)  //����SDA 
/////////////////////////////////////////////////////////



void IIC_Init(void);        //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  	  //����IICֹͣ�ź�

u8   IIC_Wait_Ack(void); 	  //IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Send_Byte(u8 txd);		        //IIC����һ���ֽ�
u8   IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�

#endif
