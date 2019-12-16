/*
 * File:   newmainXC16.c
 * Author: MTurner
 *
 * Created on December 16, 2019, 10:28 AM
 */

int i = 0;
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
        blocking_read_pin(1,1);
        //idle
    }
    return 0;
}

int blocking_read_pin(int pin, int capture_time)
{
    static int reading = 0;
    TMR1 = 0;
    PR1 = 10000;
    while(TMR1 < 50)
    {
        i++;
    }
    while(1)
    {
        Nop();
    }
    return reading;
}