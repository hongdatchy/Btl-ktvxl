/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : StepMotor_control
Version : 
Date    : 19/04/2020
Author  : 
Company : 
Comments: 

Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
// Alphanumeric LCD functions
#include <alcd.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
// Declare your global variables here

#define a1 PORTB.1
#define a2 PORTB.2
#define b1 PORTB.3
#define b2 PORTB.4

unsigned int i = 0;
unsigned int tt = 1;
unsigned int tt2 = 1;
unsigned int delayTime = 10; //delay time in ms

float speed; 
char buffer[16];
char f2s_buffer[16];
//unsigned int count_test = 0;

//int codea1[] = {1,0,0,1};
//int codea2[] = {0,1,1,0};
//int codeb1[] = {1,1,0,0};
//int codeb2[] = {0,0,1,1};

int counterclockwise_code[] = {0x10,0x18,0x08,0x0c,0x04,0x06,0x02,0x12};//, 0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08 ;
int clockwise_code[] = {0x12,0x02,0x06,0x04,0x0c,0x08,0x18,0x10};//, 0x0E, 0x0A, 0x0B, 0x09}; 
int trunggian[]={0x12,0x02,0x06,0x04,0x0c,0x08,0x18,0x10};
int trunggiantruoc[] = {0x12,0x02,0x06,0x04,0x0c,0x08,0x18,0x10};

void clockwise_rotate(int delayTime){
    //float delayTime = 60000.0/(4096.0 * speed); //delayTime in ms; 
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts("Clockwise");
    for(i = 0; i<8 ;i++){
        trunggian[i] =  clockwise_code[i];
        trunggiantruoc[i] = trunggian[i];
    }
    for(i = 0; i<8; i++){
        PORTB = trunggian[i]; 
        //trunggiantruoc[i] = trunggian[i];
        delay_ms(delayTime); 
    } 
} 

void counterclockwise_rotate(int delayTime){
    //float delayTime = 60000.0/(4096.0 * speed); //delayTime in ms  
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts("Counter clock");
    for(i = 0; i<8 ;i++){
        trunggian[i] =  counterclockwise_code[i];
        trunggiantruoc[i] = trunggian[i];
    }
    for(i = 0; i<8; i++){
        PORTB = trunggian[i];
        delay_ms(delayTime); 
    } 
}

// External Interrupt 0 service routine
// Place your code here
interrupt [EXT_INT0] void ext_int0_isr(void)
{
     delay_ms(100);
    /* lcd_clear();
    lcd_gotoxy(0,0);
    ftoa(tt2, 2, f2s_buffer);
    sprintf(buffer, "tt2 = %s", f2s_buffer);
    lcd_puts(buffer); */
     if(tt2==0){ 
        tt2=1;
         clockwise_rotate(delayTime); 
     }
     else{  
        tt2=0;
        counterclockwise_rotate(delayTime);
        
     }
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{ 
    delay_ms(100);  
    /*lcd_clear();
    lcd_gotoxy(0,0);
    ftoa(tt, 2, f2s_buffer);
    sprintf(buffer, "tt = %s", f2s_buffer);
    lcd_puts(buffer);  */
     if(tt ==1){
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_puts("Stop!");
        for(i = 0; i<8; i++){
          trunggian[i] = 0;
        }   
        tt=0;
     }
     else{
        if(trunggiantruoc[0] == clockwise_code[0]){
            lcd_clear();
            lcd_gotoxy(0,0);
            lcd_puts("Clockwise");  
        }
        else{
            lcd_clear();
            lcd_gotoxy(0,0);
            lcd_puts("Counter clock");
        } 
        for(i = 0; i<8; i++){
          trunggian[i] = trunggiantruoc[i];
        }
        tt=1;
     }                   
}


void main(void)
{
// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: On
// INT1 Mode: Falling Edge
// INT2: Off
GICR|=(1<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(1<<INTF1) | (1<<INTF0) | (0<<INTF2);
// Global enable interrupts
#asm("sei")

// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (1<<DDD5) | (1<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 8
lcd_init(16);
lcd_puts("Welcome!");
delay_ms(100);
lcd_clear();


lcd_gotoxy(0,0);
lcd_puts("Clockwise");
    while(1){
        speed = (1000.0*60.0)/(512.0*8.0*delayTime);
        ftoa(speed, 2, f2s_buffer);
        sprintf(buffer, "Speed = %srpm", f2s_buffer);
        lcd_gotoxy(0,1);
        lcd_puts(buffer);
        /*if (PIND.4!=0 && PIND.5!=0){  
            for(i = 0;i<8;i++){
                PORTB = trunggian[i];
                delay_ms(delayTime);
            }    
        }  */
        if (PIND.4==0){ 
            delay_ms(100);
            if(delayTime > 1)    delayTime -= 1;
            //for(i = 0;i<8;i++){
              //  PORTB = trunggian[i];
             //   delay_ms(delayTime);
            //}        
        } 
        if (PIND.5==0){
            delay_ms(100);
            delayTime += 2;
            //for(i = 0;i<8;i++){
            //    PORTB = trunggian[i];
            //    delay_ms(delayTime);
            //}      
        } 
        for(i = 0;i<8;i++){
                PORTB = trunggian[i];
                delay_ms(delayTime);
        }
           
    }  
}