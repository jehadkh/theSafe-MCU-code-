/*
 * USART.c
 *
 * Created: 27/09/2022 04:58:49 م
 *  Author: Jehad kh
 */ 

/*----------------------- Includes -----------------------*/
#include <avr/io.h>
#include "../../Header Files/mcal_layer/USART.h"

void UART_Init(unsigned long baud){
	unsigned short UBRR;
	UBRR=(F_CPU/(16*baud))-1;
	UBRRH=(unsigned char)(UBRR>>8);
	UBRRL=(unsigned char)(UBRR);
	//ENABLE TX,RX
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	//8-BIT WORD, MUST WRITE 1 IN URSEL
	UCSRC|=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);		
}

void UART_SendData(char data){
	//wait for transmit buffer to be empty
	while(READ_BIT(UCSRA,UDRE)==0);
	UDR=data;
}

char UART_ReceiveData(void){
	while(READ_BIT(UCSRA,RXC)==0);
	
	return UDR;
}

void UART_Sendstring( char *ptr){
	while(*ptr!=0){
		UART_SendData(*ptr);
		ptr++;
		_delay_ms(100);
	}
}