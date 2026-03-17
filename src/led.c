#include "bits.h"
#include <pic18f4550.h>


void initLed (void){
    // RB2 -> RB5 sao os leds
    TRISB = TRISB & ~0x3C;
    LATB = LATB & ~0x3C;
}

void ledON (int x){
    BitSet(LATB,x);
}


void ledOFF (int x){
    BitClr(LATB,x);
}
