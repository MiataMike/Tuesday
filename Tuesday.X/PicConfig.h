
/* 
 * File:PioConfig.h   
 * Author: MTurner
 * Comments:
 * Revision history: first header!
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  




// TODO Insert declarations

int PicConfig(void);
int Timer1Config(void);
int Timer2Config(void);
int SwConfig(void);
int DacConfig(void);
long sec2clk(float seconds);
int PowerDownConfig(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

