/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Bai2
Version : 
Date    : 6/3/2020
Author  : 
Company : 
Comments: 


Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega328p.h>
#include <delay.h>
// Declare your global variables here

void main(void)
{
    PORTD.0 = 1;
    PORTD.1 = 1; 
    PORTB.0 = 0;
    DDRB.0 = 1;
 

while (1)
      {
      // Place your code here
//        if(PIND.0 == 0)      // co nhan nut ON
//        {
//            PORTB.0 = 1;     //bat led
//        }               
//        if(PIND.1 ==0)       // co nhan nut OFF
//        {
//            PORTB.0 =0;      // tat led
//        }
        PINB.0 = 1;      // togger trang thai cua portb, neu dang xuat(PINB.0 = 1) thi thanh doc(PINB.0 = 0)
        delay_ms(500);   
      }
}
