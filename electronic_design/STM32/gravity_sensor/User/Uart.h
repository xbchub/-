/**
  ******************************************************************************
  * @file   Uart.h
  * @brief  The driver of the Uart.
  ******************************************************************************
  */
	
#ifndef _USART_H_
#define _USART_H_

#ifdef  __cplusplus
extern "C"{
#endif
	
#include "stm32f1xx.h"


extern uint8_t rx_buffer[100];//��������
extern volatile uint8_t rx_len ; //���յ������ݳ���
extern volatile uint8_t recv_end_flag ; //���ս�����־λ

void MY_UART_Init(void);
void My_printf1(char* fmt,...);
void My_printf2(char* fmt,...);

	#ifdef  __cplusplus
}
#endif
#endif



