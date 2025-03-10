/* 
 * File:   keu00001_Lab5_header_v001.h
 * Author: Ethan Keu
 *
 * Created on March 21, 2023, 6:20 PM
 */

#ifndef KEU00001_LAB5_HEADER_V001_H
#define	KEU00001_LAB5_HEADER_V001_H
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "xc.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    void delay_ms(long int);
    void lcd_cmd(char);
    void lcd_init(void);
    void lcd_lcdsetCursor(char,char);
    void lcd_printChar(char);
    void lcd_printStr(const char s[]);

#ifdef	__cplusplus
}
#endif

#endif	/* KEU00001_LAB5_HEADER_V001_H */

