#include "lcd.h"
#include <stdio.h>

#if (LCD1602_4OR8_DATA_INTERFACE==0)//8?LCD
void lcd1602_write_cmd(u8 cmd)
{
	LCD1602_RS=0;
	LCD1602_RW=0;
	LCD1602_E=0;
	LCD1602_DATAPORT=cmd;
	delay_ms(1);
	LCD1602_E=1;
	delay_ms(1);
	LCD1602_E=0;
}
#else	

#endif


#if (LCD1602_4OR8_DATA_INTERFACE==0)//8?LCD
void lcd1602_write_data(u8 dat) 
{
	LCD1602_RS=1;
	LCD1602_RW=0;
	LCD1602_E=0;
	LCD1602_DATAPORT=dat;
	delay_ms(1);
	LCD1602_E=1;
	delay_ms(1);
	LCD1602_E=0;
}
#else

#endif


#if (LCD1602_4OR8_DATA_INTERFACE==0)//8?LCD
void lcd1602_init(void)
{
	lcd1602_write_cmd(0x38);

	lcd1602_write_cmd(0x0c);
	lcd1602_write_cmd(0x06);
	lcd1602_write_cmd(0x01);	
	
}
#else

#endif

void lcd1602_clear(void)
{
	lcd1602_write_cmd(0x01);	
}
void LCD_PutChar(char Data){
        LCD1602_RS=1;
        lcd1602_write_cmd(Data);
        LCD1602_RS=0 ;
}
void LCD_Puts(char *s){
        while (*s){
                LCD_PutChar(*s);
                s++;
        }
}

void lcd1602_show_string(u8 x,u8 y,u8 *str)
{
	u8 i=0;

	if(y>1||x>15)return;

	if(y<1)	
	{	
		while(*str!='\0')
		{
			if(i<16-x)
			{
				lcd1602_write_cmd(0x80+i+x);
			}
			else
			{
				lcd1602_write_cmd(0x40+0x80+i+x-16);
			}
			lcd1602_write_data(*str);
			str++;
			i++;	
		}	
	}
	else	
	{
		while(*str!='\0')
		{
			if(i<16-x) 
			{
				lcd1602_write_cmd(0x80+0x40+i+x);	
			}
			else
			{
				lcd1602_write_cmd(0x80+i+x-16);	
			}
			lcd1602_write_data(*str);
			str++;
			i++;	
		}	
	}				
}
void int_to_str(int num, char *str) {
    sprintf(str, "%d", num);
}


void lcd1602_show_integer(u8 x, u8 y, int num) {
    char num_str[10];  
    int_to_str(num, num_str);
    lcd1602_show_string(x, y, num_str);
}

