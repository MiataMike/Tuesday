/*
 * File:   PicConfig.c
 * Author: MTurner
 *
 * Created on December 16, 2019, 10:42 AM
 */


#include "xc.h"
#include "PicConfig.h"

/** CONFIGURATION Bits **********************************************/

// CONFIG3
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable bit (Segmented code protection disabled)
#pragma config WPCFG = WPCFGDIS         // Configuration Word Code Page Protection Select bit (Last page(at the top of program memory) and Flash configuration words are not protected)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select bit (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config IOL1WAY = ON             // IOLOCK One-Way Set Enable bit (Write RP Registers Once)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL           // Oscillator Select (Primary oscillator (XT, HS, EC) with PLL module (XTPLL,HSPLL, ECPLL))
#pragma config PLLDIV = NODIV           // USB 96 MHz PLL Prescaler Select bits (No division, already at 4MHz)
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-speed start-up)disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = WDT_DIS         // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator functions are shared with PGEC1/PGED1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

int PicConfig(void) {

    Timer1Config();
    Timer2Config();
    LedConfig();
    DacConfig();

    return 0;
}

int Timer1Config()
{
    //T1 config, see page 218
    T1CONbits.TON = 1;     //turn on timer
    T1CONbits.TSIDL = 0;   // continues to run in idle mode
    T1CONbits.TCS = 0;     // use 4MHz internal clock
    T1CONbits.TCKPS = 0b11;// sets prescale, 256/64/8/1
    //IEC0bits.T1IE = 1;     // enable interrupt                polling for now
    //IPC0bits.T1IP = 0b001; //interrupt priority 1 (lowest)
    return 0;
}

int Timer2Config()
{
    // see page 222
    T2CONbits.T32 = 1;     //32 bit timer mode
    T2CONbits.TSIDL = 0;   // runs in idle
    T2CONbits.TCS = 0;     //use 4MHz internal clock
    T2CONbits.TCKPS = 0b11;// sets prescale, 256/64/8/1

    //set interrupt
    IEC0bits.T2IE = 1; //enable interrupt
    IPC1bits.T2IP = 0b001; //interrupt priority 1 (lowest)
    
    T2CONbits.TON = 1; //turn on        
    return 0;
}

int LedConfig()
{
    return 0;
}

int DacConfig()
{
    return 0;
}
