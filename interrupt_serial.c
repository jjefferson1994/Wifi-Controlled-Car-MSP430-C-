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
#include <string.h>

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile unsigned int Interrupt_Event;
extern volatile char USB_Receive_Message[200];
extern int USB_Receive_Count;
extern int USB_Transmit_Count;
extern volatile char IOT_Trans_Message[MESSAGE_LENGTH];
extern char IOT_Receive_Message[8];
extern char Received[MESSAGE_LENGTH+1];
extern char USB_Trans_Message[MESSAGE_LENGTH];
extern int IOT_Receive_Count;
extern int IOT_Transmit_Count;
extern int ready_to_TX;
extern char command[3];
int command_ring = 0;
extern int command_ready;
int IOT_command_ring = 0;
extern char IOT_command[3];
extern int IOT_command_ready;
extern char disassociation[8];
extern char IPAddr[8];
extern char dispIPAddr[30];
extern int reconnect;
extern volatile int check_IOT_Status;
extern int IPcount=0;
//------------------------------------------------------------------------------

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) { //USB communiaation
    unsigned int temp;
    switch(__even_in_range(UCA0IV,CASE)) {
    case CASE_ZERO: // Vector 0 - no interrupt
        break;
    case CASE_TWO: // Vector 2 - RXIFG
        if(UCRXIFG) {
            Interrupt_Event |= RECEIVE;
            ready_to_TX = TRUE;

            temp = USB_Receive_Count;

            Received[temp] = USB_Receive_Message[temp] = command[command_ring] = UCA1TXBUF = UCA0RXBUF;
            USB_Receive_Count++;
            command_ring++;
            USB_Transmit_Count = USB_Receive_Count;
            //USB_Trans_Message[USB_Receive_Count] = USB_Receive_Message[USB_Receive_Count];


            if(USB_Receive_Count > MESSAGE_LENGTH-1) {
                USB_Receive_Count = INIT_TO_ZERO;
            }
            if(command_ring == 3) {
                command_ready = TRUE;
                command_ring = INIT_TO_ZERO;
            }
        }
        break;
    case CASE_FOUR: // Vector 4 – TXIFG
        if(UCTXIFG && ready_to_TX) {
            Interrupt_Event |= TRANSMIT;
        }
        break;
    default:
        break;
    }
}
//-------------------------------------------------------------------

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void) { //USB communiaation
    //unsigned int temp;
    switch(__even_in_range(UCA1IV,CASE)) {
    case CASE_ZERO: // Vector 0 - no interrupt
        break;
    case CASE_TWO: // Vector 2 - RXIFG
        if(UCRXIFG) {
            if(ready_to_TX) {
                //IOT_Receive_Message[7] = '\0';

                dispIPAddr[IPcount] = IOT_Receive_Message[IOT_Receive_Count] = IOT_command[IOT_command_ring] = UCA0TXBUF = UCA1RXBUF;

                IOT_command_ring++;


                if(IOT_command_ring == 3) {
                    IOT_command_ready = TRUE;
                    IOT_command_ring = INIT_TO_ZERO;
                }

                if(IOT_Receive_Message[0] == '+') {
                    IOT_Receive_Count++;
                    if(IOT_Receive_Count == 8) {
                        if(disassociation[6] == IOT_Receive_Message[6] && disassociation[7] == IOT_Receive_Message[7]) {
                            check_IOT_Status = 41;
                        }
                        if(IPAddr[6] == IOT_Receive_Message[6] && IPAddr[7] == IOT_Receive_Message[7]) {
                            check_IOT_Status = 24;
                        }
                        IOT_Receive_Count = INIT_TO_ZERO;
                    }
                }

                if(dispIPAddr[0] == '#') {
                    IPcount++;
                    if(IPcount == 28) {
                        dispIPAddr[29] = '\0';
                        IPcount = 0;
                        display_3 = &dispIPAddr[9];
                        display_4 = &dispIPAddr[19];
                    }
                }

                //Interrupt_Event |= TRANSMIT;
                /*
                temp = USB_Receive_Count;
                IOT_Receive_Message[temp] = UCA1RXBUF;
                IOT_Trans_Message[temp] = IOT_Receive_Message[temp];
                IOT_Receive_Count++;
                if(IOT_Receive_Count > SIZE_7){
                IOT_Receive_Count = INIT_TO_ZERO;
                }
                */
            }
        }
        break;
    case CASE_FOUR: // Vector 4 – TXIFG
        if(UCTXIFG) {
            /*
            //Interrupt_Event |= TRANSMIT;
            //UCA1TXBUF = USB_Trans_Message[IOT_Transmit_Count];
            IOT_Transmit_Count++;
            if(IOT_Transmit_Count > SIZE_7){
            IOT_Transmit_Count = INIT_TO_ZERO;
            }
            }
            */
            break;
        default:
            break;
        }
    }
}
//-------------------------------------------------------------------
