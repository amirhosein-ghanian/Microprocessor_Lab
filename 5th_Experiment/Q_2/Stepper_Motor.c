/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Stepper_Motor
Version : 
Date    : 1/12/2021
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

int Timer_Zero_OF;
int Begin_Time;
int Rotatation;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    TCNT0=0x0C;

    if(Begin_Time==1) {
        if(Timer_Zero_OF==0) {     
            if (Rotatation == 0) {
                PORTB.0 = 1;
                PORTB.1 = 0;
                PORTB.2 = 0;
                PORTB.3 = 1;
            }else if (Rotatation == 1) {
                PORTB.0 = 1;
                PORTB.1 = 0;
                PORTB.2 = 1;
                PORTB.3 = 0;
            }else if (Rotatation == 2) {
                PORTB.0 = 0;
                PORTB.1 = 1;
                PORTB.2 = 1;
                PORTB.3 = 0;
            }else if (Rotatation == 3) {
                PORTB.0 = 0;
                PORTB.1 = 1;
                PORTB.2 = 0;
                PORTB.3 = 1;
            }
        }
        
        if(Timer_Zero_OF == 5){
            Timer_Zero_OF = 0;  
            if(Rotatation<3) {
                Rotatation++;
            } else {
                Rotatation=0;
                Begin_Time=0;
            }
        } else {
            Timer_Zero_OF++;
        }   
    }
}

void main(void)
{ 
    Timer_Zero_OF = 0;  
    Rotatation = 0;
    Begin_Time = 0;
    
    DDRC = 0x00;   
    PINC = 0x00;  
       
    DDRB = 0xff;  
    PORTB = 0x00;

    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (0<<CS00);
    TCNT0=0x0C;
    OCR0=0x00;
    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;
    ASSR=0<<AS2;
    TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
    TCNT2=0x00;
    OCR2=0x00;
    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);
    UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
    ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
    SFIOR=(0<<ACME);
    ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
    SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
    TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

    #asm("sei")

    while (1) {
        if(PINC.2==0 &&  Begin_Time==0) { 
             Timer_Zero_OF = 0;  
             Begin_Time = 1;
        }
    }
}
