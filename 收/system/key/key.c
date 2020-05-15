
#include "key.h"

volatile u8 Key; 
						    
//������ʼ������
void Key_Scan_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 #if  (Stm32f103zet6_key==1)
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
#endif
#if  (Stm32f103c8t6_key==1)
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;//KEY1-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
#endif

}

//ע��˺�������Ӧ���ȼ�,WK_UP>KEY1>KEY2>KEY3
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//-1��û���κΰ�������
//0��WK_UP���� WK_UP
//1��KEY1����
//2��KEY2����
//3��KEY3���� 
u8 KEY_Scan(u8 mode)
{	 
	static u8 flag=0;
	static s8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������	
#if  (Stm32f103zet6_key==1)
  if(flag==0)
  {
			if(key_up&&(KEY_UP==1||KEY_LEFT==0||KEY_DOWN==0||KEY_RIGHT==0))
			    flag=1;
			else if(KEY_UP==0&&KEY_LEFT==1&&KEY_DOWN==1&&KEY_RIGHT==1)
         key_up=1; 
	}
	else if(flag==1)
	{
		key_up=0;
		flag=0;
		if     (KEY_UP==1)    return KEY_UP_PRES;
		else if(KEY_LEFT==0)  return KEY_LEFT_PRES;
		else if(KEY_DOWN==0)  return KEY_DOWN_PRES;
		else if(KEY_RIGHT==0) return KEY_RIGHT_PRES; 
	}	    
 	return KEY_NO_PRES;// �ް�������
#endif
#if  (Stm32f103c8t6_key==1)
  if(flag==0)
  {
			if(key_up&&(KEY_UP==0||KEY_DOWN==0))
			    flag=1;
			else if(KEY_UP==1&&KEY_DOWN==1)
         key_up=1; 
	}
	else if(flag==1)
	{
		key_up=0;
		flag=0;
		if     (KEY_UP==0)    return KEY_UP_PRES;
		else if(KEY_DOWN==0)  return KEY_DOWN_PRES;
	}	    
 	return KEY_NO_PRES;// �ް�������
#endif
}


