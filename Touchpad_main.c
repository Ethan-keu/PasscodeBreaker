/* 
 * File:   Touchpad_main.c
 * Author: Ethan Keu
 * Source code borrowed from: https://electronics.stackexchange.com/questions/411897/write-collision-for-multiple-reads-pic24-i2c
 * Created on April 7, 2023, 2:44 PM
 */
//#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
//#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
//#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
//#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
//#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)
//// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
//#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
//#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
//#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
//#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
//// Fail-Safe Clock Monitor is enabled)
//#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#include <stdio.h>
#include <stdlib.h>
#include "xc.h" 
#include "keu00001_Lab5_lcdLib_v002.c"


void chipWrite(unsigned char reg, unsigned char data){
    //Start bit
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;

    //Slave address bit
    I2C2TRN = 0b01010000;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

    //Register address
    I2C2TRN = reg; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

    //Data
    I2C2TRN = data;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

    //Stop bit
    I2C2CONbits.PEN = 1;
    IFS3bits.MI2C2IF = 0;
    while(I2C2CONbits.PEN);
}


unsigned char chipRead(unsigned char reg){   
    unsigned char msb = 0;
    
    /*start*/   
    I2C2CONbits.SEN = 1;   
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;

    /*sensor address*/  
    I2C2TRN = 0b01010000; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

     /*Register for reading*/
    I2C2TRN = reg;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

     /*repeated start*/   
    I2C2CONbits.RSEN = 1;   
    while(I2C2CONbits.RSEN);
    _MI2C2IF = 0;

    /*Slave address with read = 1*/
    I2C2TRN = 0b01010001;       
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

     /*receiver enabled*/   
    I2C2CONbits.RCEN = 1;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;

    /*read first byte data*/   
    while(!I2C2STATbits.RBF);   
    while(I2C2CONbits.RCEN); 
    msb = I2C2RCV;
    _MI2C2IF = 0;

    /*send nack*/   
    I2C2CONbits.ACKEN = 1;
    while(I2C2CONbits.ACKEN);
    _MI2C2IF = 0;

    /*send stop*/   
    I2C2CONbits.PEN = 1;   
    while(I2C2CONbits.PEN);    

return msb; 
}

    void configTouchpad(void){
     //Enable multi-touch; Select number of simultaneous touches
     // Byte 7 corresponds to enable/disable multi-touch
     //Byte 2 and 3 correspond to number of simultaneous touches
    chipWrite(0x2A, 0b10000000); 
    
    //LED Selection 
    //Sets whether LED 1-8 are pulled high. 
    chipWrite(0x72, 0x9F);

    //Sensitivity of touchpads. 
    //<3:0> correspond to Resolution of data (not really needed for this application)
    //<6:4> correspond to Sensitivity factor. --> Check pg 45, 46 in data sheet for more info. 
    chipWrite(0x1F, 0b1100000); 
    
    //Sensor input Configuration 
    //Controls timings associated with each capacitive touchpad. 
    //See pg 49 in datasheet for more details. 
    chipWrite(0x22, 0b00010100);
    
    
    //chipWrite(0x02, 0x00); 
//    chipWrite(0x10, 0b1000000);

 }
