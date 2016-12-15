#include <msp430.h>
#include "types.h"
#include "ports.h"
#include "uscia0_spi.h"
#include "pcd8544.h"
/*
 * pcd8544.c
 *
 *  Created on: 2016. dec. 14.
 *      Author: lmajer
 */

// Instrucions


#define NOP             (0x00)      // No operation
#define FUNC            BIT5        // Power Down control Entry mode, Istruction mode control
#define DISP            BIT3        // Set Display Configuration
#define SET_Y           BIT6        // Sets Y address ok RAM 0<=Y<=5
#define SET_X           BIT7        // Sets X address ok RAM 0<=X<=83


// Funtion Parameters
#define PD              BIT2        // PD = 1 Power Down, PD = 0 chip active
#define V_H             BIT1        // V = 1 Vertical Addressing, V = 0 Horizontal Addressing
#define H               BIT0        // H = 1 Extend Instruction Set, H = 0 Basic Instruction Set

// Extended Instruction Set

#define VOP             BIT7        // Vop, Contrast set 0-127
#define TC              BIT2        // Temperature coefficient 0-3
#define BS              BIT4        // Set Bias System 0-7

// Display Control Parameters
#define D               BIT2        // D = 0 E = 0 Display Blank, D = 1 E = 0 Normal Mode
#define E               BIT0        // D = 0 E = 1 All Display Segments On, D = 1 E = 1 Inverse Video Mode

void send_lcd(unsigned char command,unsigned char data)
{
    PCD_CE = 0;             // Chip enable
    PCD_DC = command;       // Set command
    transferSpi(data);      // Transfer data
    PCD_CE = 1;             // Chip Disable
}

void init_lcd(void)
{
    // Reset LCD
    PCD_RESET = 0;
    __delay_cycles(1000);           // set the optimal min time for lcd
    PCD_RESET = 1;

    send_lcd(CMD,FUNC + H);             // Extended instruction set, horizontal addressing
    send_lcd(CMD,VOP + 27);             // Set Contrast: 27
    send_lcd(CMD,TC + 0);               // Set Temperature Coefficient: 0
    send_lcd(CMD,BS + 7);               // Set Bias System: 7
    send_lcd(CMD,FUNC);                 // Set Basic Instruction set, horizontal addressing
    send_lcd(CMD,DISP + D);             // Display Normal mode
}

void lcd_set_cursor(unsigned char x, unsigned char y)
{
    send_lcd(CMD,SET_X + x);                // Set X address of RAM
    send_lcd(CMD,SET_Y + y);                // Set Y address of RAM
}

void lcd_clear_diplay()
{
    lcd_set_cursor(0, 0);                   // Set cursor to RAM 0
    int c = 0;
    while(c < 504)
    {
        send_lcd(DAT,0);
        c++;
    }
    lcd_set_cursor(0, 0);
}

void lcd_set_char(unsigned char c)
{
    unsigned char i;
    for(i=0; i<5;i++)
    {
        send_lcd(DAT,font[c - 0x20][i]);        // Font write
    }
    send_lcd(DAT,0);                            // Font Spacing
}


void lcd_string(const char *string)
{
    while(*string)
    {
        lcd_set_char(*string++);
    }
}
