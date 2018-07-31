/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 2  Exercise 2 
 *    Exercise Description:
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */


#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s
	unsigned char tmpC = 0x00; 
	unsigned char tmpAGas = 0x00;
	unsigned char tmpAsb = 0x00;
	while(1)
	{
		// 1) Read Inputs and assign to variables
		tmpAGas = PINA & 0x4F; 
		tmpAsb = PINA & 0x30;
		// 2) Perform Computation
		
					// GetBit(tmpA, 4) && GetBit(tmpA, 5) && ~GetBit(TmpA, 6) 
		if (tmpAGas > 0x0C) {
			tmpC = 0x3F;
		}
		else if (tmpAGas > 0x09) {
			tmpC = 0x3E;
		}
		else if (tmpAGas > 0x06) {
			tmpC = 0x3C;
		}
		else if (tmpAGas > 0x04) {
			tmpC = 0x38;
		}
		else if (tmpAGas > 0x02) {
			tmpC = 0x70;
		}
		else if (tmpAGas) {
			tmpC = 0x60;
		}
		else {
			tmpC = 0x40;
		}
		
		if (tmpAsb == 0x30) {
			tmpC = tmpC | 0x80;
		}

		// 3) write results to port
		PORTC = tmpC;
	}
}