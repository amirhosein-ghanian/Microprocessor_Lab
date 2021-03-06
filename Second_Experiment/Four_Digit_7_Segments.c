/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/26/2020
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
#include <delay.h>

int ar[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int No[4] = {0,0,0,0}; // array for indecating which number is showing in 7 segments

int timer_Zero_OF =0; // timer 0 over flow counter int   
int timer_One_OF =0; // timer 1 over flow counter int   
int portc_Temp; // template for doing maths and ...
int i = 3; // for going from top to bottom in array SevenSegmentNumbersArry
int last_SevenSegment_Initiated = 3;  // can be 0, 1, 2, 3

// Timer 0 overflow interrupt
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    timer_Zero_OF++;
    if(timer_Zero_OF == 2){ 

           portc_Temp = PORTC ^ 0b11111111;
           PORTC = portc_Temp ^ 0b11111111;
           portc_Temp = portc_Temp >> 1;
           if(portc_Temp == 0){
            portc_Temp = 8;
           }
           portc_Temp = portc_Temp ^ 0b11111111;
           PORTC = portc_Temp;
           
           PORTD = ar[No[last_SevenSegment_Initiated]];
           last_SevenSegment_Initiated--;
           if(last_SevenSegment_Initiated == -1 ){
            last_SevenSegment_Initiated = 3;
           }
           
           timer_Zero_OF=0;
    }
    TCNT0=0x00;
}

// Timer1 overflow interrupt
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    timer_One_OF++;
    if(timer_One_OF == 100){
        No[3]++;  
        //check numbers to incress the counter (recorrect array of 7segs)
        while (i >= 0){
            if( No[i] ==10){
             No[i-1]++;
             No[i]=0;
            }
            i--;
        }
        i=3;
        timer_One_OF=0;
    }
    TCNT1H=0xFF;
    TCNT1L=0xF0;
}


void main(void)
{

DDRD=0b11111111;
PORTD=0b00000000;
DDRC=0b11111111;
PORTC=0b11101111;// 0b00001000 = 8 decimal

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);


// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 0.032 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x00;


// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 8.192 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0xFF;
TCNT1L=0xF0;


// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

#asm("sei")
while (1)
      {
      // Place your code here
      }
}
