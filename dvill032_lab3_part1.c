/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 3  Exercise 1 
 *    Exercise Description:
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h> 

enum States { start, B0, B0x, B1, B1x } state;

void tick()
{
    switch(state) {   // Transitions
        case start:  // Initial transition
            state = B0;
        break;

        case B0:   
            if (!(PINA & 0x01))   
                state = B0;
            else
                state = B0x;
            break;

        case B0x:  // Initial transition
            if (PINA & 0x01 && 0x01)
                state = B0x;
            else
                state = B1;
            break;

        case B1:  // Initial transition
            if (!(PINA & 0x01))
                state = B1;
            else
                state = B1x;
            break;                            //ternary
       
        case B1x:  // Initial transition
            if (PINA & 0x01 && 0x01)
                state = B1x;
            else
                state = B0;
            break;   
       
        default:
            state = B0;
            break;
               
    } // Transitions

    switch(state) {   // State actions
        case B0:
            PORTB = 0x01;
            break;
        case B0x: 
            PORTB = 0x02;
            break;
        case B1: 
            PORTB = 0x02;
            break;
        case B1x: 
            PORTB = 0x01;
            break;
        default:
            PORTB = 0x01;
            break;
    } // State actions
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