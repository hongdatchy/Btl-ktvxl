/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Atmega328
Version : 1.0.0
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
    DDRD.0 = 1;
while (1)
      {
      // Place your code here
         
         PORTD.0 = 1;
         delay_ms(500);
         PORTD.0 = 0; 
         delay_ms(500);
      }
}
