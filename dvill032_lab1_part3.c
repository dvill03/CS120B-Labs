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
		
		tmpA = PINA & 0x0F;				// Consider the rightmost 4 bits
		if (tmpA == 0x0F) {
			cntavail = 0x80;
		} 
		else { 
			cntavail = (tmpA & 0x01 && 0x01) + (tmpA & 0x02 && 0x02) + (tmpA & 0x04 && 0x04) + (tmpA & 0x08 && 0x08);
			cntavail = 0x04 - cntavail;
		}
		PORTC = cntavail;
	}
	return 0;
}