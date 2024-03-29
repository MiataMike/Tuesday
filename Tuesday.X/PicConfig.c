/*
 * File:   PicConfig.c
 * Author: MTurner
 *
 * Created on December 16, 2019, 10:42 AM
 */


#include "xc.h"
#include "PicConfig.h"

/** CONFIGURATION Bits **********************************************/

// code protection
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable bit (Segmented code protection disabled)
#pragma config WPCFG = WPCFGDIS         // Configuration Word Code Page Protection Select bit (Last page(at the top of program memory) and Flash configuration words are not protected)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select bit (Write Protect from WPFP to the last page of memory)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)

// Clocks
#pragma config IOL1WAY = ON             // IOLOCK One-Way Set Enable bit (Write RP Registers Once)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL           // Oscillator Select (Primary oscillator (XT, HS, EC) with PLL module (XTPLL,HSPLL, ECPLL))
#pragma config PLLDIV = NODIV           // USB 96 MHz PLL Prescaler Select bits (No division, already at 4MHz)
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-speed start-up)disabled)

//Watchdog
#pragma config DSWDTPS = DSWDTPSE       // Deep sleep Watchdog Timer Postscaler  1ms
#pragma config DSWDTOSC = LPRC          // low power RC source for WDT
#pragma config DSWDTEN = ON             // enable deep sleep watchdog timer
#pragma config DSSWEN = ON              // enable deep sleep
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = WDT_DIS         // Watchdog Timer Enable (Watchdog Timer is disabled)

//Programming
#pragma config ICS = PGx1               // Comm Channel Select (Emulator functions are shared with PGEC1/PGED1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled

int PicConfig(void) {
    //configure everything
    Timer1Config(); 
    Timer2Config();
    SwConfig();
    DacConfig();
    //PowerDownConfig();
    return 0;
}

int Timer1Config()
{
    //T1 config, see page 218
    T1CONbits.TON = 1;     //turn on timer
    T1CONbits.TSIDL = 1;   // stops in idle mode
    T1CONbits.TCS = 0;     // use 4MHz internal clock
    T1CONbits.TCKPS = 0b11;// sets prescale, 256/64/8/1
    IEC0bits.T1IE = 0;     // disable interrupt                polling for now
    //IPC0bits.T1IP = 0b001; //interrupt priority 1 (lowest)
    PR1 = 0xFFFF;// set timer period to max (we're polling)
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
    IEC0bits.T2IE = 1; //enable interrupts
    IEC0bits.T3IE = 1; 
    IPC1bits.T2IP = 0b011; //interrupt priority 3 (1 is lowest)
    
    //load values
    PR3 = sec2clk(1) / 0x10000; // gets upper bytes of period (in clock cycles)
    PR2 = sec2clk(1) & 0xFFFF; // gets lower bytes
    TMR3 = 0;
    TMR2 = 0; //reset timer
    
    T2CONbits.TON = 1; //turn on        
    return 0;
}

int SwConfig()
{
    TRISBbits.TRISB14 = 0; // configures pin as digital output
    ANSBbits.ANSB14 = 0;  
    return 0;
}

int DacConfig()
{
    TRISGbits.TRISG9 = 1; // configures as analog output
    ANSGbits.ANSG9 = 1; 
    DAC1CONbits.DACSIDL = 1; // doesnt operate in idle 
    DAC1CONbits.DACFM = 0; // left justified
    DAC1CONbits.DACREF = 0b10; //3.3v output
    DAC1CONbits.DACEN = 1; //enable
    return 0;
}

long sec2clk(float seconds)
{
    long clocks = 0;
    clocks = seconds * 16000000; // checked with stopwatch, needs multiplied by 4
    clocks /= 256; // 4MHz clock rate with 256 prescaler
    return clocks;
}

int PowerDownConfig()
{
    PMD1 = !(0x3800);
    PMD2 = !(0xFFFF);
    PMD3 = !(0x0040);
    PMD4 = 0xFFFF;
    PMD5 = 0xFFFF;
    PMD6 = 0xFFFF;
    PMD7 = 0xFFFF;
    return 0;
}