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
				i2c_send_byte(0XA0);	   			//����д����
				i2c_wait_ack();
				i2c_send_byte(read_addr >> 8);//���͸ߵ�ַ
				i2c_wait_ack();		 
		}
		else 
				i2c_send_byte(0XA0 + ((read_addr / 256) << 1));   //����������ַ0XA0,д���� 	 

		i2c_wait_ack(); 
		i2c_send_byte(read_addr %256);   //���͵͵�ַ
		i2c_wait_ack();	    
		i2c_start();  	 	   
		i2c_send_byte(0XA1);           		//�������ģʽ			   
		i2c_wait_ack();	 
		temp = i2c_read_byte(0);		   
		i2c_stop();												//����һ��ֹͣ����	    
		return temp;
}

void at24c_write_byte(uint16_t write_addr, uint8_t byte)
{				   	  	    																 
    i2c_start();  
		if(EE_TYPE > AT24C16)
		{
				i2c_send_byte(0XA0);	    			//����д����
				i2c_wait_ack();
				i2c_send_byte(write_addr >> 8);	//���͸ߵ�ַ
		}
		 else
		{
			i2c_send_byte(0XA0 + ((write_addr / 256) << 1));   //����������ַ0XA0,д���� 
		}	 
		i2c_wait_ack();	   
		i2c_send_byte(write_addr % 256);   	//���͵͵�ַ
		i2c_wait_ack(); 	 										  		   
		i2c_send_byte(byte);     						//�����ֽ�							   
		i2c_wait_ack();  		    	   
		i2c_stop();													//����һ��ֹͣ���� 
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

		printf("д�������\r\n");
#else	
		
		at24c_read_bytes(0, test_buf, 256);
	
		printf("���������ݣ�\r\n");
		for(i = 0; i < 256; i++)
		{
				printf("%02X ", test_buf[i]);
				if(i % 16 >= 15)
						printf("\r\n");
		}
		
#endif
}


