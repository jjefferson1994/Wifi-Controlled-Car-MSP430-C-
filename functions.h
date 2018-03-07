// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);
void Display_Process(void);
void five_msec_sleep(unsigned int fivemsec);
void Timer_code(void);
void out_character(char TX[], int size);
void wait(int x);

//IOT 
void setUpIOTModule(void);
void displayStatus(void);
void fixBaudRate(void);
void resetModule(void);
void getIPAddr(void);
void followBlackLine(void);
void LongForward(void);

//Int to Display
void IntToIntArray(int integer, int intArray[]);
void IntArrayToASCIIarray(int intArray[], char ASCIIarray[]);

//Serial
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);

//pwm
void decelerate(void);

//Timer functions
void Delay(unsigned int);
void Wait_Time(void);

//Turns all motors off
void Stop_All_Motors(void);

//Driving
void Forward(void);
void IOTForward(void);
void Turn_Left(void);
void Turn_More_Left(void);
void Turn_Right(void);
void Turn_More_Right(void);
void Pause(void);
void Reverse(void);
void Left45(void);
void Right90(void);

//ADC
void Convert_ADC_Right(void);
void Convert_ADC_Left(void);
void HEXtoBCD(int);
void Direction(void);

//timer interrupt
void Timer_Inter(void);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

//Switch functions
void Switch_1_pressed(void);
void Switch_2_pressed(void);
void Toggle_LCD(void);

// interrupts
void enable_interrupts(void);
__interrupt void Timer2_B0_ISR(void);
__interrupt void TIMER2_B1_ISR(void);
__interrupt void ADC10_ISR(void);

//Timer Stuffs
void Init_Timer_A0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);
void Init_ADC(void);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);

void grab_a_character(void);
int wait_for_character(void);
void menu(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);

//Shape Functions
void Triangle(void);
void Circle(void);
void Figure_Eight(void);
