/*
 * File:		nokia.h
 * Purpose:		Serial Input/Output routines
 *
 */

#ifndef _NOKIA_H
#define _NOKIA_H

#include "gpio.h"
/********************************************************************/
/*-----------------------------------------------------------------------
LCD_init          : 5110LCD初始化

编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/
#define LCD_RST   PTA13_OUT 
#define LCD_CE    PTA14_OUT
#define SDIN      PTA15_OUT
#define SCLK      PTA19_OUT
#define LCD_DC    PTA16_OUT
#define LCD_LED    PTA17_OUT


void delay_1us(void)  ;
void delay_1ns(void)  ;
void LCD_clear(void);
void LCD_write_byte(u8 dat, u8 command);
void LCD_init(void) ;
void LCD_write_char(u8 c) ;
void LCD_set_XY(u8 X, u8 Y);



    

/********************************************************************/

#endif
