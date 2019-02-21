/*
 * File:   main.c
 * Author: Raphael Pereira
 */
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "my_delays.h"
#include "hd44780.h"
#include "my_i2c.h"
#include "hih6130.h"

void main(void)
{
    //float temp;
    //float humidity;
    unsigned char aux[20];
    
    OSCCON = 0b01110010;

    ADCON1 = 0b00001111; // Set all pins in digital mode.
    CMCON = 0b00000111; // Disable all comparators.

    TRISA = 0b00000000; // Configure PORTA as output
    TRISB = 0b11111111;
    TRISC = 0b00000000;
    TRISD = 0b00000000; // Configure PORTD as output
    TRISE = 0b00000011;
    
    CMCON = 0b00000111;
    
    Lcd_Init();                // Start LCD
    Lcd_Command(LCD_CLEAR);
    Lcd_Command(LCD_CURSOR_OFF);
    
    I2C_Close(); // Close the  I2C Bus.
    //I2C_Init(49); // I2C 100kHz, 20MHz-CRYSTAL.
    I2C_Init(19); // I2C 100kHz, 8MHz-CRYSTAL.
    //I2C_Init(9); // I2C 100kHz, 4MHz-CRYSTAL.
    
    Lcd_CreateStdChar();
    
    Lcd_Text(1, 1, "H:");
    Lcd_Text(2, 1, "T:");
    
    HIH6130_Init_Norm();
    __delay_ms(50);
    
    while(1)
    {        
        HIH6130_ReadRHT();
        sprintf(aux, "%3.2f", humidity);
        Lcd_Text(1, 3, aux);
        Lcd_CharCP('%');
        
        sprintf(aux, "%3.2f", temperature);
        Lcd_Text(2, 3, aux);
        Lcd_CharCP(178);
        Lcd_CharCP('C');
        
        sprintf(aux, "%d", _status);
        Lcd_Text(1, 10, aux);
    }
}