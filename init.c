//------------------------------------------------------------------------------
//File Name : init.c
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  John Jefferson
//  Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern char display_line_1[DISPLAY_LINE];
extern char display_line_2[DISPLAY_LINE];
extern char display_line_3[DISPLAY_LINE];
extern char display_line_4[DISPLAY_LINE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile char USB_Trans_Message[MESSAGE_LENGTH];
extern volatile char USB_Receive_Message[200];
extern int USB_Receive_Count;
extern int USB_Transmit_Count;
extern volatile char IOT_Trans_Message[MESSAGE_LENGTH];
extern char IOT_Receive_Message[8];
extern int IOT_Receive_Count;
extern int IOT_Transmit_Count;
//===========================================================================
// Function name: Init_Conditons
//
// Description: initializes the timers
//===========================================================================
void Init_Conditions(void) {
    enable_interrupts();
    display_1 = &display_line_1[INIT_TO_ZERO];
    display_2 = &display_line_2[INIT_TO_ZERO];
    display_3 = &display_line_3[INIT_TO_ZERO];
    display_4 = &display_line_4[INIT_TO_ZERO];
}

//===========================================================================
// Function name: Init_Timers
// Description: initializes the timers
//===========================================================================
void Init_Timers(void) {
    Init_Timer_A0(); //
    //  Init_Timer_A1(); //
    //  Init_Timer_B0(); //
    Init_Timer_B1(); //
    //  Init_Timer_B2();   //  Required for provided compiled code to work
}

//===========================================================================
// Function name: Init_ADC
// Description: initializes the ADC
//===========================================================================
void Init_ADC(void) {
    ADC10CTL0 = INIT_TO_ZERO; // Clear ADC10CTL0
    ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
    ADC10CTL0 &= ~ADC10MSC; // Single Sequence
    ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled

    ADC10CTL1 = INIT_TO_ZERO; // Clear ADC10CTL1
    ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
    ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
    ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
    ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
    ADC10CTL1 |= ADC10SSEL_0; // MODCLK
    ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion

    ADC10CTL2 = INIT_TO_ZERO; // Clear ADC10CTL2
    ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
    ADC10CTL2 |= ADC10RES; // 10-bit resolution
    ADC10CTL2 &= ~ADC10DF; // Binary unsigned
    ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps

    ADC10MCTL0 = INIT_TO_ZERO; // Clear ADC10MCTL0
    ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
    ADC10MCTL0 |= ADC10INCH_0; // Channel A0 Right Detect
    ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}

//===========================================================================
// Function name: Init_Timers
// Description: initilizes timers-
//------------------------------------------------------------------------------
// Timer A0 initialization sets up both A0_0 and A0_1-A0_2
void Init_Timer_A0(void) {
    TA0CTL = TASSEL__SMCLK; // SMCLK source
    TA0CTL |= TACLR; // Resets TA0R, clock divider, count direction
    TA0CTL |= MC__UP; // up
    TA0CTL |= ID__8; // Divide clock by 8
    TA0CTL &= ~TAIE; // Disable Overflow Interrupt
    TA0CTL &= ~TAIFG; // Clear Overflow Interrupt flag
    TA0EX0 = TAIDEX_7; // Divide clock by an additional 8
    TA0CCR0 = TA0CCR0_INTERVAL; // CCR0
    TA0CCTL0 |= CCIE; // CCR0 enable interrupt*/
    // TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
    // TA0CCTL1 |= CCIE; // CCR1 enable interrupt
    // TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
    // TA0CCTL2 |= CCIE; // CCR2 enable interrupt
}

void Init_Timer_B1(void) {
    TB1CTL = TBSSEL__SMCLK; //source SMCLK
    TB1CTL |= TBCLR; //clear

    TB1CTL |= MC__UP; //Timer mode

    //CCR0
    TB1CCR0 = WHEEL_PERIOD; //PWM period

    //CCR1
    TB1CCTL1 = OUTMOD_7; //CCR1 reset/set
    TB1CCR1 = OFF; //R_FORWARD PWM duty cycle

    //CCR2
    TB1CCTL2 = OUTMOD_7; //CCR2 reset/set
    TB1CCR2 = OFF; //L_FORWARD PWM duty cycle

    //overflow
    TB1CTL &= ~TBIE; //Disable the overflow interrupt
    TB1CTL &= ~TBIFG; //Clear the interrupt flag

}


void Init_Serial_UCA0(void) { //USB
    int i;
    for(i=INIT_TO_ZERO; i<MESSAGE_LENGTH; i++) {
        USB_Receive_Message[i] = INIT_TO_ZERO; // USB Rx Buffer
    }
    USB_Receive_Count = INIT_TO_ZERO;
    USB_Transmit_Count = INIT_TO_ZERO;

    // Configure UART 0
    UCA0CTLW0 = INIT_TO_ZERO; // Use word register
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA0CTLW0 |= UCSWRST; // Set Software reset enable

    UCA0BRW = SIZE_52; // 9,600 Baud
    UCA0MCTLW = SW2BAUD;
    UCA0CTL1 &= ~UCSWRST; // Release from reset

    UCA0IE |= UCRXIE; // Enable RX interrupt
    //UCA0IE |= UCTXIE; //Enable TX interrupt
}

void Init_Serial_UCA1(void) { //USB
    int i;
    for(i=INIT_TO_ZERO; i<MESSAGE_LENGTH; i++) {
        IOT_Receive_Message[i] = INIT_TO_ZERO; // USB Rx Buffer
    }
    IOT_Receive_Count = INIT_TO_ZERO;
    IOT_Transmit_Count = INIT_TO_ZERO;

    // Configure UART 0
    UCA1CTLW0 = INIT_TO_ZERO; // Use word register
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA1CTLW0 |= UCSWRST; // Set Software reset enable

    UCA1BRW = SIZE_52; // 9,600 Baud
    UCA1MCTLW = SW2BAUD;
    UCA1CTL1 &= ~UCSWRST; // Release from reset

    UCA1IE |= UCRXIE; // Enable RX interrupt
}
