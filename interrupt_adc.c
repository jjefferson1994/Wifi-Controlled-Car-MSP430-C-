///------------------------------------------------------------------------------
//
//File Name : interrupt_adc.c
//  Description: This file contains timers used in the board
//
//
//  John Jefferson
//  Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===============================================================================
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//-------------------------------------------
// interrupt name: Interrupt timers A0
// Description: setsup
//------------------------------------------------------------------------------
// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Thumb;
int adc_case = INIT_TO_ZERO;
extern volatile unsigned int Interrupt_Event;
extern unsigned int ADC_Right_Count;
extern unsigned int ADC_Left_Count;
//-----------------------------------

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
    switch(__even_in_range(ADC10IV,CASE_TWELVE)) {
    case CASE_ZERO:
        break; // No interrupt
    case CASE_TWO:
        break; // conversion result overflow
    case CASE_FOUR:
        break; // conversion time overflow
    case CASE_SIX:
        break; // ADC10HI
    case CASE_EIGHT:
        break; // ADC10LO
    case CASE_TEN:
        break; // ADC10IN

    case CASE_TWELVE:
        Interrupt_Event |= ADC_CASE; //hits the ADC case

        ADC10CTL0 &= ~ADC10ENC; // Turn off the ENC bit of the ADC10CTL0
        switch (adc_case++) {
        case STATE_ZERO:
            ADC10MCTL0 = ADC10INCH_1; // Next channel A1
            ADC_Right_Detector = ADC10MEM0; // Current Channel result for A0
            //ADC_Right_Count++;
            break;
        case STATE_ONE:
            ADC10MCTL0 = ADC10INCH_3; // Next channel A3
            ADC_Left_Detector = ADC10MEM0; // Current Channel result for A1
            break;
        case STATE_TWO:
            ADC10MCTL0 = ADC10INCH_0; // Next channel A0
            ADC_Thumb = ADC10MEM0; // Current Channel result for A3
            adc_case = INIT_TO_ZERO;
            break;
        default:
            break;
        }
        ADC10CTL0 |= ADC10ENC;
        ADC10CTL0 |= ADC10SC; // Sampling and conversion start
        break;
    default:
        break;
    }
}
