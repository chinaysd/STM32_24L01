#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
#include "sys.h"

//GPIO_Mode_AIN            ģ������
//GPIO_Mode_IN_FLOATING    ��������
//GPIO_Mode_IPD            ��������
//GPIO_Mode_IPU            ��������
//GPIO_Mode_Out_OD         ��©���
//GPIO_Mode_Out_PP         �������
//GPIO_Mode_AF_OD          ���ÿ�©���
//GPIO_Mode_AF_PP          �����������


//�ж����ȼ����ã�ֻ����ռ����������Ӧ
//��ռ0-15 �δ�ʱ��Ĭ����15,0Ҳ��ò��ã��������õķ�ΧΪ��1-14

//����
#define USART1_IRQHandler_NVIC_IRQChannelPreemptionPriority          5//USART1ȫ���ж�
//#define USART2_IRQHandler_NVIC_IRQChannelPreemptionPriority          5//USART2ȫ���ж�
//#define USART3_IRQHandler_NVIC_IRQChannelPreemptionPriority          5//USART3ȫ���ж�
//#define UART4_IRQHandler_NVIC_IRQChannelPreemptionPriority           5//UART4ȫ���ж�
//#define UART5_IRQHandler_NVIC_IRQChannelPreemptionPriority           5//UART5ȫ���ж�
////�ⲿ�ж���
#define EXTI0_IRQHandler_NVIC_IRQChannelPreemptionPriority           2//EXTI��0�ж�
#define EXTI1_IRQHandler_NVIC_IRQChannelPreemptionPriority           2//EXTI��1�ж�
//#define EXTI2_IRQHandler_NVIC_IRQChannelPreemptionPriority           2//EXTI��2�ж�
//#define EXTI3_IRQHandler_NVIC_IRQChannelPreemptionPriority           2//EXTI��3�ж�
//#define EXTI4_IRQHandler_NVIC_IRQChannelPreemptionPriority           2//EXTI��4�ж�
//#define EXTI9_5_IRQHandler_NVIC_IRQChannelPreemptionPriority         2//EXTI��5-9�ж�
//#define EXTI15_10_IRQHandler_NVIC_IRQChannelPreemptionPriority       2//EXTI��10-15�ж�
////��ʱ���жϣ�TIM1,8�߼���ʱ����TIM2,3,4,5ͨ�ö�ʱ����TIM6,7������ʱ����
//#define TIM1_BRK_IRQHandler_NVIC_IRQChannelPreemptionPriority        1//TIM1ɲ���ж�
//#define TIM1_UP_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//TIM1�����ж�
//#define TIM1_TRG_COM_IRQHandler_NVIC_IRQChannelPreemptionPriority    1//TIM1������ͨ���ж� 
//#define TIM1_CC_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//TIM1����Ƚ��ж�
//#define TIM2_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//TIM2ȫ���ж�
//#define TIM3_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//TIM3ȫ���ж�
//#define TIM4_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//TIM4ȫ���ж�
//#define TIM5_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//TIM5ȫ���ж�
//#define TIM6_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//TIM6ȫ���ж�
//#define TIM7_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//TIM7ȫ���ж�
//#define TIM8_BRK_IRQHandler_NVIC_IRQChannelPreemptionPriority        1//TIM8ɲ���ж�
//#define TIM8_UP_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//TIM8�����ж�
//#define TIM8_TRG_COM_IRQHandler_NVIC_IRQChannelPreemptionPriority    1//TIM8������ͨ���ж�
//#define TIM8_CC_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//TIM8����Ƚ��ж�
////DMA�ж�
//#define DMA1_Channel1_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA1ͨ��1ȫ���ж�
//#define DMA1_Channel2_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA1ͨ��2ȫ���ж�
//#define DMA1_Channel3_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA1ͨ��3ȫ���ж�
//#define DMA1_Channel4_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA1ͨ��4ȫ���ж�
//#define DMA1_Channel5_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA1ͨ��5ȫ���ж�
//#define DMA1_Channel6_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA1ͨ��6ȫ���ж�
//#define DMA1_Channel7_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA1ͨ��7ȫ���ж�
//#define DMA2_Channel1_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA2ͨ��1ȫ���ж�
//#define DMA2_Channel2_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA2ͨ��2ȫ���ж�
//#define DMA2_Channel3_IRQHandler_NVIC_IRQChannelPreemptionPriority   1//DMA2ͨ��3ȫ���ж�
//#define DMA2_Channel4_5_IRQHandler_NVIC_IRQChannelPreemptionPriority 1//DMA2ͨ��4ȫ���ж�
////CAN USB
//#define USB_HP_CAN1_TX_IRQHandler_NVIC_IRQChannelPreemptionPriority  1//USB�����ȼ���CAN�����ж� 
//#define CAN1_RX1_IRQHandler_NVIC_IRQChannelPreemptionPriority        1//CAN����1�ж�
//#define USB_LP_CAN1_RX0_IRQHandler_NVIC_IRQChannelPreemptionPriority 1//USB�����ȼ���CAN����0�ж� 
//#define CAN1_SCE_IRQHandler_NVIC_IRQChannelPreemptionPriority        1//CAN SCE�ж� 
//#define USBWakeUp_IRQHandler_NVIC_IRQChannelPreemptionPriority       1//����EXTI�Ĵ�USB���������ж�
////RTCʵʱʱ��
//#define RTC_IRQHandler_NVIC_IRQChannelPreemptionPriority             1//ʵʱʱ��(RTC)ȫ���ж� 
//#define RTCAlarm_IRQHandler_NVIC_IRQChannelPreemptionPriority        1//����EXTI��RTC�����ж�


////������
//���ڿ��Ź�
//#define WWDG_IRQHandler_NVIC_IRQChannelPreemptionPriority            14//���ڿ��Ź�
////SPI  IIC SDIO�ж�
//#define SPI1_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//SPI1ȫ���ж�
//#define SPI2_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//SPI2ȫ���ж�
//#define SPI3_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//SPI3ȫ���ж�
//#define I2C1_EV_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//I2C1�¼��ж�
//#define I2C1_ER_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//I2C1�����ж�
//#define I2C2_EV_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//I2C2�¼��ж�
//#define I2C2_ER_IRQHandler_NVIC_IRQChannelPreemptionPriority         1//I2C2�����ж�
//#define SDIO_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//SDIOȫ���ж�
////ADC
//#define ADC1_2_IRQHandler_NVIC_IRQChannelPreemptionPriority          1//ADC1��ADC2ȫ���ж�
//#define ADC3_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//ADC3ȫ���ж�

//#define FSMC_IRQHandler_NVIC_IRQChannelPreemptionPriority            1//FSMCȫ���ж�
//#define FLASH_IRQHandler_NVIC_IRQChannelPreemptionPriority           1//����ȫ���ж� 
//#define RCC_IRQHandler_NVIC_IRQChannelPreemptionPriority             1//��λ��ʱ�ӿ���(RCC)�ж�
//#define PVD_IRQHandler_NVIC_IRQChannelPreemptionPriority             1//����EXTI�ĵ�Դ��ѹ���(PVD)�ж� 
//#define TAMPER_IRQHandler_NVIC_IRQChannelPreemptionPriority          1//�������ж� 



//λ������,ʵ��51���Ƶ�GPIO���ƹ���,����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO�ڲ���,ֻ�Ե�һ��IO��! ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

//����Ϊ��ຯ��
void WFI_SET(void);		  //ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(u32 addr);	//���ö�ջ��ַ
#define _BIN8(a,b,c,d,e,f,g,h) ((a<<7)+(b<<6)+(c<<5)+(d<<4)+(e<<3)+(f<<2)+(g<<1)+(h<<0))
#endif
