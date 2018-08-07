/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 5  Exercise 1
 *    Exercise Description:
 *  
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

enum States {start, B0, B1, B2} state;

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0;
unsigned char tmpB = 0x00;

void tick() {
	switch (state) {
		case start:
			state = B0;
			break;
		case B0:
			state = B1;
			break;
		case B1:
			state = B2;
			break;
		case B2:
			state = B0;
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
		case B1:
			tmpB = 0x02;
			break;
		case B2:
			tmpB = 0x04;
			break;
		default:
			break;
	}
}

void TimerISR() {TimerFlag = 1;}
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
    DDRC = 0xFF; PORTC = 0x00;
    state = start;
    TimerSet(1000);
    TimerOn();
    
    while (1) 
    {
		tick();
		PORTB = tmpB;
        while(!TimerFlag);	//Wait 1 sec
        TimerFlag = 0;
    }
}