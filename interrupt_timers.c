///------------------------------------------------------------------------------
//
//File Name : interrupt_imers.c
//  Description: This file contains timers used in the board
//
//
//  John Jefferson
//  Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===================================================================
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


extern volatile unsigned int Interrupt_Event;
extern volatile unsigned int OFlow_Count;
extern volatile unsigned int PWM_Count;
extern volatile unsigned int splash_timer;
extern unsigned int wait_count;
extern int unsigned reconnect_timer;
extern int unsigned timer;
//===================================================================
// interrupt name: Interrupt timers A0
// Description: setsup
//------------------------------------------------------------------------------
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void) { //
    if(TA0CTL & CCIFG) {
        splash_timer++;
        wait_count++;
        timer++;
        reconnect_timer++;
        Interrupt_Event |= DISPLAY_UPDATE;
        TA0CTL &= ~CCIFG; //clears the overflow flag
        //Interrupt_Event = TIMER_FLAG;
    }
}
/*
//----------------------------------------------------------------------------
// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
switch(__even_in_range(TA0IV,ENDCASE)){
case INIT_TO_ZERO: break; // No interrupt
case WAIT_TWO: // CCR1 not used
//...... Add What you need happen in the interrupt ......
TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
break;
case FOURTH_CASE: // CCR2 not used
//...... Add What you need happen in the interrupt ......
TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
break;
case ENDCASE: // overflow
//...... Add What you need happen in the interrupt ......
break;
default: break;
}
}
*/

#pragma vector = TIMER1_B1_VECTOR
__interrupt void TimerB1_1_ISR(void) {
    switch(__even_in_range(TB1IV,CASE_TWELVE)) {
    case CASE_ZERO:
        break; // No interrupt
    case CASE_TWO:
        if(TB1CTL & CCIFG) {
            PWM_Count++;
            Interrupt_Event |= PWM_FORWARD;
            TB1CTL &= ~CCIFG;
        }
        break;
    case CASE_FOUR:
        if(TB1CTL & CCIFG) {
            Interrupt_Event |= PWM_FORWARD;
            TB1CTL &= ~CCIFG;
        }
        break;
    case CASE_SIX:
        break;
    case CASE_EIGHT:
        break;
    case CASE_TEN:
        break;
    case CASE_TWELVE:
        break;
    default:
        break;
    }
}
