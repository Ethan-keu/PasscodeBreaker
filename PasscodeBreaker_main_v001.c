/* 
 * File:   PasscodeBreaker_main_v001.c
 * Author: Ethan Keu, Jason Chu 
 * 
 * Created on April 20, 2023, 6:57 PM
 * 
 * This File contains all the logic used for the PasscodeBreaker Game.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "Touchpad_main.c"
#include "keu00001_lab2b_main_v002.c"
#include "Stepper_main.c"


#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

/*
 * The second player will input their passcode by changing the values of each digit. They will also
 * assign the amount of guesses that player 1 is alloted.  */
int GUESSES = 3; 

int digit1 = 1; 
int digit2 = 2; 
int digit3 = 3; 
int digit4 = 3; 

void initChip(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9FFF; 
    TRISB = 0x00; 
    PORTB = 0x00; 
    TRISA = 0x00;
    PORTA = 0x00;
    
    I2C2CON = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB2 = 0;
    I2C2CONbits.ACKDT = 1;
    I2C2BRG = 0x25; //Page 153
    I2C2CONbits.I2CEN = 1;
    _MI2C2IF = 0;
    
    I2C1CONbits.I2CEN = 1;
    I2C1BRG = 0x9D; //Set Baud Rate Generator to minimum frequency of 100kHz 
    _MI2C1IF = 0; //Clear interrupt flag 

    lcd_init();//This function can be found in the LCD library. 

}


//Initialize and set the LEDs off 
void colorOFF(void) {
    writeColor1(0, 0, 0);
    writeColor2(0, 0, 0);
    writeColor3(0, 0, 0);                                                                           
    writeColor4(0, 0, 0);
}

int main(void) {
    initChip(); 
    configTouchpad(); 
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

    //Clear screen before the start of a new game.
    lcd_cmd(0b00000001);    
    
    //Set the all the iLEDs to off
    colorOFF();
    char key1 = 0b00000000;
    char key2 = 0b00000000;
    char key3 = 0b00000000;
    char key4 = 0b00000000;
    char submitKey = 0b00000000;
    char adStr1[2], adStr2[2], adStr3[2], adStr4[2], adStrG[1];

    //Keys 1-4 read from inputs 1-4 on the CAP1188. 
    //submitKey reads from input 5 on the CAP1188. 
    while(1){
        //Reading input from touchpads 
        lcd_setCursor(0, 0);

        key1 = chipRead(0x13);
        key2 = chipRead(0x12);
        key3 = chipRead(0x11);
        key4 = chipRead(0x10);
        submitKey = chipRead(0x14);

        //Touch detection
        if(key1 > 0x50){
            delay_ms(500); 
            count1 = (count1 + 1) % 9;
        }
        
        if(key2 > 0x50) {
            delay_ms(500);
            count2 = (count2 + 1) % 9; 
        }

        if (key3 > 0x50) {
            delay_ms(500);
            count3 = (count3 + 1) % 9; 
        }

        if (key4 > 0x50) {
            delay_ms(500);
            count4 = (count4 + 1) % 9; 

        }
        
        //Key submit
        if(submitKey > 0x50){
            
            //Guess is correct
            if(count1 == digit1 && count2 == digit2 && count3 == digit3 && count4 == digit4) {
                lcd_cmd(0b00000001);//Clear Screen
                colorOFF();
                //Guess is correct, enter win phase. 
                
                //Drive the motor to open the lock box
                stepper_setup();
                drive_motor1();
                delay_ms(2000);
                reset_motor1();
                while(count1 == digit1 && count2 == digit2 && count3 == digit3 && count4 == digit4) {
                    lcd_setCursor(0, 0);     
                    lcd_printStr("You");
                    lcd_setCursor(4,0);
                    lcd_printStr("Win!");
                    writeColor4(0, 100, 0);
                    writeColor3(0, 0, 100);
                    writeColor2(0, 100, 0);
                    writeColor1(0, 0, 100);
                    delay_ms(100);
                    writeColor4(0, 0, 100);
                    writeColor3(0, 100, 0);
                    writeColor2(0, 0, 100);
                    writeColor1(0, 100, 0);
                    delay_ms(100);
                    
                }
                
            }
            
            //Guess is incorrect
            if (count1 != digit1 || count2 != digit2 || count3 != digit3 || count4 != digit4) {
                GUESSES = GUESSES - 1;
                delay_ms(500);

            }
            
            //LED guessing color code
            if (count1 == digit1) {
                writeColor4(0, 100, 0);
            }
            else if(count1 < digit1) {
                writeColor4(100, 0, 0);
            }
            else if (count1 > digit1) {
                writeColor4(100, 100, 0);
            }
            if (count2 == digit2) {
                writeColor3(0, 100, 0);
            } else if (count2 < digit2) {
                writeColor3(100, 0, 0);
            } else if (count2 > digit2) {
                writeColor3(100, 100, 0);
            }
            if (count3 == digit3) {
                writeColor2(0, 100, 0);
            } else if (count3 < digit3) {
                writeColor2(100, 0, 0);
            } else if (count3 > digit3) {
                writeColor2(100, 100, 0);
            }
            if (count4 == digit4) {
                writeColor1(0, 100, 0);
            } else if (count4 < digit4) {
                writeColor1(100, 0, 0);
            } else if (count4 > digit4) {
                writeColor1(100, 100, 0);
            }
        } 
        
        //Print to the screen the current count values of each digit. 
        sprintf(adStr1, "%d", count1);
        sprintf(adStr2, "%d", count2);
        sprintf(adStr3, "%d", count3);
        sprintf(adStr4, "%d", count4);
        sprintf(adStrG, "%d", GUESSES);
        lcd_printStr(adStr1);
        lcd_printStr(adStr2);
        lcd_printStr(adStr3);
        lcd_printStr(adStr4);
        lcd_setCursor(0, 1);
        lcd_printStr("Guess:");
        lcd_setCursor(7,1);
        lcd_printStr(adStrG);
        delay_ms(100);
        
        //Endgame Results 
        //Place conditions for when the game is over. 
        if(GUESSES == 0) {
            lcd_cmd(0b00000001); //Clear the screen 
            //Drive motor 2 which is connected to the watergun. 
            stepper_setup();
            drive_motor2(); 
            reset_motor2();

            while(GUESSES == 0){
                char d1[2],d2[2],d3[2],d4[2]; 
                lcd_setCursor(0, 0);
                lcd_printStr("GAMEOVER");
                sprintf(d1, "%d", digit1);
                sprintf(d2, "%d", digit2); 
                sprintf(d3, "%d", digit3); 
                sprintf(d4, "%d", digit4);
                lcd_setCursor(0, 1);
                lcd_printStr(d1);
                lcd_printStr(d2);
                lcd_printStr(d3);
                lcd_printStr(d4);
                delay_ms(10);
                
            }            
        }


    }

}

