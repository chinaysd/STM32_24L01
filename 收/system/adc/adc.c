#include "adc.h"


u16 AD_Value[CH_NUM];
float AD_float_v[CH_NUM];
//PA0--ADC_Channel_0  PA1--ADC_Channel_1  PA2--ADC_Channel_2   PA3--ADC_Channel_3   PA4--ADC_Channel_4   PA5--ADC_Channel_5   
//PA6--ADC_Channel_6  PA7--ADC_Channel_7  PB0--ADC_Channel_8   PB1--ADC_Channel_9    
//ADC_Channel_TempSensor �ڲ��¶�--ADC_Channel_16   �ڲ��ο���ѹ ADC_Channel_Vrefint--ADC_Channel_17
//temperate=(1.43-(float)adcx*(3.3/4096))/0.0043+25;	//ת��Ϊ�¶�ֵ 


//����Ŀ����8·�����һ·�ڲ���ѹ����
//PA0--ADC_Channel_0  PA1--ADC_Channel_1  PA4--ADC_Channel_4   PA5--ADC_Channel_5   
//PA6--ADC_Channel_6  PA7--ADC_Channel_7  PB0--ADC_Channel_8   PB1--ADC_Channel_9
//�ڲ��ο���ѹ ADC_Channel_Vrefint--ADC_Channel_17
void  Adc_Init(void)
{ 	
			GPIO_InitTypeDef  GPIO_InitStructure;
			ADC_InitTypeDef  ADC_InitStructure; 
	    DMA_InitTypeDef DMA_InitStructure;
	    NVIC_InitTypeDef NVIC_InitStructure;
	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB| RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE );   

			RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M    
																		 
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                
			GPIO_Init(GPIOA, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
			ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
			ADC_InitStructure.ADC_ScanConvMode =ENABLE;        //���ŵ�ɨ��ģʽ
			ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //ģ��ת������������ת��ģʽ
			ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   //�ⲿ����ת���ر�
			ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
			ADC_InitStructure.ADC_NbrOfChannel = CH_NUM;        //�˴���7���ŵ����ɿ���Ϊ1~16��
			ADC_Init(ADC1, &ADC_InitStructure);        //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���


			//ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����
			ADC_RegularChannelConfig(ADC1, ADC_Channel_0,1, ADC_SampleTime_239Cycles5 );                
			ADC_RegularChannelConfig(ADC1, ADC_Channel_1,2, ADC_SampleTime_239Cycles5 );
			ADC_RegularChannelConfig(ADC1, ADC_Channel_4,3, ADC_SampleTime_239Cycles5 );                
			ADC_RegularChannelConfig(ADC1, ADC_Channel_5,4, ADC_SampleTime_239Cycles5 );
			ADC_RegularChannelConfig(ADC1, ADC_Channel_6,5, ADC_SampleTime_239Cycles5 );
		  ADC_RegularChannelConfig(ADC1, ADC_Channel_7,6, ADC_SampleTime_239Cycles5 );                
			ADC_RegularChannelConfig(ADC1, ADC_Channel_8,7, ADC_SampleTime_239Cycles5 );
			ADC_RegularChannelConfig(ADC1, ADC_Channel_9,8, ADC_SampleTime_239Cycles5 );
			ADC_TempSensorVrefintCmd(ENABLE); //�����ڲ��¶ȴ��������ο���ѹͨ��
			ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint,9, ADC_SampleTime_239Cycles5 );

			//����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
			ADC_DMACmd(ADC1, ENABLE);       //ʹ��ADC1��DMA����         
			ADC_Cmd(ADC1, ENABLE);           //ʹ��ָ����ADC1
			ADC_ResetCalibration(ADC1);        //��λָ����ADC1��У׼�Ĵ���
			while(ADC_GetResetCalibrationStatus(ADC1));        //��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�
			ADC_StartCalibration(ADC1);                //��ʼָ��ADC1��У׼״̬
			while(ADC_GetCalibrationStatus(ADC1));                //��ȡָ��ADC1��У׼����,����״̬��ȴ�
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);	  //�������ADת��
     /* Enable the DMA Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;   
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // ���ȼ�����
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);		
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
			DMA_DeInit(DMA1_Channel1);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
			DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)ADC1_DR_Address;  //DMA����ADC����ַ
			DMA_InitStructure.DMA_MemoryBaseAddr =    (u32)&AD_Value;        //DMA�ڴ����ַ
			DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
			DMA_InitStructure.DMA_BufferSize = CH_NUM;  //DMAͨ����DMA��������ݵ�Ԫ��С
			DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
			DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
			DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
			DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
			DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //ѭ������ģʽ
			DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ� 
			DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
			DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
			DMA_ClearFlag(DMA1_Channel1_IRQn);                                 // ���DMA���б�־ 
			DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
			DMA_Cmd(DMA1_Channel1, ENABLE);           //����DMAͨ��
}				  


void DMA1_Channel1_IRQHandler(void)
{
		u8 i=0;
    if(DMA_GetITStatus(DMA1_FLAG_TC1))
    {
            DMA_ClearFlag(DMA1_FLAG_GL1);         // �����־
            for(i=0;i<CH_NUM;i++)
							 AD_float_v[i]=(float)AD_Value[i]/(float)AD_Value[8]*1.2;
			     //����˲�����
    }
}

//���ADCֵ
u16 Get_Adc(u8 ch)  //ch:ͨ��ֵ 0~CH_NUM-1 
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

