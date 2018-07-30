/*
 * dvill032_lab1_part2.c
 *
 * Created: 7/30/2018 3:11:31 PM
 * Author : ucrcse
 */ //Purpose of masking is to only look at certain bits

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs,
	
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char cntavail = 0x00;
	while(1)
	{
		
		// (1) Read input
		tmpA = PINA & 0x0F;			// Consider the rightmost 4 bits
		// (2) Perform computation
		cntavail = (tmpA & 0x01 && 0x01) + (tmpA & 0x02 && 0x02) + (tmpA & 0x04 && 0x04) + (tmpA & 0x08 && 0x08);
		// (3) Write output
		PORTC = cntavail;
	}
	return 0;
}


