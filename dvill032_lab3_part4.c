/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 3  Exercise 4
 *    Exercise Description:
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>

#define X 0x01
#define Y 0x02
#define pound 0x04
#define from_in 0x80

enum States { start, WAIT, POUNDx, CHECK_Y, LOCK_TOGGLE, LOCK_TOGGLEx, LOCK } state;

unsigned char tmpA = 0x00;	// PA0, PA1, PA2, PA7			

void tick()
{
	tmpA = PINA & 0x87;
	switch(state) {   
		case start:
			state = WAIT;
			break;
			
		case WAIT:					// Wait for # or from_in
			if (tmpA == from_in)
				state = LOCK;
			else
				state = (tmpA == pound) ? POUNDx : WAIT;
			break;

		case POUNDx:				// Pushing #, need to let go, otherwise back to waiting
			if (tmpA == pound)
				state = POUNDx;
			else
				state = !tmpA ? CHECK_Y : WAIT;	
			break;

		case CHECK_Y:				// Let go of #, need Y to unlock, otherwise back to waiting
			if (!tmpA)
				state = CHECK_Y;
			else 
				state = (tmpA == Y) ? LOCK_TOGGLE : WAIT; 
			break;

		case LOCK_TOGGLE:				// PUSHING Y, need to let go then back to waiting
			state = (!tmpA) ? WAIT : LOCK_TOGGLEx;
			break;							
		
		case LOCK_TOGGLEx:				// Pushing something, need to let go
			state = (!tmpA) ? WAIT : LOCK_TOGGLEx;
			break;
		
		default:					// Default, waiting
			state = start;
			break;
				
	} // Transitions

	switch(state) {   // State actions
		case WAIT:
			break;
			
		case POUNDx:
			break;
		
		case CHECK_Y:  
			break;
		
		case LOCK_TOGGLE:				// Perform the flip only once
			PORTB ^= 1;						// xor, 0000 0000 -> 0000 0001. // 0000 0001 -> 0000 0000
			break;							
		
		case LOCK_TOGGLEx:
			break;
			
		case LOCK:
			PORTB = 0x00;

		default:
			break;
	} 
}

int main() {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;           
	state = start; 

	while(1) {
		tick();
	}
	return 0;
}