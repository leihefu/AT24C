#ifndef __BSP_AT24C_H
#define __BSP_AT24C_H

#include "sys.h"   

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	  8191
#define AT24C128	16383
#define AT24C256	32767  
#define EE_TYPE 	AT24C02
					  
void at24c_init(void);
uint8_t at24c_read_byte(uint16_t read_addr);							
void at24c_write_byte(uint16_t write_addr, uint8_t byte);		
void at24c_read_bytes(uint16_t read_addr, uint8_t *pBuffer, uint16_t lenth);
void at24c_write_bytes(uint16_t write_addr, uint8_t *pBuffer, uint16_t lenth); 	
void at24c_test(void);
#endif


