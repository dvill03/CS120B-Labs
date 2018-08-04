/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 3  Exercise 3
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

enum States { start, WAIT, POUNDx, CHECK_Y, UNLOCK, LOCK } state;

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
				state = (tmpA == Y) ? UNLOCK : WAIT; 
			break;

		case UNLOCK:				// PUSHING Y, need to let go then back to waiting
			state = (!tmpA) ? WAIT : UNLOCK;
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
		
		case UNLOCK:
			PORTB = 0x01;
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