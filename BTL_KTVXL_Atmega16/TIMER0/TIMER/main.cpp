#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <avr/interrupt.h>

#define cbi(port, bit) (port) &= ~(1 << (bit))
#define sbi(port, bit) (port) |=  (1 << (bit))
#define tbi(port, bit) (port) ^=  (1<<bit)

int main(void)
{
	DDRB = 0x00;
	DDRC = 0xff;
	TCCR0 |= (1<<CS01)|(1<< CS02);
	TCNT0 = 0;
    /* Replace with your application code */
    while (1) 
    {

		if(TCNT0 ==10){
			TCNT0=0;
		}
		PORTC = TCNT0;
    }
}


