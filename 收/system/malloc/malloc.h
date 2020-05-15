#ifndef __MALLOC_H
#define __MALLOC_H
#include "sys.h"

#define SRAMEX    0		//�ⲿ�ڴ�� 
 

//�ڴ�����趨.
#if SRAMEX==0
		#define MEM_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
		#define MEM_MAX_SIZE			  10*1024  						//�������ڴ� 10K
		#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//�ڴ���С
#else	
		#define MEM_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
		#define MEM_MAX_SIZE			  960 *1024           //�������ڴ�960K(963.76)    x*1024+x*1024/32*2=1024*1024 x=963.765
		#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//�ڴ���С 
#endif	




#ifndef NULL
#define NULL 0
#endif	

//�ڴ���������
struct _m_mallco_dev
{
	void (*init)(void);				//��ʼ��
	u8 (*perused)(void);		  	//�ڴ�ʹ����
	u8 	*membase;					//�ڴ�� 
	u16 *memmap; 					//�ڴ����״̬��
	u8  memrdy; 					//�ڴ�����Ƿ����
};
extern struct _m_mallco_dev mallco_dev;	//��mallco.c���涨��

void mymemset(void *s,u8 c,u32 count);	//�����ڴ�
void mymemcpy(void *des,void *src,u32 n);//�����ڴ�     
void mem_init(void);					 //�ڴ�����ʼ������(��/�ڲ�����)
u32 mem_malloc(u32 size);		 		//�ڴ����(�ڲ�����)
u8 mem_free(u32 offset);		 		//�ڴ��ͷ�(�ڲ�����)
u8 mem_perused(void);					//���ڴ�ʹ����(��/�ڲ�����) 


//�û����ú���
void myfree(void *ptr);  				//�ڴ��ͷ�(�ⲿ����)
void *mymalloc(u32 size);				//�ڴ����(�ⲿ����)
void *myrealloc(void *ptr,u32 size);	//���·����ڴ�(�ⲿ����)
#if SRAMEX==1
		void FSMC_SRAM_Init(void);
		void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 NumHalfwordToWrite);
		void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 NumHalfwordToRead);
		void fsmc_sram_test_write(u8 data,u32 addr);
		u8 fsmc_sram_test_read(u32 addr);
#endif	


#endif













