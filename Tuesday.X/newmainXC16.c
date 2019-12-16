/*
 * File:   newmainXC16.c
 * Author: MTurner
 *
 * Created on December 16, 2019, 10:28 AM
 */


#include "xc.h"
//configure timer
/* the timer will be set up to have two different length states: the on state
 * and the sleep state. The on state will turn on the first LED, and when
 * the timer expires, resets and turns on the second LED. After the second
 * expiration, the timer is set to a much higher value and sleeps. Once this
 * timer expires, the processor wakes up and restarts
 * todos: create enum for state
 * implement processor power down
 
 */


int main(void) {
    PicConfig();
    
    return 0;
}
