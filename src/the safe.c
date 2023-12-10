/*
 * timer.c
 *
 * Created: 9/25/2019 7:22:07 PM
 *  Author: Mohamed jeahd
 */ 

 /*----------------------- Includes -----------------------*/
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "Header Files/ecu_layer/LCD.h"
#include "Header Files/mcal_layer/EEPROM_driver.h"
#include "Header Files/mcal_layer/USART.h"
#include "Header Files/mcal_layer/timer.h"
#include "Header Files/mcal_layer/DIO.h"

/*------------------ Macros declarations -----------------*/
#define  EEPROM_STATUS_LOCATION    0x20     //safe closed =0x08  
#define  EEPROM_PASSWORD_LOCATION1 0x21
#define  EEPROM_PASSWORD_LOCATION2 0x22
#define  EEPROM_PASSWORD_LOCATION3 0x23
#define  EEPROM_PASSWORD_LOCATION4 0x24
#define MAX_TRIES 3
//volatile char  x =0;

char arr[4];

int main(void)
{
	//initialize UART 
	UART_Init(9600);
	char value;
	//this flag will be used to check if user entered right pass correctly
	char flag=0;
	//this var will be used for forLoop counter
	unsigned char i=0;
	char tries=MAX_TRIES;
	LCD_vInit();
	sei();
	
	//if EEPROM_STATUS_LOCATION not equal 0x08 then the safe is not closed Forever
	if(EEPROM_read(EEPROM_STATUS_LOCATION)!=0x08){
		UART_Sendstring("/Choose Operation:");
		LCD_vSend_string("Choose Operation:");
		
		char value2=UART_ReceiveData();
		//if user send 0 this means SET the password
		if(value2=='0')
		{
			LCD_clearscreen();
			LCD_vSend_string("Set Pass:");
			UART_Sendstring("/Set Pass:");
			for (i=0;i<=3;i++)
			{
				value=UART_ReceiveData();
				
				LCD_vSend_char(value);
				_delay_ms(500);
				LCD_movecursor(1,10+i);
				LCD_vSend_char('*');
				_delay_ms(500);
				EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,value);
			}
			//this status means that user set the pass
			EEPROM_write(EEPROM_STATUS_LOCATION,0x01);
		}
	
		//if user sends value 2 so it means Change the password
		if(value2=='2'){
			
			char flag2=0;
			//this will loop until user change pass correctly
			while(flag2==0){
				LCD_clearscreen();
				
				LCD_vSend_string("Old Pass :");
				for (i=0;i<=3;i++)
				{
			    	arr[i]=UART_ReceiveData();
					LCD_vSend_char(arr[i]);
					_delay_ms(250);
					LCD_movecursor(1,11+i);
					LCD_vSend_char('*');
					_delay_ms(250);
				}
				//this check if user entered right pass	
				if(EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_read(EEPROM_PASSWORD_LOCATION4)==arr[3])
				{
					LCD_clearscreen();
					LCD_vSend_string("Right Password");
					UART_Sendstring("/Right Password");
					_delay_ms(1000);
					LCD_clearscreen();
					LCD_vSend_string("New Pass:");
					UART_Sendstring("/New Pass:");
						
					for (i=0;i<=3;i++)
					{
						value=UART_ReceiveData();
						
						LCD_vSend_char(value);
						_delay_ms(500);
						LCD_movecursor(1,10+i);
						LCD_vSend_char('*');
						_delay_ms(500);
						EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,value);
						EEPROM_write(EEPROM_STATUS_LOCATION,0x01);
						//flag2 = 1 means that user changed pass correctly
						flag2=1;
					}
				}
				
			}
		}
		//loop until user enter the correct pass			
		while(flag==0)
		{
			LCD_clearscreen();
			LCD_vSend_string("Enter Pass:");
			UART_Sendstring("/Enter Pass:");
			for (i=0;i<=3;i++)
			{
					arr[i]=UART_ReceiveData();
				LCD_vSend_char(arr[i]);
				_delay_ms(500);
				LCD_movecursor(1,12+i);
				LCD_vSend_char('*');
				_delay_ms(500);
			}		
			
			if(EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_read(EEPROM_PASSWORD_LOCATION4)==arr[3])
			{
				LCD_clearscreen();
				LCD_vSend_string("Right Passowrd");
				UART_Sendstring("/Right Password");
				_delay_ms(500);
				LCD_movecursor(2,1);
				LCD_vSend_string("Safe Opened");
				UART_Sendstring("/Safe Opened");
				
				
				//timer1_wave_fastPWM(8);
				//_delay_ms(2000);
				
				//servo motor open safe door
				timer1_wave_fastPWM(16);
				_delay_ms(1000);
				flag=1;	
				
			}	
			else
			{
				tries=tries-1;
				if (tries>0)
				{
					LCD_clearscreen();
					LCD_vSend_string("Wrong Passowrd");
					UART_Sendstring("/Wrong Password");
					
					LCD_clearscreen();
					LCD_vSend_string("Tries Left:");
					

					LCD_vSend_char(tries+48);
					UART_Sendstring("/Tries Left:"+(tries+48));
					_delay_ms(500);
				
				}
				//the code will reach here if user entered wrong pass many times so
				//safe will be closed forever
				else
				{
					LCD_clearscreen();
					LCD_vSend_string("Wrong Passowrd");
					UART_Sendstring("/Wrong Password");
					
					
					LCD_movecursor(2,1);
					_delay_ms(500);
					LCD_vSend_string("Safe Closed");
					UART_Sendstring(" /Safe Closed");
					//write 0x08 in status location which means safe closed forever
					EEPROM_write(EEPROM_STATUS_LOCATION,0x08);
					//DIO_vsetPINDir('C',4,1);
					DDRC|=(1<<4);
					//DIO_vsetPINDir();
					//buzzer
					SET_BIT(PORTC,4);
					_delay_ms(3000);
					CLR_BIT(PORTC,4);
					flag=1;
				}
			}
		}
	}
	else {
		LCD_clearscreen();
		LCD_vSend_string("Safe Closed");
		UART_Sendstring("/Safe Closed");
		char var=UART_ReceiveData();
		if(var=='0'){
			EEPROM_write(EEPROM_STATUS_LOCATION,0x00);
		}
	}			
}
//-----FUTURE WORK--
//to complete here we will use RFID with the safe
/*
ISR(TWI_vect){
 LCD_clearscreen();
		LCD_vSend_string("Right Passowrd");
		UART_Sendstring("/Right Password");
		_delay_ms(500);
		LCD_movecursor(2,1);
		LCD_vSend_string("Safe Opened");
		UART_Sendstring("/Safe Opened");
		
		
		//timer1_wave_fastPWM(8);
		//_delay_ms(2000);
		
		//servo motor open safe door
		timer1_wave_fastPWM(16);
		_delay_ms(1000);
		
}
*/
