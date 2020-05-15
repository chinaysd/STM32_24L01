#include "iic.h"


void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(IIC_RCC_APB2Periph_GPIOx,ENABLE);
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_IO|IIC_SDA_IO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(IIC_GPIO,&GPIO_InitStructure);
  GPIO_SetBits(IIC_GPIO,IIC_SCL|IIC_SDA); 	
}

void IIC_SDA_OUT()
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_IO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(IIC_GPIO,&GPIO_InitStructure);
}


void IIC_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_IO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(IIC_GPIO,&GPIO_InitStructure);
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	IIC_SDA_OUT();
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0; 
	delay_us(4);
	IIC_SCL=0; 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	IIC_SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
	IIC_SCL=1; 
 	delay_us(4);
	IIC_SDA=1;
	delay_us(4);							   	
}

//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	IIC_SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	IIC_SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}			

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��   0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_IN(); 
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;   
	return 0;  
} 

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��  0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
		u8 t;   
		IIC_SDA_OUT(); 	    
		IIC_SCL=0;
		for(t=0;t<8;t++)
		{              
				if((txd&0x80)>0)
				IIC_SDA=1;
				else
				IIC_SDA=0;
				txd<<=1; 	  
				delay_us(2);   //��TEA5767��������ʱ���Ǳ����
				IIC_SCL=1;
				delay_us(2); 
				IIC_SCL=0;	
				delay_us(2);
		}	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
		u8 i,receive=0;
		IIC_SDA_IN();
		for(i=0;i<8;i++ )
		{
				IIC_SCL=0; 
				delay_us(2);
				IIC_SCL=1;
				receive<<=1;
				if(READ_SDA)receive++;   
				delay_us(1); 
		}					 
		if(ack==0)
			IIC_NAck();
		else
			IIC_Ack(); 
		return receive;
}
