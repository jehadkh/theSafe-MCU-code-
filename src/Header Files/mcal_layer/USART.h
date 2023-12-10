/*
 * USART.h
 *
 * Created: 27/09/2022 04:59:02 م
 *  Author: Jehad kh
 */ 


#ifndef USART_H_
#define USART_H_

/*----------------------- Includes -----------------------*/
#include <util/delay.h>
#include <avr/io.h>
#include "../std_macros.h"

/*------------------ Macros declarations -----------------*/
#define F_CPU 8000000UL

/* ------------- Software Interfaces Declarations ----------*/

/*
	Function Name        : UART_Init
	Function Returns     : void
	Function Arguments   : unsigned long baud
	Function Description : initialize UART with specific baud rate
*/
void UART_Init(unsigned long baud);
/*
	Function Name        : UART_SendData
	Function Returns     : void
	Function Arguments   : char data
	Function Description : send single character using uart
*/
void UART_SendData(char data);
/*
	Function Name        : UART_ReceiveData
	Function Returns     : char
	Function Arguments   : void
	Function Description : recieve single character from uartini
*/
char UART_ReceiveData(void);
/*
	Function Name        : UART_Sendstring
	Function Returns     : void
	Function Arguments   : char *ptr
	Function Description : send string using uart
*/
void UART_Sendstring( char *ptr);



#endif /* USART_H_ */