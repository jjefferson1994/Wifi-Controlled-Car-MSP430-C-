//------------------------------------------------------------------------------
//
//File Name : ports.c
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  John Jefferson
//  Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
//===========================================================================
// Function name: Init_Ports
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared

//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===========================================================================
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ();
}

//===========================================================================
// Function name: Init_Port1
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared

//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===========================================================================
void Init_Port1(void){
  /*Configure Port 1 ---------------------------------------------------------------
  V_DETECT_R  (0x01)
  V_DETECT_L  (0x02)
  LCD_BACKLITE (0x04)
  V_THUMB  (0x08)
  SPI_CS_LCD  (0x10)
  RESET_LCD  (0x20)
  SIMO_B  (0x40)
  SOMI_B  (0x80)
  ---------------------------------------------------------------------------------*/
  P1SEL0 = 0x00;     //P1 Set as I/0
  P1SEL1 = 0x00;    //P1 set as I/0
  P1DIR = 0x00;     //Set P1 direction to input

  P1SEL0 |= V_DETECT_R;  //V_DETECT_R selected
  P1SEL1 |= V_DETECT_R;  //V_DETECT_R selected

  P1SEL0 |= V_DETECT_L;  //V_DETECT_L selected
  P1SEL1 |= V_DETECT_L;  //V_DETECT_L selected

  P1SEL0 &= ~LCD_BACKLITE; // LCD_BACKLITE GPI/O selected
  P1SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE GPI/O selected
  P1OUT &= ~LCD_BACKLITE ; // LCD_BACKLITE Port Pin set low
  P1DIR |= LCD_BACKLITE ; // Set LCD_BACKLITE direction to output

  P1SEL0 |= V_THUMB; // V_THUMB selected
  P1SEL1 |= V_THUMB; // V_THUMB selected

  P1SEL0 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
  P1SEL1 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
  P1OUT |= SPI_CS_LCD; // SPI_CS_LCD Port Pin set high
  P1DIR |= SPI_CS_LCD; // Set SPI_CS_LCD output direction

  P1SEL0 &= ~RESET_LCD; // RESET_LCD GPI/O selected
  P1SEL1 &= ~ RESET_LCD; // RESET_LCD GPI/O selected
  P1OUT &= ~ RESET_LCD; // RESET_LCD Port Pin set low
  P1DIR |= RESET_LCD; // Set RESET_LCD output direction

  P1SEL0 &= ~SIMO_B; // SIMO_B selected
  P1SEL1 |= SIMO_B; // SIMO_B selected
  P1DIR |= SIMO_B; // SIMO_B set to Output

  P1SEL0 &= ~SOMI_B; // SOMI_B is used on the LCD
  P1SEL1 |= SOMI_B; // SOMI_B is used on the LCD
  P1OUT |= SOMI_B; // SOMI_B Port Pin set for Pull-up
  P1DIR &= ~SOMI_B; // SOMI_B set to Input
  P1REN |= SOMI_B; // Enable pullup resistor
  //------------------------------------------------------------------------------
}

//===========================================================================
// Function name: Init_Port2
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared

//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===========================================================================
void Init_Port2(void){
  /*Configure Port 2 ---------------------------------------------------------------
  USB_TXD  (0x01)
  USB_RXD  (0x02)
  SPI_SCK (0x04)
  UNKNOWN23  (0x08)
  UNKNOWN24  (0x10)
  CPU_TXD  (0x20)
  CPU_RXD  (0x40)
  UNKNOWN27  (0x80)
  ---------------------------------------------------------------------------------*/
  P2SEL0 = 0x00;     //P2 Set as I/0
  P2SEL1 = 0x00;    //P2 set as I/0
  P2DIR = 0x00;     //Set P2 direction to input

  P2SEL0 &= ~USB_TXD;  //USB_TXD selected
  P2SEL1 |= USB_TXD;  //USB_TXD selected 2.0
  P2DIR |= USB_TXD;	//Sets USB_TXD high
  P1OUT &= ~ USB_TXD; //sets output low

  P2SEL0 &= ~USB_RXD;  //USB_RXD selected
  P2SEL1 |= USB_RXD;  //USB_RXD selected 2.1
  P2DIR &= ~USB_RXD;	//USB_RXD set as input
  P2OUT &= ~USB_RXD;  //set output low for pulldown
  P2REN |= USB_RXD;	//resistor enabled

  P2SEL0 &= ~SPI_SCK; // SPI_SCK selected
  P2SEL1 |= SPI_SCK; // SPI_SCK selected 2.2
  P2OUT |= SPI_SCK ; // SPI_SCK set high
  P2DIR |= SPI_SCK; // Set direction to output

  P2SEL0 &= ~UNKNOWN23; // Sets unknown GPI/O
  P2SEL1 &= ~UNKNOWN23; // Sets unknown GPI/O
  P2DIR &= ~UNKNOWN23; //sets as input
  P2OUT &= ~UNKNOWN23; //sets output low
  P2REN |= UNKNOWN23;	//pulldown resistor

  P2SEL0 &= ~UNKNOWN24; // Sets unknown GPI/O
  P2SEL1 &= ~UNKNOWN24; // Sets unknown GPI/O
  P2DIR &= ~UNKNOWN24; //sets as input
  P2OUT &= ~UNKNOWN24; //sets output low
  P2REN |= UNKNOWN24;	//pulldown resistor

  P2SEL0 &= ~ CPU_TXD; // CPU_TXD selected
  P2SEL1 |= CPU_TXD; // CPU_TXD selected
  P2DIR |= CPU_TXD; // Set CPU_TXD output direction
  P2OUT &= ~ CPU_TXD; //sets as output

  P2SEL0 &= ~ CPU_RXD; // CPU_TXD selected
  P2SEL1 |= CPU_RXD; // CPU_TXD selected
  P2OUT &= ~CPU_RXD; // CPU_TXD Port Pin set low for pulldown
  P2DIR &= ~CPU_RXD; // Set CPU_TXD output direction
  P2REN |= CPU_RXD; //enables pulldown resistor

  P2SEL0 &= ~UNKNOWN27; // Sets unknown GPI/O
  P2SEL1 &= ~UNKNOWN27; // Sets unknown GPI/O
  P2DIR &= ~UNKNOWN27; //sets as input
  P2OUT &= ~UNKNOWN27; //sets output low
  P2REN |= UNKNOWN27;	//pulldown resistor
  //------------------------------------------------------------------------------
}

//===========================================================================
// Function name: Init_Port3
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared

//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===========================================================================
void Init_Port3(void){
  /*Configure Port 3 ---------------------------------------------------------------
  X  (0x01)
  Y  (0x02)
  Z (0x04)
  IR_LED  (0x08)
  R_FORWARD  (0x10)
  L_FORWARD  (0x20)
  R_REVERSE  (0x40)
  L_REVERSE  (0x80)
  ---------------------------------------------------------------------------------*/
  P3SEL0 = 0x00;     //P3 Set as I/0
  P3SEL1 = 0x00;    //P3 set as I/0
  P3DIR = 0x00;     //Set P3 direction to input

  P3SEL0 &= ~ X;  //X selected
  P3SEL1 &= ~ X;  //X selected
  P3DIR &= ~X; //input
  P3REN |= X; //pulldown
  P3OUT &= ~X; //output set low

  P3SEL0 &= ~ Y;  //Y selected
  P3SEL1 &= ~ Y;  //Y selected
  P3DIR &= ~ Y;  //input
  P3REN |= Y; //pulldown
  P3OUT &= ~Y; //output set low

  P3SEL0 &= ~ZZ; // Z GPI/O selected
  P3SEL1 &= ~ZZ; // Z GPI/O selected
  P3DIR &= ~ ZZ; // input
  P3REN |= ZZ; //pulldown
  P3OUT &= ~ZZ; //output set low

  P3SEL0 &= ~ IR_LED; // IR_LED selected
  P3SEL1 &= ~ IR_LED; // IR_LED selected
  P3DIR |= IR_LED; // set as output
  P3OUT &= ~ IR_LED; //output set low

  P3SEL0 |= R_FORWARD; // R_FORWARD ,  TB1.1
  P3SEL1 &= ~R_FORWARD; // R_FORWARD
  P3DIR |= R_FORWARD; // Set R_FORWARD output direction
  //P3OUT &= ~ R_FORWARD; //output set to low

  P3SEL0 |= L_FORWARD; // L_FORWARD TB1.2
  P3SEL1 &= ~ L_FORWARD; // L_FORWARD
  //P3OUT &= ~ L_FORWARD; // L_FORWARD Port Pin set low
  P3DIR |= L_FORWARD; // Set L_FORWARD output direction

  P3SEL0 &= ~ R_REVERSE; // R_REVERSE selected
  P3SEL1 &= ~ R_REVERSE; // R_REVERSE selected
  P3DIR |= R_REVERSE; // R_REVERSE set to Output
  //P3OUT &= ~ R_REVERSE; //R_REVERSE port pin set low

  P3SEL0 &= ~L_REVERSE; // L_REVERSE is used
  P3SEL1 &= ~ L_REVERSE; // L_REVERSE is used
  //P3OUT &= ~ L_REVERSE; // L_REVERSE Port Pin set for Pull-up
  P3DIR |= L_REVERSE; // L_REVERSE set to output
  //------------------------------------------------------------------------------
}

//===========================================================================
// Function name: Init_Port4
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared

//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===========================================================================
void Init_Port4(void){
  //------------------------------------------------------------------------------
  // Configure PORT 4
  // Port 4 has only two pins
  // Port 4 Pins
  // SW1 (0x01) // Switch 1
  // SW2 (0x02) // Switch 2
  //------------------------------------------------------------------------------
  P4SEL0 = 0x00; // P4 set as I/0
  P4SEL1 = 0x00; // P4 set as I/0
  P4DIR = 0x00; // Set P4 direction to input
  P4OUT = 0x00;

  // SW1
  P4SEL0 &= ~SW1; // SW1 set as I/0
  P4SEL1 &= ~SW1; // SW1 set as I/0
  P4OUT |= SW1; // Configure pullup resistor
  P4DIR &= ~SW1; // Direction = input
  P4REN |= SW1; // Enable pullup resistor
  P4IES |= SW1; // SW1 Hi/Lo edge interrupt
  P4IFG &= ~SW1; // IFG SW1 cleared
  P4IE |= SW1; // SW1 interrupt Enabled
  // SW2
  P4SEL0 &= ~SW2; // SW2 set as I/0
  P4SEL1 &= ~SW2; // SW2 set as I/0
  P4OUT |= SW2; // Configure pullup resistor
  P4DIR &= ~SW2; // Direction = input
  P4REN |= SW2; // Enable pullup resistor
  P4IES |= SW2; // SW2 Hi/Lo edge interrupt
  P4IFG &= ~SW2; // IFG SW2 cleared
  P4IE |= SW2; // SW2 interrupt Enabled
  //------------------------------------------------------------------------------
}

//===========================================================================
// Function name: Init_PortJ
//
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
//
// Passed : no variables passed
// Locals: no variables declared

//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//===========================================================================
void Init_PortJ(void){
  //------------------------------------------------------------------------------
  // Port J Pins
  // IOT_WAKEUP (0x01) // LED 5
  // IOT_FACTORY (0x02) // LED 6
  // IOT_STA_MINIAP (0x04) // LED 7
  // IOT_RESET (0x08) // LED 8
  // XINR (0x10) // XINR
  // XOUTR (0x20) // XOUTR
  //------------------------------------------------------------------------------
  PJSEL0 = 0x00; // PJ set as I/0
  PJSEL1 = 0x00; // PJ set as I/0
  PJDIR = 0x00; // Set PJ direction to output

  PJSEL0 &= ~IOT_WAKEUP;
  PJSEL1 &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_WAKEUP;
  PJDIR |= IOT_WAKEUP; // Set PJ Pin 1 direction to output

  PJSEL0 &= ~IOT_FACTORY;
  PJSEL1 &= ~IOT_FACTORY;
  PJOUT &= ~IOT_FACTORY;
  PJDIR |= IOT_FACTORY; // Set PJ Pin 2 direction to output

  PJSEL0 &= ~IOT_STA_MINIAP;
  PJSEL1 &= ~IOT_STA_MINIAP;
  PJOUT |= IOT_STA_MINIAP;
  PJDIR |= IOT_STA_MINIAP; // Set PJ Pin 3 direction to output

  PJSEL0 &= ~IOT_RESET;
  PJSEL1 &= ~IOT_RESET;
  PJDIR |= IOT_RESET; // Set P3 Pin 4 direction to output
  PJOUT &= ~IOT_RESET;

  // XT1 Setup
  // PJSEL0 |= XINR;
  // PJSEL0 |= XOUTR;
  //------------------------------------------------------------------------------
}


//The control PORT and PINS for the board *Please cross reference with data sheet before changing*
//===========================================================================
// Init_Port1
// Purpose: Initialize Port 1
//
// Various options for Pin 0
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR1 capture: CCI1A input
// 0 1 1 - TA0 CCR1 compare: Out1
// 1 0 0 - External DMA trigger
// 1 0 1 - RTC clock calibration output
// 1 1 X - Analog input A0 - ADC, Comparator_D input CD0, Vref- External applied reference
//
// Various options for Pin 1
// SEL0 SEL1 DIR
// 0 0 I:0 0:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA0 CCR2 capture: CCI2A input,
// 0 1 1 - TA0 CCR2 compare: Out2
// 1 0 0 - TA1 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A1 - ADC, Comparator_D input CD1, Input for an external reference voltage to the ADC
//
// Various options for Pin 2
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR1 capture: CCI1A input
// 0 1 1 - TA1 CCR1 compare: Out1
// 1 0 0 - TA0 input clock
// 1 0 1 - Comparator_D output
// 1 1 X - Analog input A2 - ADC, Comparator_D input CD2
//
// Various options for Pin 3
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TA1 CCR2 capture: CCI2A input
// 0 1 1 - TA1 CCR2 compare: Out2
// 1 0 X - Slave transmit enable - eUSCI_B0 SPI mode
// 1 1 X - Analog input A3 - ADC, Comparator_D input CD3
//
// Various options for Pin 4
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCR1 capture: CCI1A input
// 0 1 1 - TB0 CCR1 compare: Out1
// 1 0 X - Slave transmit enable - eUSCI_A0 SPI mode
// 1 1 X - Analog input A4 - ADC, Comparator_D input CD4
//
// Various options for Pin 5
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB0 CCR2 capture: CCI2A input
// 0 1 1 - TBO CCR2 compare: Out2
// 1 0 X - Clock signal input - eUSCI_A0 SPI slave, Clock signal output - eUSCI_A0 SPI master
// 1 1 X - Analog input A5 - ADC, Comparator_D input CD5
//
// Various options for Pin 6
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1 CCR1 capture: CCI1A input
// 0 1 1 - TB1 CCR1 compare: Out1
// 1 0 X - *Slave in, master out - eUSCI_B0 SPI mode, I2C data - eUSCI_B0 I2C mode
// 1 1 0 - TA0 CCR0 capture: CCI0A input
// 1 1 1 - TA0 CCR0 compare: Out0
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5
// 0 1 0 - TB1 CCR2 capture: CCI2A input
// 0 1 1 - TB1 CCR2 compare: Out2 (not available on devices without TB1)
// 1 0 X - Slave out, master in - eUSCI_B0 SPI mode, I2C clock - eUSCI_B0 I2C mode
// 1 1 0 - TA1 CCR0 capture: CCI0A input
// 1 1 1 - TA1 CCR0 compare: Out0
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------

//===========================================================================
// Init_Port2  //Update this later
// Purpose: Initialize Port 2
//
// Various options for Pin 0
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TB2.CCI0!
// 1 0 1- TB2.0
// X 1 0- UCATXD
// 0 1 1- TB0CLK
// 1 1 1- ACLK

// Various options for Pin 1
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TB2.CCI1A
// 1 0 1- TB2.1
// X 1 0- UCARXD
// 0 1 1- TB0.CCI0A
// 1 1 1- TB0.0

// Various options for Pin 2
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TB2.CCI2A
// 1 0 1- TB2.2
// X 1 0- UCB0CLK
// 0 1 1- TB1.CCI0A
// 1 1 1- TB1.0

// Various options for Pin 3
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TA0.CCI0B
// 1 0 1- TA0.0
// X 1 0- UCA1STE
// X 1 1- AB or CD10
//
// Various options for Pin 4
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TA1.CCI0B
// 1 0 1- TA1.0
// X 1 0- UCA1CLK
// X 1 1- A7 or CD11
//
//
// Various options for Pin 5
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TB1.CCI0B
// 1 0 1- TB1.0
// X 1 0- UCA1TXD/SIMO

// Various options for Pin 6
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TB1.CCI0B
// 1 0 1- TB1.0
// X 1 0- UCA1TXD/SIMO
//
// Various options for Pin 7
// SEL0 SEL1 DIR
// 0 0 I:0 O:1 - *General-purpose digital I/O with port interrupt and wake up from LPMx.5

//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------

//===========================================================================
// Init_Port3  //Update this later
// Purpose: Initialize Port 3
//
// Various options for Pin 0
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X 1 1- A12 or CD12
//
// Various options for Pin 1
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X 1 1- A13 or CD13
//
// // Various options for Pin 2
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X 1 1- A14 or CD14
//
//// Various options for Pin 3
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X 1 1- A15 or CD15
//
/// Various options for Pin 4
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
//0 0 1- TB1.CCI1B
//1 0 1- TB1.1
//0 1 1-TB2CLK
//1 1 1-SMCLK
//
///// Various options for Pin 5
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
//0 0 1- TB1.CCI2B
//1 0 1- TB1.2
//0 1 1-TB2CLK
//1 1 1-CDOUT
//
///// Various options for Pin 6
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
//0 0 1- TB2.CCI1B
//1 0 1- TB2.1
//
///// Various options for Pin 7
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
//0 0 1- TB2.CCI2B
//1 0 1- TB2.2
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------

//===========================================================================
// Init_Port4  //Update this later
// Purpose: Initialize Port 4
//
// Various options for Pin 0
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// 0 0 1- TB2.CCI0B
//1 0 1- TB2.0
//
// Various options for Pin 1
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------

//===========================================================================
// Init_PortJ  //Update this later
// Purpose: Initialize Port 2
//
// Various options for Pin 0
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X X X- TDO
// 0 0 1- TB0OUTH
// 1 0 0- SMCLK
// X 1 1- CD6
//
//
// Various options for Pin 1
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X X X- TCI/TCLK
// 0 0 1- TB1OUTH
// 1 0 0- MCLK
// X 1 1- CD7

// Various options for Pin 2
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X X X- TMS
// 0 0 1- TB2OUTH
// 1 0 0- ACLK
// X 1 1- CD8

// Various options for Pin 3
// P2DIR.x P2SEL1.x P2SEL0.x
//I:0, O:1 0 0 - GPI/O
// X X X - TCK
// X 1 1- CD9
//
//
// Passed: No variables passed
// Locals: No local variables
// Returned: No values returned
//
// Author: John Jefferson
// Date: Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
// Version: 1.0
//-----------------------------------------------------------------------------
