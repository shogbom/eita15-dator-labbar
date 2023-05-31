#include <avr/io.h>

#define BAUD 9600
#define F_CPU 16000000UL
#define UBRR_VALUE F_CPU/16/BAUD-1

void USART0_init(void) {
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
	UBRR0L = (uint8_t)(UBRR_VALUE);

	// Set frame format: 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

	// Enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void USART0_send(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
	UDR0 = data; // Put data into buffer, sends the data
}

uint8_t USART0_receive(void) {
	while (!(UCSR0A & (1 << RXC0))); // Wait for data to be received
	return UDR0; // Get and return received data from buffer
}

int main(void) {
	USART0_init();

	while (1) {
		uint8_t received = USART0_receive();
		USART0_send(received);
	}

	return 0;
}
