/*    Partner(s) Name & E-mail: Austin Topacio (atopa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Lab 3  Exercise 5
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
#define len 4

enum States { WAIT, SEQUENCEx, LOCK_TOGGLE, LOCK_TOGGLEx, LOCK, END } state;

unsigned char tmpA = 0x00;            
unsigned char seq [4] = {pound, X, Y, X};

void tick()
{
    for (unsigned char i=0; i<len; i++){
        tmpA = PINA & 0x87;						// PA 7,[0:2] 
        switch(state) {          
            case WAIT:								   // Wait for # or from_in
                if (tmpA == from_in)
                    state = LOCK;
                else if (i == 3)
                    state = (tmpA == seq[i]) ? LOCK_TOGGLE : END;
                else
                    state = (tmpA == seq[i]) ? SEQUENCEx : END;
                break;

            case SEQUENCEx:                       
                state = (!tmpA) ? WAIT : SEQUENCEx;    //Move on to next char if let go, else wait
                break;

            case LOCK_TOGGLE:					   // PUSHING Y, need to let go then back to waiting
                state = (!tmpA) ? WAIT : LOCK_TOGGLEx;
                break;                          
      
            case LOCK_TOGGLEx:				       // Pushing something, need to let go
                state = (!tmpA) ? WAIT : LOCK_TOGGLEx;
                break;
      
            default:								   // Default, waiting
                state = WAIT;
                break;
              
        } // Transitions

        switch(state) {   // State actions
            case WAIT:                           
                break;
               
            case SEQUENCEx:
                i -= 1;
                break;
      
            case LOCK_TOGGLE:                    // Perform the flip only once
                PORTB ^= 1;                       
                break;                          
      
            case LOCK_TOGGLEx:
                break;
          
            case LOCK:
                PORTB = 0x00;

            case END:
                i = 3;

            default:
                break;
        }
    }
}

int main() {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    state = WAIT;

    while(1) {
        tick();
    }
    return 0;
}