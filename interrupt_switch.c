//------------------------------------------------------------------------------
//File Name : interrupt_ports.c
//  Description: This file contains timers used in the board
//
//
//  John Jefferson
//  Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===============================================================================

#include "msp430.h"
#include "functions.h"
#include "macros.h"

extern volatile  unsigned int Interrupt_Event;
extern volatile  unsigned int OFlow_Count;
//===============================================================================
// interrupt name: Interrupt switches
// Description: setsup
//-------------------------------------------------------------------------------------
#pragma vector = PORT4_VECTOR
__interrupt void switch_interrupt(void) {
    // Switch 1
    if (P4IFG & SW1) {
        Interrupt_Event |= SWITCH_1;
        P4IFG &= ~SW1;  //Clear SW1 interrupt flag
    }
    // Switch 2
    if (P4IFG & SW2) {
        Interrupt_Event |= SWITCH_2;
        P4IFG &= ~SW2;
    }
}
