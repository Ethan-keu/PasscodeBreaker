/*
 * File:   keu00001_lab2b_main_v001.c
 * Author: Ethan Keu 
 *
 * Created on February 7, 2023, 1:22 PM
 */
#include "xc.h"
#include "stdint.h"
#include "keu00001_lab2b_asmLib_v002.h"

#define PERIOD 5



    //The writeColor function takes three 8-bit RGB values. It first converts them to binary, from which the 
    //individual bits are stored within an array of size 8. From the array, the function checks for each individual
    //bit that corresponds to a write_0 or write_1. 
void writeColor1(int r, int g, int b){

    if(r >= 0 || r <= 255) {
        if (r == 0) {
            int w;
            for(w = 0; w <= 7; w++){
                write_0_1();
            }
        }
        
        else if(r > 0) { 
            int i;
            int z[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; r > 0; i--) {
                z[i] = r % 2;
                r = r / 2;
            }
            
            
            int o;
            for (o = 0; o <= 7; o++) {
                if (z[o] == 1) {
                    write_1_1();
                } else if(z[o] == 0) {
                    write_0_1();
                }
            }
        }
       
    }
        
    if (g >= 0 && g <= 255) {
        if(g == 0){
            int kk;
            for(kk = 0; kk <= 7; kk++){
                write_0_1();
            }
        }
        else if(g > 0){
            int k;
            int t[8] = {0,0,0,0,0,0,0,0};
            for (k = 7; g > 0; k--) {
                t[k] = g % 2;
                g = g / 2;
            }

            int j;
            for (j = 0; j <= 7; j++) {
                if (t[j] == 1) {
                    write_1_1();
                } else if(t[j] == 0) {
                    write_0_1();
                }
            }
        }
        
    
    }
    
    if (b >= 0 && b <= 255) {
        if(b == 0){
            int jj;
            for(jj = 0; jj <= 7; jj++){
                write_0_1();
            }
        }
        
        else if(b > 0){
            int i;
            int p[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; b > 0; i--) {
                p[i] = b % 2;
                b = b / 2;
            }
            int u;
            for (u = 0; u <= 7; u++) {
                if (p[u] == 1) {
                    write_1_1();
                } else if (p[u] == 0) {
                    write_0_1();
                }
            }
        }
        
    
    }
}

void writeColor2(int r, int g, int b){

    if(r >= 0 || r <= 255) {
        if (r == 0) {
            int w;
            for(w = 0; w <= 7; w++){
                write_0_2();
            }
        }
        
        else if(r > 0) { 
            int i;
            int z[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; r > 0; i--) {
                z[i] = r % 2;
                r = r / 2;
            }
            
            
            int o;
            for (o = 0; o <= 7; o++) {
                if (z[o] == 1) {
                    write_1_2();
                } else if(z[o] == 0) {
                    write_0_2();
                }
            }
        }
       
    }
        
    if (g >= 0 && g <= 255) {
        if(g == 0){
            int kk;
            for(kk = 0; kk <= 7; kk++){
                write_0_2();
            }
        }
        else if(g > 0){
            int k;
            int t[8] = {0,0,0,0,0,0,0,0};
            for (k = 7; g > 0; k--) {
                t[k] = g % 2;
                g = g / 2;
            }

            int j;
            for (j = 0; j <= 7; j++) {
                if (t[j] == 1) {
                    write_1_2();
                } else if(t[j] == 0) {
                    write_0_2();
                }
            }
        }
        
    
    }
    
    if (b >= 0 && b <= 255) {
        if(b == 0){
            int jj;
            for(jj = 0; jj <= 7; jj++){
                write_0_2();
            }
        }
        
        else if(b > 0){
            int i;
            int p[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; b > 0; i--) {
                p[i] = b % 2;
                b = b / 2;
            }
            int u;
            for (u = 0; u <= 7; u++) {
                if (p[u] == 1) {
                    write_1_2();
                } else if (p[u] == 0) {
                    write_0_2();
                }
            }
        }
        
    
    }
}

void writeColor3(int r, int g, int b){

    if(r >= 0 || r <= 255) {
        if (r == 0) {
            int w;
            for(w = 0; w <= 7; w++){
                write_0_3();
            }
        }
        
        else if(r > 0) { 
            int i;
            int z[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; r > 0; i--) {
                z[i] = r % 2;
                r = r / 2;
            }
            
            
            int o;
            for (o = 0; o <= 7; o++) {
                if (z[o] == 1) {
                    write_1_3();
                } else if(z[o] == 0) {
                    write_0_3();
                }
            }
        }
       
    }
        
    if (g >= 0 && g <= 255) {
        if(g == 0){
            int kk;
            for(kk = 0; kk <= 7; kk++){
                write_0_3();
            }
        }
        else if(g > 0){
            int k;
            int t[8] = {0,0,0,0,0,0,0,0};
            for (k = 7; g > 0; k--) {
                t[k] = g % 2;
                g = g / 2;
            }

            int j;
            for (j = 0; j <= 7; j++) {
                if (t[j] == 1) {
                    write_1_3();
                } else if(t[j] == 0) {
                    write_0_3();
                }
            }
        }
        
    
    }
    
    if (b >= 0 && b <= 255) {
        if(b == 0){
            int jj;
            for(jj = 0; jj <= 7; jj++){
                write_0_3();
            }
        }
        
        else if(b > 0){
            int i;
            int p[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; b > 0; i--) {
                p[i] = b % 2;
                b = b / 2;
            }
            int u;
            for (u = 0; u <= 7; u++) {
                if (p[u] == 1) {
                    write_1_3();
                } else if (p[u] == 0) {
                    write_0_3();
                }
            }
        }
        
    
    }
}

void writeColor4(int r, int g, int b){

    if(r >= 0 || r <= 255) {
        if (r == 0) {
            int w;
            for(w = 0; w <= 7; w++){
                write_0_4();
            }
        }
        
        else if(r > 0) { 
            int i;
            int z[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; r > 0; i--) {
                z[i] = r % 2;
                r = r / 2;
            }
            
            
            int o;
            for (o = 0; o <= 7; o++) {
                if (z[o] == 1) {
                    write_1_4();
                } else if(z[o] == 0) {
                    write_0_4();
                }
            }
        }
       
    }
        
    if (g >= 0 && g <= 255) {
        if(g == 0){
            int kk;
            for(kk = 0; kk <= 7; kk++){
                write_0_4();
            }
        }
        else if(g > 0){
            int k;
            int t[8] = {0,0,0,0,0,0,0,0};
            for (k = 7; g > 0; k--) {
                t[k] = g % 2;
                g = g / 2;
            }

            int j;
            for (j = 0; j <= 7; j++) {
                if (t[j] == 1) {
                    write_1_4();
                } else if(t[j] == 0) {
                    write_0_4();
                }
            }
        }
        
    
    }
    
    if (b >= 0 && b <= 255) {
        if(b == 0){
            int jj;
            for(jj = 0; jj <= 7; jj++){
                write_0_4();
            }
        }
        
        else if(b > 0){
            int i;
            int p[8] = {0,0,0,0,0,0,0,0};
            for (i = 7; b > 0; i--) {
                p[i] = b % 2;
                b = b / 2;
            }
            int u;
            for (u = 0; u <= 7; u++) {
                if (p[u] == 1) {
                    write_1_4();
                } else if (p[u] == 0) {
                    write_0_4();
                }
            }
        }
        
    
    }
}
    
//The delay function delays the program for about N ms. Where N is defined above
// as a constant PERIOD and can be changed to make the color changes visible. 
//void delay(int delay_in_ms){
//    int x;
//    for(x = 0; x < delay_in_ms; x++){
//        keu_wait_1ms(); 
//    }
//}





