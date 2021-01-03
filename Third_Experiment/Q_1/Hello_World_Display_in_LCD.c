/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Hello_World_Display_in_LCD
Version : 
Date    : 1/3/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <alcd.h>

void main(void)
{

    DDRB=0b00000000;
    PORTB=0b00000000;
    
    lcd_init(20);   
    
    while (1)
    {
        lcd_gotoxy(0,0);
        lcd_putsf("Hello_World!");
    }
}
