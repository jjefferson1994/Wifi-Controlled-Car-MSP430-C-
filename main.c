//------------------------------------------------------------------------------
//
//File Name : main.c
//Description: This file contains the Main Routine - "While" Operating System
//
//
//  John Jefferson
//  Sept 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

// Global Variables
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char display_line_1[DISPLAY_LINE];
extern char display_line_2[DISPLAY_LINE];
extern char display_line_3[DISPLAY_LINE];
extern char display_line_4[DISPLAY_LINE];
char posL1;
char posL2;
char posL3;
char posL4;
volatile unsigned int Interrupt_Event;
volatile unsigned int OFlow_Count;
volatile unsigned int PWM_Count;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Left_Detector;
extern unsigned volatile int ADC_Thumb;
char adc_char[SIZE_4];
char adc_string_right[SIZE_5];
char adc_string_left[SIZE_5];
unsigned int temp_HEX_right;
unsigned int temp_HEX_left;
unsigned int temp_THUMB;
unsigned int HEX_right=INIT_TO_ZERO;
unsigned int HEX_left=INIT_TO_ZERO;
unsigned int ADC_Right_Count;
unsigned int ADC_Left_Count;
int i,j;
unsigned int BLBL_Count;
unsigned int CURR_STATE = INIT_TO_ZERO;
unsigned int PREV_STATE = INIT_TO_ZERO;
unsigned int DETECT = FALSE;
volatile unsigned int splash_timer;
char USB_Trans_Message[MESSAGE_LENGTH];
char Received[MESSAGE_LENGTH + SIZE_1];
volatile char USB_Receive_Message[200];
int USB_Receive_Count;
int USB_Transmit_Count;
unsigned int wait_count;
volatile char IOT_Trans_Message[MESSAGE_LENGTH];
char IOT_Receive_Message[8];
int IOT_Receive_Count = 0;
int IOT_Transmit_Count = 0;
int ready_to_TX;
char command[3];
int command_ready = FALSE;
int IOT_command_ready = FALSE;
char * getACK = "AT\r";
char * setBAUD = "AT+S.SCFG=console1_speed,9600\r";
char * saveMEM = "AT&W\r";
char * resetIOT = "AT+CFUN=1\r";
char * getMAC = "AT+S.GCFG=nv_wifi_macaddr\r";
char * setSSID = "AT+S.SSIDTXT=ncsu\r";
char * getSSID = "AT+S.SSIDTXT\r";
char * setNAME = "AT+S.SCFG=ip_hostname,ECE-306_18_J\r";
char * getNAME = "AT+S.GCFG=ip_hostname\r";
char * setPrivacy = "AT+S.SCFG=wifi_priv_mode,0\r"; //0=none, 1=WEP, 2=WPA-Personal (TKIP/AES) or WPA2-Personal (TKIP/AES)
char * getPrivacy = "AT+S.GCFG=wifi_priv_mode\r";
char * setNETWORK = "AT+S.SCFG=wifi_mode,1\r"; //1 = STA, 2 = IBSS, 3 = MiniAP
char * getNETWORK = "AT+S.GCFG=wifi_mode\r";
char * checkStatus = "AT+S.STS\r"; //displays the variables of the board
char * getIP = "AT+S.STS=ip_ipaddr\r";
char disassociation[8] = "+WIND:41";
char IPAddr[8] = "+WIND:24";
int size;
char IOT_command[3];
int reconnect = FALSE;
int unsigned reconnect_timer;
int volatile check_IOT_Status;
char dispIPAddr[30];
int unsigned timer=0;
int unsigned temp_timer;
int timer_array[5];
char timer_char_array[5];
char timer_display[6];

void main(void) {
    //------------------------------------------------------------------------------
    // Main Program
    // This is the main routine for the program. Execution of code starts here.
    // The operating system is Back Ground Fore Ground.
    //
    //------------------------------------------------------------------------------
    Init_Ports();                             // Initialize Ports
    Init_Clocks();                            // Initialize Clock System
    Init_Conditions();
    Init_Timers();                            // Initialize Timers
    Init_LCD();
    Init_ADC();
    Init_Serial_UCA0(); // Initialize Serial Port for USB
    Init_Serial_UCA1(); // Initialize Serial Port for USB


    //Stop_All_Motors();
    Interrupt_Event = INIT_TO_ZERO;
    PWM_Count = INIT_TO_ZERO;
    ADC_Right_Count = INIT_TO_ZERO;
    ADC_Left_Count = INIT_TO_ZERO;
    BLBL_Count = INIT_TO_ZERO;
    P3OUT &= ~ IR_LED; //output set low
    //ADC10CTL0 |= ADC10ENC;
    //ADC10CTL0 |= ADC10SC; // Sampling and conversion start
    ready_to_TX = FALSE;


    //------------------------------------------------------------------------------
    // Begining of the "While" Operating System
    //------------------------------------------------------------------------------
    while(ALWAYS) {

        if(splash_timer < SIZE_5) {
            display_1 = "Project8";					//Starts the LCD saying these messages
            posL1 = SIZE_0;
            display_2 = " ";
            posL2 = SIZE_1;
            display_3 = "jajeffe2";
            posL3 = SIZE_0;
            display_4 = " ";
            posL4 = SIZE_0;
            PJOUT |= IOT_RESET;
            UCA1BRW = SIZE_52;
            UCA1MCTLW = SW2BAUD;
        }

        if(splash_timer > 15) {
            ready_to_TX = TRUE;
			display_1 = "Ready";
        }
		
        if(timer % 100 == 0) {
            getIPAddr();
        }
		
		if(timer > 0){
			temp_timer = timer;
			IntToIntArray(temp_timer,timer_array);
			IntArrayToASCIIarray(timer_array,timer_char_array);
			for(i=0;i<6;i++){
				timer_display[i] = timer_char_array[i];
			}
			timer_display[5] = '\0';
			display_2 = timer_display;
		}

        if(Interrupt_Event & RECEIVE) {
            Received[USB_Receive_Count + 1] = '\0';
            Interrupt_Event &= ~RECEIVE;
        }

        if(reconnect_timer > 100) {
            resetModule();
            reconnect_timer = 0;
        }

        for(i=0; i<3; i++) { //this interprets messages coming from the PC
            if(command_ready && command[i] == '.') {
                switch(command[i+1]) {
                case 'A':
                    setUpIOTModule();
                    for(j=0; j<3; j++) {
                        command[j] = '\0';
                    }
                    break;
                case 'B':
                    fixBaudRate();
                    for(j=0; j<3; j++) {
                        command[j] = '\0';
                    }
                    break;
                case 'Q':
                    displayStatus();
                    for(j=0; j<3; j++) {
                        command[j] = '\0';
                    }
                    break;
                case 'R':
                    resetModule();
                    for(j=0; j<3; j++) {
                        command[j] = '\0';
                    }
                    break;
                }
            }
        }

        for(i=0; i<3; i++) { //this interprets messages coming from the IOT
            if(IOT_command_ready && IOT_command[i] == '.') {
                switch(IOT_command[i+1]) {
                case 'F':
                    //display_2 = "FORWARD";
                    BLBL_Count = 0;
                    DETECT = 0;
                    IOTForward();
                    for(j=0; j<3; j++) {
                        IOT_command[j] = '\0';
                    }
                    break;
                case 'B':
                    //display_2 = "REVERSE";
                    BLBL_Count = 0;
                    DETECT = 0;
                    Reverse();
                    for(j=0; j<3; j++) {
                        IOT_command[j] = '\0';
                    }
                    break;
                case 'L':
                    //display_2 = "LEFT";
                    BLBL_Count = 0;
                    DETECT = 0;
                    Left45();
                    for(j=0; j<3; j++) {
                        IOT_command[j] = '\0';
                    }
                    break;
                case 'R':
                    //display_2 = "RIGHT";
                    BLBL_Count = 0;
                    DETECT = 0;
                    Right90();
                    for(j=0; j<3; j++) {
                        IOT_command[j] = '\0';
                    }
                    break;
                case 'I':
                    getIPAddr();
                    for(j=0; j<3; j++) {
                        IOT_command[j] = '\0';
                    }
                    break;
                case 'M':
                    followBlackLine();
                    BLBL_Count = INIT_TO_ZERO;
                    TB1CCR1 = R_SPEED;
                    TB1CCR2 = L_SPEED;
                    for(j=0; j<3; j++) {
                        IOT_command[j] = '\0';
                    }
                    break;
                case 'Z':
                    BLBL_Count = 0;
                    DETECT = 0;
                    LongForward();
                    for(j=0; j<3; j++) {
                        IOT_command[j] = '\0';
                    }
                    break;
                }
            }

            switch(check_IOT_Status) { //looks at different states of the IOT module
            case 41:
                resetModule();
                check_IOT_Status = INIT_TO_ZERO;
                break;
            case 24:
                getIPAddr();
                check_IOT_Status = INIT_TO_ZERO;
                break;
            }


            if(ready_to_TX) { //waits for receive to transmit
                //display_2 = Received;
            }

            if(BLBL_Count == TRUE) { //This hits the black line the first time and starts state machine
                Pause();
                DETECT = TRUE;
                CURR_STATE = INIT_TO_ZERO;
            }

            if(DETECT == TRUE) { //This is the State Machine
                switch(CURR_STATE) {
                case STATE_ZERO: //Black Black
                    Forward();
                    PREV_STATE = STATE_ZERO;
                    break;
                case STATE_ONE: //Black White
                    Turn_Left();
                    PREV_STATE = STATE_ONE;
                    break;
                case STATE_TWO: //White Black
                    Turn_Right();
                    PREV_STATE = STATE_TWO;
                    break;
                case STATE_THREE: //White Black
                    Turn_More_Left();
                    //PREV_STATE == 0x02;
                    break;
                case STATE_FOUR: //White Black
                    Turn_More_Right();
                    //PREV_STATE == 0x02;
                    break;
                }
            }

            if(Interrupt_Event & SWITCH_1) { //Case for SW1
                Switch_1_pressed();
                Interrupt_Event &= ~SWITCH_1;
                P4IE |= SW1;
            }

            if(Interrupt_Event & SWITCH_2) { //Case for SW2
                Switch_2_pressed();
                Interrupt_Event &= ~SWITCH_2;
                P4IE |= SW2;
            }

            if(Interrupt_Event & DISPLAY_UPDATE) {
                Display_Process();
                Interrupt_Event &= ~DISPLAY_UPDATE;
            }

            if(Interrupt_Event & TIMER_CASE) { //Case for Timers
                Interrupt_Event &= ~TIMER_CASE;
            }

            if(Interrupt_Event & ADC_CASE) { //Case for ADC
                ADC_Left_Count++;
                if(ADC_Left_Count < SIZE_16) {
                    temp_HEX_left += ADC_Left_Detector;
                    temp_HEX_right += ADC_Right_Detector;
                }

                if(ADC_Left_Count == SIZE_16) {
                    temp_HEX_left += ADC_Left_Detector; //Left
                    temp_HEX_left = temp_HEX_left >> SIZE_4;

                    temp_HEX_right += ADC_Right_Detector; //Right
                    temp_HEX_right = temp_HEX_right >> SIZE_4;;
                    ADC_Left_Count = INIT_TO_ZERO;

                    if(temp_HEX_left > SIZE_400 && temp_HEX_right > SIZE_400) { //Black Black
                        BLBL_Count++;
                        CURR_STATE = STATE_ZERO;
                        // display_4 = "Straight";
                        // posL4 = SIZE_1;
                    }

                    if(temp_HEX_left < SIZE_400 && temp_HEX_right > SIZE_400) { // White Black
                        CURR_STATE = STATE_TWO;
                        //display_4 = "Turning";
                        //posL4 = SIZE_1;
                    }

                    if(temp_HEX_left > SIZE_400 && temp_HEX_right < SIZE_400) { //Black White
                        CURR_STATE = STATE_ONE;
                        // display_4 = "Turning";
                        //posL4 = SIZE_1;
                    }

                    if(temp_HEX_left < SIZE_400 && temp_HEX_right < SIZE_400 && PREV_STATE == STATE_ONE) {
                        CURR_STATE = STATE_THREE;
                        //display_4 = "Turning";
                        //posL4 = SIZE_1;
                    }

                    if(temp_HEX_left < SIZE_400 && temp_HEX_right < SIZE_400 && PREV_STATE == STATE_TWO) {
                        CURR_STATE = STATE_FOUR;
                        //display_4 = "Turning";
                        //posL4 = SIZE_1;
                    }
                    Direction();
                }
                Interrupt_Event &= ~ADC_CASE;
            }

        }
    }
}


void followBlackLine(void) {
    P3OUT |= IR_LED; //turns on the LED
    //display_1 = "FORWARD";					//Starts the LCD saying these messages
    //posL1 = SIZE_1;
    //Display_Process();
    PWM_Count = INIT_TO_ZERO;
    TB1CCTL1 |= CCIE;
    TB1CCTL2 |= CCIE;
    ADC10CTL0 |= ADC10ENC;
    ADC10CTL0 |= ADC10SC; // Sampling and conversion start
}

//===========================================================================
// Function name: setUpIOTModule
// Description: Connects the IOT to the internet
//===========================================================================
void setUpIOTModule(void) { //.A
    size = strlen(getACK);
    out_character(getACK, size);
    wait(8);
    size = strlen(setSSID);
    out_character(setSSID,size);
    wait(8);
    size = strlen(setNAME);
    out_character(setNAME,size);
    wait(8);
    size = strlen(setPrivacy);
    out_character(setPrivacy,size);
    wait(8);
    size = strlen(setNETWORK);
    out_character(setNETWORK,size);
    wait(8);
    size = strlen(saveMEM);
    out_character(saveMEM,size);
    wait(8);
    size = strlen(resetIOT);
    out_character(resetIOT,size);
    PJOUT &= ~IOT_RESET;
    wait(8);
    PJOUT |= IOT_RESET;
    size = strlen(getACK);
    out_character(getACK, size);
}

//===========================================================================
// Function name: displayStatus
// Description: displays the certain variables of the IOT module
//===========================================================================
void displayStatus(void) { //.Q
    size = strlen(checkStatus);
    out_character(checkStatus, size);
    wait(8);
    size = strlen(getMAC);
    out_character(getMAC,size);
    wait(4);
    size = strlen(getSSID);
    out_character(getSSID,size);
    wait(4);
    size = strlen(getNAME);
    out_character(getNAME,size);
    wait(4);
    size = strlen(getPrivacy);
    out_character(getPrivacy,size);
    wait(4);
    size = strlen(getNETWORK);
    out_character(getNETWORK,size);
}

//===========================================================================
// Function name: fixBaudRate
// Description: fixes the baud rate
//===========================================================================
void fixBaudRate(void) { //.B
    size = strlen(setBAUD);
    out_character(setBAUD,size);
    wait(8);
    size = strlen(saveMEM);
    out_character(saveMEM,size);
    wait(8);
    size = strlen(resetIOT);
    out_character(resetIOT,size);
    PJOUT &= ~IOT_RESET;
    wait(8);
    PJOUT |= IOT_RESET;
    size = strlen(getACK);
    out_character(getACK, size);
}

void getIPAddr(void) { //.I
    size = strlen(getIP);
    out_character(getIP,size);
}
//===========================================================================
// Function name: resetModule
// Description: Resets the modules through the PC
//===========================================================================
void resetModule(void) {
    size = strlen(resetIOT);
    out_character(resetIOT,size);
    PJOUT &= ~IOT_RESET;
    PJOUT |= IOT_RESET;
    getIPAddr();
}

//===========================================================================
// Function name: out_character
// Description: outputs the string to IOT module
//===========================================================================
void out_character(char * send,int size) {
    int i=INIT_TO_ZERO;
    while(i < size) {
        if(UCA1IFG & UCTXIFG) {
            UCA1TXBUF = send[i];
            i++;
        }
    }
}

//===========================================================================
// Function name: IntArrayToInt
// Description: Switches between the different switch presses
//===========================================================================
void IntToIntArray(int integer, int intArray[]){
  int i=INIT_TO_ZERO;
  for(i=SIZE_5; i>INIT_TO_ZERO; i--){
    intArray[i] = integer % SIZE_10;
    integer = integer - intArray[i];
    integer = integer / SIZE_10;
  }
}
//===========================================================================
// Function name: Switch_2_pressed
// Description: Switches between the different switch presses
//===========================================================================
void IntArrayToASCIIarray(int intArray[], char ASCIIarray[]){
  int i=INIT_TO_ZERO;
  for(i=INIT_TO_ZERO; i<SIZE_5; i++){
    if((INIT_TO_ZERO <= intArray[i]) && (intArray[i] <= SIZE_9)){
      ASCIIarray[i] = intArray[i] + SIZE_48;
    }
  }
}



//===========================================================================
// Function name: wait
// Description: waits a certain amount of intervals
//===========================================================================
void wait(int time) { //function for waiting s certain amount of time
    wait_count = 0;
    while(wait_count < time) {

    }
}
//===========================================================================
// Function name: Switch_1_pressed
// Description: Switches between the different switch presses
//===========================================================================
void Switch_1_pressed(void) {

}

//===========================================================================
// Function name: Switch_2_pressed
// Description: Switches between the different switch presses
//===========================================================================
void Switch_2_pressed(void) {

}

//------------------------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//------------------------------------------------------------------------------

void HEXtoBCD(int hex_value) {
    int value;
    adc_char[INIT_TO_ZERO] = '0';
    if (hex_value > SIZE_1000) {
        hex_value = hex_value - SIZE_1000;
        adc_char[INIT_TO_ZERO] = '1';
    }

    value = INIT_TO_ZERO;
    adc_char[SIZE_1] = ASCIIOFFSET + value;
    while (hex_value > SIZE_99) {
        hex_value = hex_value - SIZE_100;
        value = value + SIZE_1;
        adc_char[ADD_ONE_TO_TIME] = ASCIIOFFSET + value;
    }

    value = INIT_TO_ZERO;
    adc_char[SIZE_2] = ASCIIOFFSET + value;
    while (hex_value > SIZE_9) {
        hex_value = hex_value - SIZE_10;
        value = value + SIZE_1;
        adc_char[SIZE_2] = ASCIIOFFSET + value;
    }

    adc_char[SIZE_3] = ASCIIOFFSET + hex_value;
}

//===========================================================================
// Function name: Direction
// Description: Prints direction of car to screen
//===========================================================================
void Direction(void) {
    if(temp_HEX_right > temp_HEX_left) {
        //display_4 = "LEFT";
        posL4 = SIZE_1;
    }
    if(temp_HEX_left > temp_HEX_right) {
        //display_4 = "RIGHT";
        posL4 = SIZE_1;
    }
    if(temp_HEX_left == temp_HEX_right) {
        //display_4 = "FORWARD";
        posL4 = SIZE_1;
    }
}

//===========================================================================
// Function name: Display_Process
// Description: Tells the LCD what to display
//===========================================================================
void Display_Process(void) {
    ClrDisplay();
    lcd_out(display_1, LCD_HOME_L1, posL1);
    lcd_out(display_2, LCD_HOME_L2, posL2);
    lcd_out(display_3, LCD_HOME_L3, posL3);
    lcd_out(display_4, LCD_HOME_L4, posL4);
}

//------------------------------------------------------------------------------
// System Configurations
void enable_interrupts(void) {
    __bis_SR_register(GIE);     // enable interrupts
}
