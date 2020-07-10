#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>

#define cbi(port, bit) (port) &= ~(1 << (bit))
#define sbi(port, bit) (port) |=  (1 << (bit))
#define tbi(port, bit) (port) ^=  (1<<bit)



int main(void)
{
    /* Replace with your application code */
	DDRC = 0b00001111;
	PORTC = 0b00000000;
	DDRD = 0b00000010;
	int count= 0;
    while (1) 
    {
// 		for (int i=0; i<4; i++)
// 		{
// 			PORTC |= (1<<i);
// 			_delay_ms(100);
// 		}
// 		for (int i=3; i>=0; i--)
// 		{
// 			PORTC ^= (1<<i);
// 			_delay_ms(100);
// 		}
// 		for (int i=0; i<4; i++)
// 		{
// 			sbi(PORTC,i);
// 			_delay_ms(100);
// 			cbi(PORTC,i);
// 			_delay_ms(100);
// 		}
		if(bit_is_clear(PIND,0))
		{
			while(bit_is_clear(PIND,0)){}
			sbi(PORTD, 2);	
			if(count %2==0){
				sbi(PORTD,1);
				count =1;
			}else{
				cbi(PORTD,1);
				count =0;
			}
		}
    }
}

