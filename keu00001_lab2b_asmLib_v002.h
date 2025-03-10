/* 
 * File:   keu00001_lab2b_asmLib_v002.h
 * Author: lego2
 *
 * Created on February 7, 2023, 3:07 PM
 */

#ifndef KEU00001_LAB2B_ASMLIB_V002_H
#define	KEU00001_LAB2B_ASMLIB_V002_H

#ifdef	__cplusplus
extern "C" {
#endif

    void keu_wait_100us(void);
    void keu_wait_1ms(void);
    void write_0_1(void);
    void write_1_1(void);
    void write_0_2(void);
    void write_1_2(void);
    void write_0_3(void);
    void write_1_3(void);
    void write_0_4(void);
    void write_1_4(void);
    void writeColor1(int,int,int);
    void writeColor2(int, int, int);
    void writeColor3(int, int, int);
    void writeColor4(int, int, int); 

//    void colorCycle(int,int,int); 
//    void delay(int); 
//    uint32_t packColor(unsigned char , unsigned char , unsigned char ); 
//    unsigned char getR(uint32_t);
//    unsigned char getG(uint32_t);
//    unsigned char getB(uint32_t);
//    void writePacCol(uint32_t);
//    uint32_t Wheel(unsigned char); 
    
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* KEU00001_LAB2B_ASMLIB_V002_H */

