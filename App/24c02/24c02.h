#ifndef _24c02_H
#define _24c02_H

#include "public.h"


void at24c02_write_one_byte(u8 addr,u8 dat);//AT24C02ָ����ַд����
void lcd1602_clear_position(u8 x, u8 y);
u8 at24c02_read_one_byte(u8 addr);//AT24C02ָ����ַ������
#endif