/* 
 * File:   keu00001_Lab5_lcdLib_v001.c
 * Author: Ethan Keu
 *
 * Created on March 22, 2023, 9:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "xc.h"
#include "string.h"
#include "keu00001_Lab5_header_v002.h"

const char CONTRAST = 0x1; //Contrast Control --> 0x0 - 0xF

void delay_ms(long int ms){
    while(ms --> 0){
        asm("repeat #15998");
        asm("nop");
    }
}


void lcd_cmd(char Package) {
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN);
    IFS1bits.MI2C1IF = 0;
    I2C1TRN = 0b01111100; //Slave address and write bit

    while (_MI2C1IF ==0);
    _MI2C1IF = 0;
    I2C1TRN = 0b00000000; //Control byte; RS bit is not set

    while (_MI2C1IF ==0);
    _MI2C1IF = 0;
    I2C1TRN = Package;

    while (_MI2C1IF ==0);
    _MI2C1IF = 0;
    I2C1CONbits.PEN = 1;

    while (I2C1CONbits.PEN);
}

void lcd_init(void){
    delay_ms(50); //After VDD Stable
    lcd_cmd(0b00111000); //Function set --> normal instruction mode
    lcd_cmd(0b00111001); //Function set --> extended instruction mode
    lcd_cmd(0b00010100); //OSC frequency  
//    lcd_cmd(0b01110000); //Temp Contrast
    lcd_cmd((0b0111 << 4) + CONTRAST); //Contrast c3 - c0 
    lcd_cmd(0b01011110); //Power/ICON/Contrast Control --> Ion, Bon, c5 - c4 
    lcd_cmd(0b01101100); //Follower Control 
    delay_ms(200); //Delay for power stable 

    lcd_cmd(0b00111000); //Function set --> normal instruction mode
    lcd_cmd(0b00001100); //Display on/off --> currently set to on
    lcd_cmd(0b00000001); //Clear display 
    delay_ms(2);
    
}

void lcd_setCursor(char x, char y) {
    lcd_cmd(0b10000000 | (0x40 * y + x)); 
    
    }

void lcd_printChar(char myChar){
    I2C1CONbits.SEN = 1;
    
    while(I2C1CONbits.SEN);
    _MI2C1IF = 0;
    I2C1TRN = 0b01111100;

    while(!_MI2C1IF);
    _MI2C1IF = 0;
    I2C1TRN = 0b01000000;// Control byte, R/W = 1

    while(!_MI2C1IF);
    _MI2C1IF = 0;
    I2C1TRN = myChar; 

    while(!_MI2C1IF);
    _MI2C1IF = 0;
    I2C1CONbits.PEN = 0;

    while (!I2C1CONbits.PEN);
    
}

void lcd_printStr(const char s[]){
    int size = strlen(s); 
    I2C1CONbits.SEN = 1; 
    while(I2C1CONbits.SEN);
    _MI2C1IF = 0;
    I2C1TRN = 0b01111100; 
    while(!_MI2C1IF);
    _MI2C1IF = 0;
    
    int x; 
    for(x = 0; x < size - 1; x++){
        I2C1TRN = 0b11000000; //Set RS = 1, and R/W = 1; 
        while(!_MI2C1IF); 
        _MI2C1IF = 0;
        I2C1TRN = s[x]; //Storing the data byte. 
        while(!_MI2C1IF);
        _MI2C1IF = 0; 
    }
    
    I2C1TRN = 0b01000000; //Set the control byte, set RS = 1. 
    while(!_MI2C1IF);
    _MI2C1IF = 0; 
    I2C1TRN = s[size - 1]; //Storing the data byte 
    while(!_MI2C1IF);
    _MI2C1IF = 0;
    I2C1CONbits.PEN = 1; //Stop sending data 
    while(I2C1CONbits.PEN); 
    
    
    
}
