#include <avr/io.h>
#include <avr/interrupt.h>

enum States {start, B0, B0x, B1, B1x, B2, B2x} state;

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void tick() {
	switch (state) {
		case start:
			state = B0;
			break;
		case B0:
			state = tmpA ? B0x : B1;
			break;
		case B0x:
			state = tmpA ? B0 : B0x;
			break;
		case B1:
			state = tmpA ? B1x : B2;
			break;
		case B1x:
			state = tmpA ? B1: B1x;
			break;
		case B2:
			state = tmpA ? B2x : B0;
			break;
		case B2x:
			state = tmpA ? B2 : B2x;
			break;
		default:
			state = start;
			break;
	}
	switch (state) {
		case start:
			break;
		case B0:
			tmpB = 0x01;
			break;	
		case  B0x:
			break;
		case B1:
			tmpB = 0x02;
			break;
		case B1x:
			break;
		case B2:
			tmpB = 0x04;
			break;
		case B2x:
			break;
		default:
			break;
	}
}

void TimerISR() {
	TimerFlag = 1;
}
	
void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	state = start;
	TimerSet(300);
	TimerOn();
	
	while (1) {
 		tmpA = ~PINA & 0x01;
 		tick();
		PORTC = tmpB;
		while(!TimerFlag);
		TimerFlag = 0;
		PORTC = tmpB;
	}
}