#ifndef _lcd1602_H
#define _lcd1602_H

#include "public.h"

#define LCD1602_4OR8_DATA_INTERFACE	0	

//??Y???
sbit LCD1602_RS=P2^6;
sbit LCD1602_RW=P2^5;
sbit LCD1602_E=P2^7; 
#define LCD1602_DATAPORT P0



void lcd1602_init(void);
void lcd1602_clear(void);
void lcd1602_show_string(u8 x,u8 y,u8 *str);
void lcd1602_write_cmd(u8 cmd);
void lcd1602_write_data(u8 dat);
void int_to_str(int num, char *str) ;
void lcd1602_show_integer(u8 x, u8 y, int num);

#endif