/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 6  Exercise 1
 *    Exercise Description:
 *  
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>


#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

enum States { start, wait, INC, INCx, DEC, DECx, RESET, RESETx } state;

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char tmpA = 0x07;
unsigned char tmpC = 0x00;

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

void tick()
{
	switch(state) {   // Transitions
		case start:
			state = wait;
			
		case wait:  // Initial transition
			if (!tmpA)
			state = start;
			else if (tmpA == 0x03)
			state = RESET;
			else if (tmpA == 0x01)
			state = INC;
			else if (tmpA == 0x02)
			state = DEC;
			break;

		case INC:
		state = INCx;
		break;

		case INCx:  // Initial transition
		if(tmpA == 0x03)
		state = RESET;
		else if (tmpA == 0x01)
		state = INCx;
		else
		state = start;
		break;

		case DEC:  // Initial transition
		state = DECx;
		break;							//ternary
		
		case DECx:  // Initial transition
		if(tmpA == 0x03)
		state = RESET;
		else if (tmpA == 0x02)
		state = DECx;
		else
		state = start;
		break;
		
		case RESET:
		state = RESETx;
		break;
		
		case RESETx:
		state = (tmpA == 0x00) ? start : RESETx;
		
		default:
		state = start;
		break;
		
	} // Transitions

	switch(state) {   // State actions
		case start:
			LCD_Cursor(1);
			LCD_WriteData( tmpC + '0' );
			break;
			
		case wait:
			break;
			
		case INC:
			if (tmpC < 0x09){
				tmpC += 0x01;
				LCD_Cursor(1);
				LCD_WriteData( tmpC + '0' );
			}
			break;
		
		case INCx:
			break;
		
		case DEC:
			if (tmpC > 0) {
				tmpC -= 0x01;
				LCD_Cursor(1);
				LCD_WriteData( tmpC + '0' );
			}
			break;
		
		case DECx:
			break;
		
		case RESET:
			tmpC = 0;
			LCD_Cursor(1);
			LCD_WriteData( tmpC + '0' );
			break;
			
		case RESETx:
			break;
		
		default:
			tmpC = 0x07;
			LCD_Cursor(1);
			LCD_WriteData( tmpC + '0' );
			break;
	} // State actions
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	state = start;
	TimerSet(100);
	TimerOn();
	LCD_init();
	
	while(1) {
		tmpA = ~PINA & 0x03;
		tick();
		while(!TimerFlag) {
			};
		TimerFlag = 0;
	}
}


