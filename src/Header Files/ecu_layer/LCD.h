/*
 * LCD.h
 *
 * Created: 2/23/2021 4:36:45 PM
 *  Author: Mohamed jehad
 */ 

#ifndef LCD_H_
#define LCD_H_

/*----------------------- Includes -----------------------*/
#include "../mcal_layer/DIO.h"
#include "LCD_config.h"

/*------------------ Macros declarations -----------------*/
#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0e
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06
#if defined four_bits_mode
#define EN 0
#define RS 1
#define RW 2
#define FOUR_BITS 0x28
#elif defined eight_bits_mode
#define EN 0
#define RS 1
#define RW 2
#define EIGHT_BITS 0x38
#endif


/* ------------- Software Interfaces Declarations ----------*/
/*
	Function Name        : LCD_vInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : initialize LCD based of config file
*/
void LCD_vInit(void);



/*
	Function Name        : LCD_vSend_cmd
	Function Returns     : void
	Function Arguments   : char cmd
	Function Description : send command to lcd ex: CLR_SCREEN
*/
void LCD_vSend_cmd(char cmd);

/*
	Function Name        : LCD_vSend_char
	Function Returns     : void
	Function Arguments   : char data
	Function Description : send character to lcd ex: "s"
*/
void LCD_vSend_char(char data);

/*
	Function Name        : LCD_vSend_string
	Function Returns     : void
	Function Arguments   : char *data
	Function Description : send string to lcd ex: "jehad"
*/
void LCD_vSend_string(char *data);

/*
	Function Name        : LCD_clearscreen
	Function Returns     : void
	Function Arguments   : none
	Function Description : clear LCD
*/
void LCD_clearscreen();

/*
	Function Name        : LCD_movecursor
	Function Returns     : void
	Function Arguments   : char row,char coloumn
	Function Description : move cursore of the lcd to specific location
*/
void LCD_movecursor(char row,char coloumn);

#endif /* LCD_H_ */