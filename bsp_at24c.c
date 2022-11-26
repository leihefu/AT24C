#include "bsp_at24c.h" 
#include "bsp_i2c.h"
#include "delay.h"
#include <stdio.h>

void at24c_init(void)
{
		i2c_init();
}

uint8_t at24c_read_byte(uint16_t read_addr)
{				  
		uint8_t temp = 0;	
	
		i2c_start();  
		if(EE_TYPE > AT24C16)
		{
				i2c_send_byte(0XA0);	   			//发送写命令
				i2c_wait_ack();
				i2c_send_byte(read_addr >> 8);//发送高地址
				i2c_wait_ack();		 
		}
		else 
				i2c_send_byte(0XA0 + ((read_addr / 256) << 1));   //发送器件地址0XA0,写数据 	 

		i2c_wait_ack(); 
		i2c_send_byte(read_addr %256);   //发送低地址
		i2c_wait_ack();	    
		i2c_start();  	 	   
		i2c_send_byte(0XA1);           		//进入接收模式			   
		i2c_wait_ack();	 
		temp = i2c_read_byte(0);		   
		i2c_stop();												//产生一个停止条件	    
		return temp;
}

void at24c_write_byte(uint16_t write_addr, uint8_t byte)
{				   	  	    																 
    i2c_start();  
		if(EE_TYPE > AT24C16)
		{
				i2c_send_byte(0XA0);	    			//发送写命令
				i2c_wait_ack();
				i2c_send_byte(write_addr >> 8);	//发送高地址
		}
		 else
		{
			i2c_send_byte(0XA0 + ((write_addr / 256) << 1));   //发送器件地址0XA0,写数据 
		}	 
		i2c_wait_ack();	   
		i2c_send_byte(write_addr % 256);   	//发送低地址
		i2c_wait_ack(); 	 										  		   
		i2c_send_byte(byte);     						//发送字节							   
		i2c_wait_ack();  		    	   
		i2c_stop();													//产生一个停止条件 
		delay_ms(10);	 
}

void at24c_read_bytes(uint16_t read_addr, uint8_t *pBuffer, uint16_t lenth)
{
		while(lenth)
		{
				*pBuffer++ = at24c_read_byte(read_addr++);	
				lenth--;
		}
}  
void at24c_write_bytes(uint16_t write_addr, uint8_t *pBuffer, uint16_t lenth)
{
		while(lenth--)
		{
				at24c_write_byte(write_addr, *pBuffer);
				write_addr++;
				pBuffer++;
		}
}
 
void at24c_test(void)
{
		uint8_t test_buf[256];
		uint16_t i;

#if 0
		for(i = 0; i < 256; i++)
		{
				test_buf[i] = i; 
		}
		at24c_write_bytes(0, test_buf, 256);

		printf("写数据完成\r\n");
#else	
		
		at24c_read_bytes(0, test_buf, 256);
	
		printf("读到的数据：\r\n");
		for(i = 0; i < 256; i++)
		{
				printf("%02X ", test_buf[i]);
				if(i % 16 >= 15)
						printf("\r\n");
		}
		
#endif
}


