/*
 * File:   newmainXC16.c
 * Author: MTurner
 *
 * Created on December 16, 2019, 10:28 AM
 */

#define LED_pwr 512 // half of 10 bit scale

int blocking_read_pin(int pin, long capture_time);
void __attribute__((interrupt,auto_psv)) _T3Interrupt(void);

#include "xc.h"
#include "PicConfig.h"


/* This program will blink the LEDs 
 * todos: create enum for state
 * implement processor power down
 
 */



int main(void) {
    PicConfig(); // see PinConfig.h for config implementation
    DAC1DAT = 256;// turns on LED via DAC 

    while(1)
    {
        
        //warning, setting to ~ 2 sec will overflow buffer
        blocking_read_pin(0, sec2clk(.2));
        blocking_read_pin(1, sec2clk(.2));
        
        //prepare to idle
        TMR2 = 0; //reset sleep timer
        TMR3 = 0;
        Idle();
    }
    return 0;
}






int blocking_read_pin(int pin, long capture_time)
{
    static int reading = 0; //not used yet
    long elapsed_time = 0; // builds clock cycles from both regs
    switch(pin)
    {
        case 0: LATBbits.LATB14 = 0; // switch select gets written low
            break;
        case 1: LATBbits.LATB14 = 1; 
            break;
        default: LATBbits.LATB14 = 1;
    }
    
    TMR2 = 0; //reset timer
    TMR3 = 0;
    while(elapsed_time < capture_time)
    {
        elapsed_time =  TMR2;
    }
    return reading;
}


void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void)
{
    if(IFS0bits.T2IF | IFS0bits.T3IF) // check if timer 2 has 
    {
        TMR2 = 0;// reset timer
        TMR3 = 0;
        IFS0bits.T2IF = 0; // clear interrupt flags
        IFS0bits.T3IF = 0;
    }
}
