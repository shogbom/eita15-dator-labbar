*
 * GccApplication4.c
 *
 * Created: 2023-02-09 10:48:20
 * Author : lu2554hv-s
 */ 

#include <avr/io.h>

void timer3_init(){
	
	ICR3 = 1024;
	
	
	TCCR3A |= (1 << WGM31) | (1 << COM3A1);
	
	TCCR3B |= (1 << WGM33) | (1 << WGM32) | (1 << CS30);
	//sätter pb6 t output.
	DDRB |= (1 << PORTB6);
}

void set_pulse(uint16_t pulse){
	pulse = pulse/2;
	OCR3A = pulse;
}

void set_period(uint16_t period){
	ICR3 = period;
}


int main(void)
{
	timer3_init();
	
	set_pulse(1024);
	set_period(1024);
	
	while (1)
		{
			
		}
	return 0;
}
