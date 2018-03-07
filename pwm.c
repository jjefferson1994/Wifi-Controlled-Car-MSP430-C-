//------------------------------------------------------------------------------
//File Name : direction
//  Description: this file has all of the direction functions
//  John Jefferson
//  Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
//  TB1CCR1 Right motors
//TB1CCR2 Left motors
#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//===========================================================================
// Function name: Stop_All_Motors
// Description: stops all the motors
//===========================================================================
void Stop_All_Motors(void) {
    TB1CCR1 = INIT_TO_ZERO;
    TB1CCR2 = INIT_TO_ZERO;
}

//===========================================================================
// Function name: Pause
// Description: Pauses based off some time
//===========================================================================
void Pause(void) {
    TB1CCR1 = INIT_TO_ZERO;
    TB1CCR2 = INIT_TO_ZERO;

}

//===========================================================================
// Function name: Stop_All_Motors
// Description: stops all the motors
//===========================================================================
void IOTForward(void) {
    //wait(5);
    TB1CCR1 = 8375;
    TB1CCR2 = 8700;
    wait(3);
    Pause();
}

void Left45(void) {
    //wait(5);
    TB1CCR1 = 4375;
    TB1CCR2 = 0;
    wait(2);
    Pause();
}

void Right90(void) {
    //wait(5);
    TB1CCR1 = 0;
    TB1CCR2 = 4200;
    wait(2);
    Pause();
}

void Reverse(void) {
    Pause();
    wait(2);
    P3OUT |= L_REVERSE;
    P3OUT |= R_REVERSE;
    wait(5);
    P3OUT &= ~L_REVERSE;
    P3OUT &= ~R_REVERSE;
    Pause();
}

void LongForward(void) {
    TB1CCR1 = 8375;
    TB1CCR2 = 8700;
    wait(8);
    Pause();
}

//===========================================================================
// Function name: Stop_All_Motors
// Description: stops all the motors
//===========================================================================
void Forward(void) {
    TB1CCR1 = 3000;
    TB1CCR2 = 3250;
}

void Turn_Left(void) {
    TB1CCR1 = 3000;
    TB1CCR2 = 1000;
}

void Turn_Right(void) {
    TB1CCR1 = 900;
    TB1CCR2 = 3250;
}

void Turn_More_Left(void) {
    TB1CCR1 = 3000;
    TB1CCR2 = 900;
}

void Turn_More_Right(void) {
    TB1CCR1 = 700;
    TB1CCR2 = 3250;
}
