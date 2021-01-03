/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : English_Letters_Display_LCD
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

int X_Length;
int Y_Length;
int Timer_OF_Counter;
int Letter_Position;

char Letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
      Timer_OF_Counter++;
      if (Letter_Position < 26 )
         {
           if(Timer_OF_Counter == 500 )
             {

          	lcd_putchar(Letters[Letter_Position]);
          	Letter_Position += 1;
          	//increase x position
          	X_Length=X_Length+1;
          
          	//check need to change line 
          	if(Letter_Position==20)
	  {
            	    X_Length=0;
            	    Y_Length=1;
          	  }

          	lcd_gotoxy(X_Length,Y_Length);
          	Timer_OF_Counter=0;
       	}
          }
       else
            {
              TCCR0=0x00;
              TIMSK=0x00;
            }      
       TCNT0=0x00;
}


void main(void)
{

    DDRB=0x00;
    PORTB=0x00; 
    
    X_Length=0;
    Y_Length=0;
    Timer_OF_Counter=0;
    Letter_Position=0;   
    
    TCCR0=0x01;
    TCNT0=0x00;
    OCR0=0x00;
    TIMSK=0x01; 
    
     lcd_init(20);
    #asm("sei")

    while (1)
    {
    }


}
