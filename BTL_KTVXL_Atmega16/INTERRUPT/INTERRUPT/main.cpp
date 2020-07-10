#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define cbi(port, bit) (port) &= ~(1 << (bit))
#define sbi(port, bit) (port) |=  (1 << (bit))
#define tbi(port, bit) (port) ^=  (1<<bit)


int main(void)
{
    /* Replace with your application code */
	GICR |= (1<< INT0);
	MCUCR |= (1<< ISC10);// n?u bên trên là Vector ng?t int1 thì dòng này ph?i là isc11, và d??i kia c?ng ph?i là int1
	sei();
	DDRD = 0b10000000;
	/*PORTD = 0b10000000;*/
    while (1) 
    {
		PORTD = 0x00;
    }

}
ISR(INT0_vect){
	PORTD = 0b10000000;
	_delay_ms(1000);
}

