/************************************************************************************
						
*************************************************************************************/
#include "HX711.h"
#include "delay.h"

u32 SENSOR_Buffer[3];

u32 Weight_Maopi[3];

s32 Weight_Shiwu[3];
u8 Flag_Error = 0;

volatile unsigned long * PIN_SCK[3] = {&SENSOR0_SCK, &SENSOR1_SCK, &SENSOR2_SCK};
volatile unsigned long * PIN_DOUT[3] = {&SENSOR0_DOUT, &SENSOR1_DOUT, &SENSOR2_DOUT};


//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
float GapValue[3] = {106.5, 106.5, 106.5};


void Init_HX711pin(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PORTB

		//SENSOR0_SCK
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	
		//SENSOR0_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		//SENSOR1_SCK
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 // �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	
		//SENSOR1_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		//SENSOR2_SCK
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	
		//SENSOR2_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
		GPIO_SetBits(GPIOB,GPIO_Pin_0);					//��ʼ������Ϊ0
		GPIO_SetBits(GPIOB,GPIO_Pin_2);					//��ʼ������Ϊ0
		GPIO_SetBits(GPIOB,GPIO_Pin_4);					//��ʼ������Ϊ0
}



//****************************************************
//��ȡHX711
//****************************************************
u32 Sensor_Read(volatile unsigned long *SENSOR_SCK,
								volatile unsigned long *SENSOR_DOUT)
{
	unsigned long count; 
	unsigned char i;
  *SENSOR_DOUT=1; 
	delay_us(1);
  *SENSOR_SCK=0; 
  count=0; 
  while(*SENSOR_DOUT); 
  for(i=0;i<24;i++)
	{ 
	  *SENSOR_SCK=1; 
	  count=count<<1; 
		delay_us(1);
		*SENSOR_SCK=0; 
	  if(*SENSOR_DOUT)
			count++; 
		delay_us(1);
	} 
 	*SENSOR_SCK=1; 
  count=count^0x800000;//��25�������½�����ʱ��ת������
	delay_us(1);
	*SENSOR_SCK=0;  
	return(count);
}


//****************************************************
//��ȡëƤ����
//****************************************************
void Get_Maopi(void)
{
	u8 i;
	for (i=0; i<3; i++)
	{
		Weight_Maopi[i] = Sensor_Read(PIN_SCK[i], PIN_DOUT[i]);
	}
} 

//****************************************************
//����
//****************************************************
void Get_Weight(void)
{
	u8 i;
	for (i=0; i<3; i++)
	{
		Weight_Maopi[i] = Sensor_Read(PIN_SCK[i], PIN_DOUT[i]);
		if (SENSOR_Buffer[i] > Weight_Maopi[i])
		{
			Weight_Shiwu[i] = SENSOR_Buffer[i];
			Weight_Shiwu[i] = Weight_Shiwu[i] - Weight_Maopi[i];				//��ȡʵ���AD������ֵ��
	
			Weight_Shiwu[i] = (s32)((float)Weight_Shiwu[i]/GapValue[i]); 	//����ʵ���ʵ������
																		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
																		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
																		//������Գ���������ƫСʱ����С����ֵ��
		}
	}
}
