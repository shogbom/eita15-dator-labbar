/*
 * Lab 2.2.c
 *
 * Created: 2023-02-08 17:31:15
 * Author : Samuel
 */ 

#include <avr/io.h>


int main(void)
{
    while (1) 
    {
    }
}
void enableUsart0(){
	UCSR0A = 0x00;
	UCSR0B = (1 << 4) | (1 << 3);
}
void setDataLengthStop(){
	011
	// 011 s'tter dataL till 8bit 
	UCSR0C =  (1 << UCSZ10) | (1 << UCSZ00) ;
	// satter StopL t 1bit
	UCSR0C = (0 << USBS0);
}
void SetBaudRate(int val){
	UBRR0H	= (unsigned char) (val >> 8);
	UBRR0L	= (unsigned char) val;
}
void usart_init(){
	enableUsart0();
	setDataLengthStop();
	SetBaudRate(8);
}
int readData(){
	while( !(UCSR0A & (1<<RXC0))){
		// snurra.
	}
	return UDR0;
}
void transmit(int kd){
	while (!(UCSR0A & (1 << UDRE0))){
		// snurra.
	}
	UDR0 = kd;
}
void SetFastPWM_ICR3(){
	TCCR3A &= ~(1 << COM3A0);
	TCCR3B |=  (1 << WGM33) | (1 << WGM32) | (1 << CS30) |  (1 << CS32) | (1 << ICES3); 
}

void setScaler10(){
	TCCR3B = (1 << CS30) | (1<<CS32);
	// sätter scalern till 1024
}
void setPortBOut(){
	DDRB |= (1<<PORTB6)
	
}
void timer3_init(){
	TCCR3A &= ~(1 << COM3A0);
	TCCR3B |=  (1 << WGM33) | (1 << WGM32) | (1 << CS30) |  (1 << CS32) | (1 << ICES3);
	TCCR3B = (1 << CS30) | (1<<CS32);
	DDRB |= (1<<PORTB6)
	//   3.1 F_timer = F_clock / prescaler = 16000000 / 1024 = 15625 Hz
	//	T = 1 / F_timer = 1 / 15625 = 64 microseconds
}
void set_pulse(uint16_t a){
	OCR3A = a;
}
void set_period(uint16_t b){
	ICR3 = b;	
}
void Question3_2(){
	set_pulse(0xFF);
	set_period(0xFFFF);
}
