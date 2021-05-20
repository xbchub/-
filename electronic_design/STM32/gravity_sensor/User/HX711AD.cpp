/**
  ******************************************************************************
  * @file   XH711AD.cpp
  * @brief  The driver of the XH711AD.
  ******************************************************************************
	G1_IN  PA4  DT
	G1_OUT PA5  CLK
	G2_IN  PA6
	G2_OUT PA7
	G3_IN  PB0
	G3_OUT PB1
	
  */
	
	
	
/* Includes ------------------------------------------------------------------*/
#include "HX711AD.h"

float GapValue[3]= {435.11, 440.06, 430.17};

unsigned long Weight_Shiwu_1 = 0;//��ȡ�����Ĵ�С
uint8_t data_1[3]={0x01,0x01,0x01};//���24λADת�����ֵ
long Weight_real_1=0;

unsigned long Weight_Shiwu_2 = 0;//��ȡ�����Ĵ�С
uint8_t data_2[3]={0x01,0x01,0x01};//���24λADת�����ֵ
long Weight_real_2=0;

unsigned long Weight_Shiwu_3 = 0;//��ȡ�����Ĵ�С
uint8_t data_3[3]={0x01,0x01,0x01};//���24λADת�����ֵ
long Weight_real_3=0;


unsigned long HX711_Read_1(void)	//����128
{
		unsigned long count; 
		unsigned char i; 
	
	  	//HX711_DOUT=1; 
			//Delay__hx711_us();���������ڸ�λģ��
	
  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);//ģ��û׼����ʱ����Ƭ����CLK��������͵�ƽ
  	count=0;
	  int ii=0;
		while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0)
			{
				delay_us(1);
				if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0)
				{
					break;
				}			
			}
			
			ii++;
			if(ii>=1000000)
			{
				break;
			}
		}
		delay_us(1);
  	for(i=0;i<24;i++)
	{ 			
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
			delay_us(1);
	  	count=count<<1; 	
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);		
	  	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1)//��������
			{
				count++; 
			}		
	} 
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
	  delay_us(2);
    count=count^0x800000;//��25�������½�����ʱ��ת������
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
		return(count);
}

unsigned long HX711_Read_2(void)	//����128
{
		unsigned long count; 
		unsigned char i; 
	
	  	//HX711_DOUT=1; 
			//Delay__hx711_us();���������ڸ�λģ��
	
  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//ģ��û׼����ʱ����Ƭ����CLK��������͵�ƽ
  	count=0;
	  int ii=0;
		while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0)
			{
				delay_us(1);
				if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0)
				{
					break;
				}			
			}
			
			ii++;
			if(ii>=1000000)
			{
				break;
			}
		}
		delay_us(1);
  	for(i=0;i<24;i++)
	{ 			
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
			delay_us(1);
	  	count=count<<1; 	
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);		
	  	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==1)//��������
			{
				count++; 
			}		
	} 
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
	  delay_us(2);
    count=count^0x800000;//��25�������½�����ʱ��ת������
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
		return(count);
}


unsigned long HX711_Read_3(void)	//����128
{
		unsigned long count; 
		unsigned char i; 
	
	  	//HX711_DOUT=1; 
			//Delay__hx711_us();���������ڸ�λģ��
	
  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);//ģ��û׼����ʱ����Ƭ����CLK��������͵�ƽ
  	count=0;
	  int ii=0;
		while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==0)
			{
				delay_us(1);
				if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==0)
				{
					break;
				}			
			}
			ii++;
			if(ii>=1000000)
			{
				break;
			}
		}
		delay_us(1);
  	for(i=0;i<24;i++)
	{ 			
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
			delay_us(1);
	  	count=count<<1; 	
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);		
	  	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==1)//��������
			{
				count++; 
			}		
	} 
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
	  delay_us(2);
    count=count^0x800000;//��25�������½�����ʱ��ת������
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
		return(count);
}

//====================================================================================================


void Get_Weight_1(void)
{
	Weight_Shiwu_1 = HX711_Read_1();
						  
	data_1[0]=(Weight_Shiwu_1&0xFF0000)>>16;
	data_1[1]=(Weight_Shiwu_1-(data_1[0]<<16))>>8;
	data_1[2]=(Weight_Shiwu_1&0x0000FF);

	if(Weight_Shiwu_1 > 0)			
	{	
		Weight_Shiwu_1 = (unsigned int)((float)Weight_Shiwu_1/GapValue[0]); 	//����ʵ���ʵ������																		
																		
		if(Weight_Shiwu_1 > 5000)		//���ر���
		{
			//Flag_ERROR = 1;	
		}
		else
		{
			//Flag_ERROR = 0;
		}
	}
	else
	{
		Weight_Shiwu_1 = 0;
		//Flag_ERROR = 1;				//���ر���
	}
}


void Get_Weight_2(void)
{
	Weight_Shiwu_2 = HX711_Read_2();
						  
	data_1[0]=(Weight_Shiwu_2&0xFF0000)>>16;
	data_1[1]=(Weight_Shiwu_2-(data_2[0]<<16))>>8;
	data_1[2]=(Weight_Shiwu_2&0x0000FF);

	if(Weight_Shiwu_2 > 0)			
	{	
		Weight_Shiwu_2 = (unsigned int)((float)Weight_Shiwu_2/GapValue[1]); 	//����ʵ���ʵ������																		
																		
		if(Weight_Shiwu_2 > 5000)		//���ر���
		{
			//Flag_ERROR = 1;	
		}
		else
		{
			//Flag_ERROR = 0;
		}
	}
	else
	{
		Weight_Shiwu_2 = 0;
		//Flag_ERROR = 1;				//���ر���
	}
}

void Get_Weight_3(void)
{
	Weight_Shiwu_3 = HX711_Read_3();
						  
	data_1[0]=(Weight_Shiwu_3&0xFF0000)>>16;
	data_1[1]=(Weight_Shiwu_3-(data_3[0]<<16))>>8;
	data_1[2]=(Weight_Shiwu_3&0x0000FF);

	if(Weight_Shiwu_3 > 0)			
	{	
		Weight_Shiwu_3 = (unsigned int)((float)Weight_Shiwu_3/GapValue[2]); 	//����ʵ���ʵ������																		
																		
		if(Weight_Shiwu_3 > 5000)		//���ر���
		{
			//Flag_ERROR = 1;	
		}
		else
		{
			//Flag_ERROR = 0;
		}
	}
	else
	{
		Weight_Shiwu_3 = 0;
		//Flag_ERROR = 1;				//���ر���
	}
}

void delay_us(uint8_t value)
{
	uint8_t i;
	for(i=value;i>0;i--);
}
