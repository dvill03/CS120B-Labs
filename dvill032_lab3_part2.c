/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 3  Exercise 2 
 *    Exercise Description:
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */ 

#include <avr/io.h>


enum States { start, INC, INCx, DEC, DECx, RESET, RESETx } state;

void tick()
{
	switch(state) {   // Transitions
		case start:  // Initial transition
			if (!PINA)    
				state = start;
			else if ((PINA & 0x03) == 0x03)
				state = RESET;
			else if ((PINA & 0x01) && 0x01)
				state = INC;
			else if ((PINA & 0x02) && 0x02)
				state = DEC;
			break;

		case INC:	
			state = INCx;
			break;

		case INCx:  // Initial transition
			if((PINA & 0x03) == 0x03)
				state = RESET;
			else if ((PINA & 0x01) && 0x01)
				state = INCx;
			else 
				state = start;
			break;

		case DEC:  // Initial transition
			state = DECx;
			break;							//ternary
		
		case DECx:  // Initial transition
			if((PINA & 0x03) == 0x03)
				state = RESET;
			else if ((PINA & 0x02) && 0x02)
				state = DECx;
			else
				state = start;
			break;	
		
		case RESET:
			state = RESETx;
			break;
		
		case RESETx:
			state = (PINA & 0x03) == 0x00 ? start : RESETx;
		
		default:
			state = start;
			break;
				
	} // Transitions

	switch(state) {   // State actions
		case start:
			break;
			
		case INC:
			if (PORTC < 0x09)
				PORTC += 0x01;
			break;
		
		case INCx:  
			break;
		
		case DEC:
			if (PORTC > 0)  
				PORTC -= 0x01;
			break;
		
		case DECx:  
			break;
		
		case RESET:
			PORTC = 0;
			break;
		case RESETx:
			break;
		
		default:
			PORTC = 0x07;
			break;
	} // State actions
}

int main() {
	PORTC = 0x07;           
	state = start; 

	while(1) {
		tick();
	}
	return 0;
}