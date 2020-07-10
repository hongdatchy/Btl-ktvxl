#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		DDRB = 0xff;
		TCCR0 |= (1<<WGM01)|(1<<WGM00)|(1<<CS01)|(1<<COM01);
		OCR0 =25;
    }
}

