#ifndef __BT05_H
#define __BT05_H

#include "sys.h"

//����ģ��GPIO��ز�����һ���װ
//**********************************************************************************
#define RCC_STATE_EN  RCC_APB2Periph_GPIOC
//#define RCC_EN		RCC_APB2Periph_GPIOC
#define STATE_Pin GPIO_Pin_13 
#define EN_Pin GPIO_Pin_14
//**********************************************************************************

#define BT05_EN  	    PCout(14) 	//��������EN�ź�
#define BT05_STATE  	PCin(13)		//��������״̬�ź�


u8 BT05_Init(void);
u8 BT05_Get_Role(void);
u8 BT05_Set_Cmd(u8* atstr);
void BT05_Role_Print(void);
void BT05_Sta_Print(void);
#endif