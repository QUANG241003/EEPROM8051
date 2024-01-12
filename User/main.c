#include "public.h"
#include "24c02.h"
#include "key.h"
#include "smg.h"
#include "lcd.h"
#include <stdio.h>

#define EEPROM_ADDRESS	0	
#define GPIO_KEY P1

unsigned char KeyValue;
unsigned char KeyState;
unsigned char check;
unsigned char check1;
void Delay10ms();
void KeyDown();

void main() {
    unsigned char key_temp = 0;
     char input[6];
     char chuoi1[6];
    unsigned char status = 0;
    unsigned char i, j;
	unsigned b=0;
	int stt=0;
    lcd1602_init();
	at24c02_write_one_byte(EEPROM_ADDRESS 	 ,2);
	at24c02_write_one_byte(EEPROM_ADDRESS + 1,2);
	at24c02_write_one_byte(EEPROM_ADDRESS + 2,2);
	at24c02_write_one_byte(EEPROM_ADDRESS + 3,2);
	at24c02_write_one_byte(EEPROM_ADDRESS + 4,2);
	at24c02_write_one_byte(EEPROM_ADDRESS + 5,2);
    lcd1602_show_string(0, 0, "Enter password");

    while (1) {
        check = 0;
        KeyDown();

        if (KeyState) {
            unsigned char a = KeyValue + '0';	
            status++;
            if (status == 1) {
                lcd1602_clear();
            }
            delay_ms(100);
            input[j] = KeyValue;
            KeyState = 0;
            lcd1602_write_cmd(0x80 + 0x40);
            lcd1602_show_integer(j, 0, a - '0');
            j++;
        }

        key_temp = key_scan(0);

        if (key_temp == KEY1_PRESS) {
            j--;
            lcd1602_clear_position(j, 0);
        }

        if (key_temp == KEY2_PRESS) {	
            check = 0;
			lcd1602_clear();
            for (i = 0; i < 30; i++) {
                chuoi1[i % 6] = at24c02_read_one_byte(EEPROM_ADDRESS + i);
                if (chuoi1[i % 6] == input[i % 6]) {
                    check++;
                    if (check == 6) {
                        lcd1602_show_string(0, 0, "Correct");
											check1 =6;
                        while (check1 == 6 && key_temp != KEY1_PRESS) {
													KeyDown();
														if (KeyState) {
																unsigned char a = KeyValue + '0';	
																status++;
																if (status == 1) {
																		lcd1602_clear();
																}
																delay_ms(100);
																input[j] = KeyValue;
																KeyState = 0;
																lcd1602_write_cmd(0x80 + 0x40);
																lcd1602_show_integer(j, 0, a - '0');
																j++;
														}
                            key_temp = key_scan(0);
                            if (key_temp == KEY1_PRESS) {
									lcd1602_show_string(0, 0, "Back and enter");
									lcd1602_show_string(0, 1, "Password");
									check=0;
									check1 = 34234;
									j=0;
									delay_ms(2000);
									lcd1602_clear();		
                            }
							if (key_temp == KEY2_PRESS) { 
								
							    lcd1602_show_string(0, 0, "Add new password");
								lcd1602_show_integer(1, 1, stt);															
								delay_ms(2000);
								lcd1602_clear();
								j = 0;
							}
							if (key_temp == KEY3_PRESS) {
								 for (j = 0; j < 29; j++) {
                                            at24c02_write_one_byte(EEPROM_ADDRESS + j, 0xff);
                                     }
									lcd1602_clear();
									j = 0;
									stt=0;
									lcd1602_show_string(0, 0, "Delete all");	
									delay_ms(1000);
									lcd1602_clear();
							
														}
                            if (key_temp == KEY4_PRESS) {
								stt++;
								if (stt>=5)
								stt=5;
                                i = 6;
                                while (i < 30) {
                                    unsigned char kt = at24c02_read_one_byte(EEPROM_ADDRESS + i);
                                    lcd1602_show_string(0, 0, "Checking EEPROM");						
                                    lcd1602_show_integer(0, 1, stt);
                                    lcd1602_show_integer(5, 1, kt);
                                    delay_ms(500);
                                    if (kt == 0xFF) {
                                        for (j = 0; j < 6; j++) {
                                            at24c02_write_one_byte(EEPROM_ADDRESS + i + j, input[j]);
                                        }
                                        break;
                                    } else {
                                        i += 6;
                                    }
                                }
                                if (i >= 30) {
                                    lcd1602_clear();
                                    lcd1602_show_string(0, 0, "Full memory");
                                }
                                delay_ms(1000);
								j=0;
								lcd1602_clear();	
                            }
                        }
                    }
                }
            }
            if(check != 6 && key_temp != KEY1_PRESS) {
                lcd1602_show_string(0, 0, "Incorrect");
				j=0;
            }
        }
        if (key_temp == KEY3_PRESS) {
		/*	for (i = 0; i < 30; i++) {
                chuoi1[i % 6] = at24c02_read_one_byte(EEPROM_ADDRESS + i);
			  lcd1602_show_integer(0, 0, chuoi1[i % 6] );
			}*/
			delay_ms(4000);
            lcd1602_clear();
            j = 0;
        }
    }
}
void KeyDown(void) {
    char a;
    GPIO_KEY = 0x0f;
    if (GPIO_KEY != 0x0f) {
        Delay10ms();
        if (GPIO_KEY != 0x0f) {
            KeyState = 1;
            GPIO_KEY = 0X0F;
            switch (GPIO_KEY) {
                case(0X07): KeyValue = 0; break;
                case(0X0b): KeyValue = 1; break;
                case(0X0d): KeyValue = 2; break;
                case(0X0e): KeyValue = 3; break;
            }
            GPIO_KEY = 0XF0;
            Delay10ms();
            switch (GPIO_KEY) {
                case(0X70): KeyValue = KeyValue; break;
                case(0Xb0): KeyValue = KeyValue + 4; break;
                case(0Xd0): KeyValue = KeyValue + 8; break;
                case(0Xe0): KeyValue = KeyValue + 12; break;
            }
            while ((a < 50) && (GPIO_KEY != 0xf0)) {
                Delay10ms();
                a++;
            }
            a = 0;
        }
    }
	
}
void Delay10ms(void) {
    unsigned char a, b, c;

    for (c = 1; c > 0; c--)
        for (b = 38; b > 0; b--)
            for (a = 130; a > 0; a--);
}