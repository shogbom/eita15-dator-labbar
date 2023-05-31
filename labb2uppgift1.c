#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
uint8_t lednbr = 4;
uint8_t k = 3;

void ledInit(){
	DDRB = 0xff;
}
void button_init()
{
	DDRA &= 0b00000011;
	DDRD &= 0b01111111;
}


void ledOn(uint8_t ledn){
	*(volatile uint8_t*) 0x25 = (1 << ledn);
	//PORTB = (1 << ledn);
}
void ledOff(uint8_t ledn){
	*(volatile uint8_t*) 0x25 &= ~(1 << ledn);
	//PORTB = ~(1 << ledn);
	//PORTB &= ~(1 << ledn);
}
uint8_t buttonRead(uint8_t n){
	n++;
	return ((PINA & (1 << n)) >> n);
	
	
}
uint8_t buttonReadR(uint8_t n){
	n++;
	if(((PINA & (1 << n)) >> n) == 1){
		_delay_ms(5);
		return 1;
	}
	
	return 0;
}


int main(void)
{
	button_init();
	ledInit();
	while (1){
		
		if((buttonReadR(2) == 1) && !(k==0)){
			k--;
			while (buttonReadR(2)==1);
		}
		if(k==0){
			ledOn(2);
			
			
		}
		if(k== 0 && buttonReadR(2)==1){
			ledOff(2);
			k=4;
		}

		
		/*ledInit();
		ledOn(lednbr);
		_delay_ms(5000);
		ledOff(lednbr);
		_delay_ms(5000);*/
	}

	
}
