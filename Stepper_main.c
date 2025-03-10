
#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include "Stepper_main.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
//#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
//#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
//#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
//#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
//#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)
//
//
//// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
//#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
//#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
//#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
//#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
//                                       // Fail-Safe Clock Monitor is enabled)
//#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void stepper_setup(){
    _RCDIV = 0;
    AD1PCFG = 0x9fff;//All pins digital
    TRISBbits.TRISB4 = 0;//!Sleep pin
    TRISBbits.TRISB5 = 0;//Direction pin
    TRISBbits.TRISB6 = 0;//Motor 1 step pin
    TRISBbits.TRISB7 = 0;//Motor 2 step pin
    
    T1CON = 0;//Set up timer 1 for 1 second
    TMR1 = 0;
    T1CONbits.TCKPS = 0b11;//1:256 pre-scalar
    PR1 = 62499;
    T1CONbits.TON = 1; //Turn on T1

    T2CON = 0;//Set up timer 2 for 1 second
    TMR2 = 0;
    T2CONbits.TCKPS = 0b11;//1:256 pre-scalar
    PR2 = 62499;//Do not turn on T2 yet
}

void drive_motor1(){//Box motor actuation
    LATBbits.LATB4 = 1;//Set !Sleep high
    LATBbits.LATB5 = 1;//Set direction
    while(1){
        if(TMR1 >= PR1){//If timer hits max value, stop stepping
            _RB7 = 0;
            break;
        }
        _RB7 = !_RB7;//Else, toggle between 0 and 1 to step motor
        delay(3);
    }
    LATBbits.LATB4 = 0;//Set !Sleep low
    delay(1000);
}

void drive_motor2(){//Gun motor actuation
    T1CONbits.TON = 1; //Turn on T2
    LATBbits.LATB4 = 1;//Set !Sleep high
    LATBbits.LATB5 = 1;//Set direction
    while(1){
        if(TMR1 >= (PR1)){//If timer hits max value, stop stepping
            _RB6 = 0;
            break;
        }
        _RB6 = !_RB6;//Else, toggle RB6 to step motor
        delay(3);
    }
    LATBbits.LATB4 = 0;//Set !Sleep low
    delay(1000);
}

void reset_motor1(){//Reset box motor to close lid
    T2CONbits.TON = 1;//Turn on T2
    LATBbits.LATB4 = 1;//Set !Sleep high
    LATBbits.LATB5 = 0;//Set direction
    while(1){
        if(TMR2 >= PR2){//If timer hits max value, stop stepping
            _RB7 = 0;
            break;
        }
        _RB7 = !_RB7;//Else, toggle RB7 to step
        delay(3);
    }
    LATBbits.LATB4 = 0;//Set !Sleep low
    delay(1000);
}

void reset_motor2(){//Reset gun motor for consecutive firings
    T2CONbits.TON = 1;//Turn on T2
    LATBbits.LATB4 = 1;//Set !Sleep high
    LATBbits.LATB5 = 0;//Set direction
    while(1){
        if(TMR2 >= (PR2)){//If timer hits max value, stop stepping
            _RB6 = 0;
            break;
        }
        _RB6 = !_RB6;//Else, toggle RB6 to step
        delay(3);
    }
    LATBbits.LATB4 = 0;//Set !Sleep low
    delay(1000);
}

void delay(unsigned int ms){//n ms delay function
    while(ms-- > 0){
        asm("repeat #15998");
        asm("nop");
    }
}

void sleep(){//Function to turn the motors off
    LATBbits.LATB4 = 0;
}