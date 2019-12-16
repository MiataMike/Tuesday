/*
 * File:   newmainXC16.c
 * Author: MTurner
 *
 * Created on December 16, 2019, 10:28 AM
 */

int i = 0;
int blocking_read_pin(int pin, long capture_time);
void __attribute__((interrupt,auto_psv)) _T3Interrupt(void);
#include "xc.h"
#include "PicConfig.h"


/* This program will blink the LEDs 
 * todos: create enum for state
 * implement processor power down
 
 */


int main(void) {
    PicConfig();
    
    
    while(1)
    {
        blocking_read_pin(1,sec2clk(.2));
        blocking_read_pin(2,sec2clk(.2));
        //idle

        TMR2 = 0; //reset sleep timer
        TMR3 = 0;
        DeepSleep();
        i++;
    }
    return 0;
}

int blocking_read_pin(int pin, long capture_time)
{
    static int reading = 0;
    TMR1 = 0; //reset timer
    while(TMR1 < capture_time)
    {
        Nop(); //wait, gather readings
    }
    return reading;
}


void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void)
{
    if(IFS0bits.T2IF | IFS0bits.T3IF) // check if timer 2 has 
    {
        TMR2 = 0;
        TMR3 = 0;
        IFS0bits.T2IF = 0; // clear interrupt flags
        IFS0bits.T3IF = 0;
    }
}

inline void DeepSleep(void)
{
    DSCONbits.DSEN = 1; // this must be repeated for safety reasons
    DSCONbits.DSEN = 1;
    asm volatile("pwrsav #0");
}