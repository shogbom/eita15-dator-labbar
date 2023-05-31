/*
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
void adc_init(){
	ADCSRA |= (1<<ADEN); // sätter på analog to dig
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1)| (1 << ADPS0); // sätter frekvensen mellan 50 till 200khz, prescaling factor blir 128
	ADMUX |= ( 1 << REFS0); // AVcc as refence voltage
	// set the channel to be read	
}
uint16_t adc_read(uint8_t channel)
{
	// set the channel to be read
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	// start the conversion process
	ADCSRA |= (1 << ADSC);
	// wait for the conversion to finish
	while (ADCSRA & (1 << ADSC)) {}
	// return the conversion result
	return ADC;
}
int main(void)
{
	timer3_init();
	adc_init();
	set_pulse(1024);
	set_period(1024);
	
	while (1)
		{
			set_pulse(adc_read(0));
		}
	return 0;
}
