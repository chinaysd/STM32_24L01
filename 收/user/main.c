
#include "sys.h"
#include "delay.h"
#include "usart1.h"
#include "nRF24L01.h"
#include<stdlib.h>   //��������rand����������ͷ�ļ�


int main()
{	
	u8 i,sta,channel,rx_len,ack_len;	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����NVIC�жϷ���4:  16λ��ռ���ȼ�0,15��ò���
	delay_init();

	USART1_Init(115200);
	printf("OK...\r\n\r\n\r\n");
 

    NRF24L01_Init();    		//��ʼ��NRF24L01 

	while(NRF24L01_Check())
	{
		printf("NRF24L01 Error\r\n");
 		delay_ms(1000);
	}
	printf("RX NRF24L01 OK\r\n");
  
	NRF24L01_RX_Mode();
	
	while(1)
	{	  
		sta=NRF24L01_RxPacket(&channel,RX_BUF,&rx_len);
		if(sta&RX_OK)              
		{	
			printf("RX_OK       RX_BUF:");
			for(i=0;i<rx_len;i++)printf("%d,",RX_BUF[i]);printf("\r\n");    //������յ����ݣ���ʾ����
 
			//Ҳ������ʱ���ACK�����յ�ֱ�Ӿͷ����ˣ����õ��յ�������䣬�´η�����
			ack_len=10;                                                     //����ack���ݳ���Ϊ10
			for(i=0;i<ack_len;i++)
				TX_BUF[i]=RX_BUF[i];
			TX_BUF[ack_len-1]=rand()%10;//��ֵack���ݣ�ǰ9���ǽ��յ����ݣ����һ�����
				
			printf("TX_ACK_BUF  TX_BUF:");                                  //��ʾһ��
			for(i=0;i<ack_len;i++)
				printf("%d,",TX_BUF[i]);
			printf("\r\n");
			printf("\r\n");	
			NRF24L01_PacketAckData(TX_BUF,ack_len);//����ACK���ͻ���
		}
	}
}
