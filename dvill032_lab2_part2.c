/*
 * dvill032_lab2_part2.c
 *
 * Created: 7/31/2018 12:19:28 PM
 * Author : Dan
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s
	unsigned char tmpC = 0x00; 
	unsigned char tmpA = 0x00;
	while(1)
	{
		// 1) Read Inputs and assign to variables
		tmpA = PINA & 0x0F; 
		// 2) Perform Computation
		if (tmpA > 0x0C) {
			tmpC = 0x1F;
		}
		else if (tmpA > 0x09) {
			tmpC = 0x1E;
		}
		else if (tmpA > 0x06) {
			tmpC = 0x1C;
		}
		else if (tmpA > 0x04) {
			tmpC = 0x1A
		}
		else if (tmpA > 0x02) {
			tmpC = 0x38
		}
		else {
			tmpC = 0x30
		}
		// 3) write results to port
		PORTC = tmpC;
	}
}

