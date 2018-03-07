//===========================================================================
// File Name : macros.h
//
// Description: This file contains the macros used by all the other files
//
// Author: John Jefferson
// Date: Sept 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)

// #Serial
#define BEGINNING (0)
#define MESSAGE_LENGTH (9)
#define SW1BAUD (0x5511)
#define SW2BAUD (0x4911)
#define CASE (0x08)

//Number Macros
#define SIZE_0 (0)
#define SIZE_1 (1)
#define SIZE_2 (2)
#define SIZE_3 (3)
#define SIZE_4 (4)
#define SIZE_5 (5)
#define SIZE_7 (7)
#define SIZE_9 (9)
#define SIZE_10 (10)
#define SIZE_11 (11)
#define SIZE_12 (12)
#define SIZE_16 (16)
#define SIZE_52 (52)
#define SIZE_95 (95)
#define SIZE_99 (99)
#define SIZE_100 (100)
#define SIZE_400 (400)
#define SIZE_1000 (1000)

//Boolean
#define TRUE (1)
#define FALSE (0)

//PWM
#define OFF (0)
#define WHEEL_PERIOD (10000)

//Case Statement Macros
#define INIT_TO_ZERO (0x00)
#define SWITCH_1 (0x01)
#define SWITCH_2 (0x02)
#define TIMER_CASE (0x04)
#define ADC_CASE (0x08)
#define PWM_FORWARD (0x10)
#define DISPLAY_UPDATE (0x20)
#define TRANSMIT (0x40)
#define RECEIVE (0x80)

//Timer Macros
#define TA0CCR0_INTERVAL (50000) //400msec
#define TA0CCR1_INTERVAL (0)
#define TA0CCR2_INTERVAL (0)
#define LCD_ON (10)
#define EVERYTHING_OFF (40)
#define TEN_STEPS (10)
#define LCD_BLINK (0x04)
#define NINE_NINE (99)

//Switch Macros
#define SWITCH_1_BOUNCE (0x01)
#define SWITCH_2_BOUNCE (0x02)
#define TIMER_FLAG (0x03)

//ADC
#define ADC_DISPLAY (0x05)
#define ASCIIOFFSET (0x30)

//ADC Interrupt
#define CASE_ZERO (0)
#define CASE_TWO (2)
#define CASE_FOUR (4)
#define CASE_SIX (6)
#define CASE_EIGHT (8)
#define CASE_TEN (10)
#define CASE_TWELVE (12)

//Direction Cases
#define FORWARD (0x10)
#define REVERSE (0x20)
#define FORWARD2 (0x30)
#define REVERSE2 (0x40)
#define Clock_W (0x50)
#define CClock_W (0x60)
#define DELAY_CASE (0xFF)
#define VICTORY (0xEE)

//Timings
#define ONE_SECOND (10)
#define TWO_SECONDS (20)
#define GG_BABY (60)

// LCD
#define LCD_HOME_L1	          0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0

//Port 1
#define V_DETECT_R  (0x01)
#define V_DETECT_L  (0x02)
#define LCD_BACKLITE (0x04)
#define V_THUMB  (0x08)
#define SPI_CS_LCD  (0x10)
#define RESET_LCD  (0x20)
#define SIMO_B  (0x40)
#define SOMI_B  (0x80)

//Port 2
#define USB_TXD  (0x01)
#define USB_RXD  (0x02)
#define SPI_SCK (0x04)
#define UNKNOWN23  (0x08)
#define UNKNOWN24  (0x10)
#define CPU_TXD  (0x20)
#define CPU_RXD  (0x40)
#define UNKNOWN27  (0x80)

//Port 3
#define X  (0x01)
#define Y  (0x02)
#define ZZ (0x04)
#define IR_LED  (0x08)
#define R_FORWARD  (0x10)
#define L_FORWARD  (0x20)
#define R_REVERSE  (0x40)
#define L_REVERSE  (0x80)

//Port 4
#define SW1 (0x01) // Switch 1
#define SW2 (0x02) // Switch 2

//Port J
#define IOT_WAKEUP (0x01) // LED 5
#define IOT_FACTORY (0x02) // LED 6
#define IOT_STA_MINIAP (0x04) // LED 7
#define IOT_RESET (0x08) // LED 8
// XINR (0x10) // XINR
// XOUTR (0x20) // XOUTR

//Drive Times
#define DRIVE5INCHES (250)
#define DRIVE_LENGTH (15)
#define STRAIGHT_ON (5)
#define STRAIGHT_OFF (3)

#define STATE_ZERO (0x00)
#define STATE_ONE (0x01)
#define STATE_TWO (0x02)
#define STATE_THREE (0x03)
#define STATE_FOUR (0x04)
#define STATE_TWELVE (12)

#define R_SPEED (3500)
#define L_SPEED (3700)

//Misc macros
#define DISPLAY_LINE (11)
#define SLEEP_TIME (50)
#define ADD_ONE_TO_TIME (1)
#define WAIT_TWO (2)
#define WAIT_THREE (3)
#define WAIT_FIVE (5)
#define WAIT_FIFTY (50)
#define WAIT_TWO_FIFTY (250)
#define WAIT_ONE_FIFTY (150)
#define WAIT_TWO_HUNDRED (200)
#define WAIT_HUNDRED (100)
#define WAIT_THOUSAND (1000)
#define FOURTH_CASE (4)
#define ENDCASE (14)
#define WAIT_NINE (9)
