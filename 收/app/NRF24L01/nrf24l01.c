#include "nrf24l01.h"
#include "spi1.h"

u8 TX_ADDRESS[TX_ADR_WIDTH]={0x13,0x14,0x52,0x05,0x21}; //�Լ��ĵ�ַ
u8 RX_ADDRESS[RX_ADR_WIDTH]={0x13,0x14,0x52,0x05,0x20}; //�Է��ĵ�ַ
u8 RX_BUF[TX_PLOAD_WIDTH];//���ջ���
u8 TX_BUF[TX_PLOAD_WIDTH];//���ͻ���
 
u8 RX_ACK_NUM=0;  //����ACK����
u8 RX_ACK_BUF[32];//����ACK����	

//��ʼ��24L01��IO��
void NRF24L01_IO_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;			   


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx_CE_CSN, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = NRF24L01_CE_IO|NRF24L01_CSN_IO;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
	GPIO_Init(GPIO_TypeDef_GPIOx_CE_CSN, &GPIO_InitStructure);
	GPIO_ResetBits(GPIO_TypeDef_GPIOx_CE_CSN,NRF24L01_CE_IO|NRF24L01_CSN_IO);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx_IRQ, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = NRF24L01_IRQ_IO;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_TypeDef_GPIOx_IRQ, &GPIO_InitStructure);
	GPIO_ResetBits(GPIO_TypeDef_GPIOx_IRQ,NRF24L01_IRQ_IO);
						 		 
	NRF24L01_SPIx_Init();    		//��ʼ��SPI	 
	SPI_Cmd(NRF24L01_SPIx, DISABLE); // SPI���費ʹ��

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//SPI����
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//ʱ�����յ�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//���ݲ����ڵ�1��ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź�����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(NRF24L01_SPIx, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	SPI_Cmd(NRF24L01_SPIx, ENABLE); //ʹ��SPI����

	NRF24L01_SPIx_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��

	NRF24L01_CE=0; 			//ʹ��24L01
	NRF24L01_CSN=1;			//SPIƬѡȡ��   	 		 	 
}

//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i; 	 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}
 
void NRF24L01_Init(void)
{
	NRF24L01_IO_Init();
	NRF24L01_CE=0;	  

	NRF24L01_Write_Reg(NRF_WRITE_REG +EN_AA     , 0x01);
	NRF24L01_Write_Reg(NRF_WRITE_REG +EN_RXADDR , 0x01);
	NRF24L01_Write_Reg(NRF_WRITE_REG +SETUP_RETR, 0x1a);
	NRF24L01_Write_Reg(NRF_WRITE_REG +RF_CH     , 0x05);
	NRF24L01_Write_Reg(NRF_WRITE_REG +RF_SETUP  , 0x0f);

	NRF24L01_CE = 1;
	delay_ms(10);
}
 
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ���,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
	NRF24L01_Write_Buf(NRF_WRITE_REG + TX_ADDR,   (u8*)TX_ADDRESS, TX_ADR_WIDTH);//д�Լ���ַ�����Զ�����뷢��֡,��ʹ��ACK
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0,(u8*)TX_ADDRESS, TX_ADR_WIDTH);//����Ӧ��ʱͨ��0���ڽ���ACK RX_ADDR_P0�����TX_ADDR��ͬ����һ������У���10ҳ����ģʽ�ڶ���  TX_ADDR�Ĵ�������
															                   	 //�ر�Ӧ��ʱ����ʡ��  
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);
	//�����ǿ���ACK����
	NRF24L01_Write_Reg(FLUSH_TX, 0xff);
	NRF24L01_Write_Reg(FLUSH_RX, 0xff);
	NRF24L01_ReadWriteByte(0x50);
	NRF24L01_ReadWriteByte(0x73);
	NRF24L01_Write_Reg(NRF_WRITE_REG + DYNPD, 0x01);
	NRF24L01_Write_Reg(NRF_WRITE_REG + FEATURE, 0x07);
	NRF24L01_CE=1;
}

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ���,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//д�Է��ڵ��ַ����ƥ��ָ����ַ����,��ʹ��ACK
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);
	//�����ǿ���ACK����
	NRF24L01_Write_Reg(FLUSH_TX, 0xff);
	NRF24L01_Write_Reg(FLUSH_RX, 0xff);
	NRF24L01_ReadWriteByte(0x50);
	NRF24L01_ReadWriteByte(0x73);
	NRF24L01_Write_Reg(NRF_WRITE_REG + DYNPD, 0x01);
	NRF24L01_Write_Reg(NRF_WRITE_REG + FEATURE, 0x07);
	NRF24L01_CE = 1; //CEΪ��,�������ģʽ 
}			
 
u8   NRF24L01_TxPacket(u8*txbuf,u8 txlen,u8*rxbuf,u8 *rxlen)//�������ݰ������ڷ���ģʽ2/4
{
	u8 sta;
	u8 return_temp=0;
	NRF24L01_CE=0;	
	NRF24L01_Write_Buf(NRF_WRITE_REG | TX_ADDR,   (u8*) TX_ADDRESS, RX_ADR_WIDTH);	//д�Լ���ַ�����Զ�����뷢��֡,��ʹ��ACK
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (u8*)TX_ADDRESS, TX_ADR_WIDTH);  //����Ӧ��ʱͨ��0���ڽ���ACK RX_ADDR_P0�����TX_ADDR��ͬ����һ������У���10ҳ����ģʽ�ڶ���  TX_ADDR�Ĵ�������
															                   	    //�ر�Ӧ��ʱ����ʡ��  
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,txlen); 
	NRF24L01_CE=1;	
	delay_us(10);
	while(NRF24L01_IRQ!=0){};//�ȴ��������
	sta=NRF24L01_Read_Reg(NRF_READ_REG+STATUS);//��״̬�Ĵ���
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta);//?���RX_DS�жϱ�־
	//printf("sta:%x\r\n",sta);

	if(sta&TX_OK)
	{        
		//printf("TX_OK\r\n");
		return_temp|=TX_OK;
	}
	if(sta&MAX_TX)
	{
		printf("MAX_TX\r\n");

		return_temp|=MAX_TX;		 
	}
	if(sta&RX_OK)
	{
		//printf("RX_ACK_OK\r\n");
		*rxlen=NRF24L01_Read_Reg(NRF_READ_REG+R_RX_PL_WID);
		if(*rxlen<33)
		{
			NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,*rxlen);//��RXFIFO��������
		}
		else
		{
			*rxlen=0;
			NRF24L01_Write_Reg(FLUSH_RX, 0xff);
		}	
		return_temp|=RX_OK;
	}
	return return_temp;
}

void NRF24L01_PacketAckData(u8*pBuf,u8 len)//�������ݰ������ڷ���ģʽ2/4
{
	NRF24L01_CE=0;	
	NRF24L01_Write_Buf(W_ACK_PAYLOAD,pBuf,len);
	NRF24L01_CE=1;	
}

u8 NRF24L01_RxPacket(u8 *channel,u8 *rxbuf,u8 *rxlen)
{
	u8 sta;
	sta=NRF24L01_Read_Reg(NRF_READ_REG+STATUS);//��״̬�Ĵ���
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta);//���RX_DS�жϱ�־
	//printf("sta:%x\r\n",sta);
	if(sta&RX_OK)
	{
		//printf("RX_OK\r\n");
		*channel = (sta & 0x0e) >> 1;
		*rxlen=NRF24L01_Read_Reg(NRF_READ_REG+R_RX_PL_WID);
		if(*rxlen<33)
		{
			NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,*rxlen);//��RXFIFO��������
		}
		else
		{
			*rxlen=0;
			NRF24L01_Write_Reg(FLUSH_RX, 0xff);
		}
		return RX_OK;
	}
	return 0; 
}








u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
	NRF24L01_CSN=0;                 //ʹ��SPI����
	status =NRF24L01_ReadWriteByte(reg);//���ͼĴ����� 
	NRF24L01_ReadWriteByte(value);      //д��Ĵ�����ֵ
	NRF24L01_CSN=1;                 //��ֹSPI����	   
	return(status);       			//����״ֵ̬
}

u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
	NRF24L01_CSN = 0;          //ʹ��SPI����		
	NRF24L01_ReadWriteByte(reg);   //���ͼĴ�����
	reg_val=NRF24L01_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
	NRF24L01_CSN = 1;          //��ֹSPI����		    
	return(reg_val);           //����״ֵ̬
}	

u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
	NRF24L01_CSN = 0;           //ʹ��SPI����
	status=NRF24L01_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=NRF24L01_ReadWriteByte(0XFF);//��������
	NRF24L01_CSN=1;       //�ر�SPI����
	return status;        //���ض�����״ֵ̬
}

u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
	NRF24L01_CSN = 0;          //ʹ��SPI����
	status = NRF24L01_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
	for(u8_ctr=0; u8_ctr<len; u8_ctr++)NRF24L01_ReadWriteByte(*pBuf++); //д������	 
	NRF24L01_CSN = 1;       //�ر�SPI����
	return status;          //���ض�����״ֵ̬
}		
