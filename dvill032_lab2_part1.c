/*
 * dvill032_lab2_part1.c
 *
 * Created: 7/31/2018 11:19:02 AM
 * Author : Dan
 */ 

#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;  // inputs
	DDRB = 0x00; PORTB = 0xFF;  // inputs
	DDRC = 0xFF; PORTC = 0x00;  // outputs,

	// Do we need tmpA, tmpB? Why not just do directly since no manip needed.
	
    while(1)
    {
		unsigned char count = 0x00;
	    // 1) Read Inputs and assign to variables
	    // 2) Perform Computation
		for (unsigned char i=0; i<8; i++){
			count += GetBit(PINA, i) + GetBit(PINB, i);
		}
	    // 3) write results to port
	    PORTC = count;
    }
}

