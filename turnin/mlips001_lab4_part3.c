
/*	Author: mlips001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States{locked, release, unlock} state;

unsigned char buttonX;
unsigned char buttonY;
unsigned char buttonP;
unsigned char buttonLock;

unsigned char tempB;


void door_lock(){
	buttonX = PINA & 0x01;
	buttonY = PINA & 0x02;
	buttonP = PINA & 0x04;
	buttonLock = PINA & 0x80;
		
	switch(state){ 
		case locked:
			if(buttonLock){
				state = locked;
			}
			if(!buttonX && buttonY && buttonP && !buttonLock){
				state = unlock;
			}
			else{
				state = locked;
			}
			break;
		case release:
			if(!buttonX && !buttonY && !buttonP && !buttonLock){
				state = release;
			}
			else if(!buttonX && buttonY && !buttonP && !buttonLock){
				state = unlock;
			}
			else{
				state = locked;
			}
			break;
		case unlock:
			if(!buttonX && !buttonY && !buttonP && buttonLock){
				state = locked;
			}
			else{
				state = unlock;
			}
			break;
	}
	switch(state){ 
		case locked:
			tempB = 0x00;
			break;
		case release:
			break;
		case unlock:
			tempB = 0x01;
			break;
	}			
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	state = locked;

    /* Insert your solution below */
    while (1) {
	door_lock();
	PORTB = tempB;
    }
    return 1;
}
