#ifndef I2C_H_
#define I2C_H_
/* ------------- Software Interfaces Declarations ----------*/
/*
	Function Name        : I2C_Master_init
	Function Returns     : void
	Function Arguments   : unsigned long SCL_Clock
	Function Description :initialize I2C
*/
void I2C_Master_init(unsigned long SCL_Clock);
void I2C_start(void);
void I2C_write_address(unsigned char address);
void I2C_write_data(unsigned char data);
void I2C_stop(void);
void I2C_set_address(unsigned char address);
unsigned char I2C_slave_read(void);
unsigned char I2C_Master_read(void);
#endif /* I2C_H_ */