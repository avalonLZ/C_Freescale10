#ifndef	_LCD_H_
#define _LCD_H_




#define RESET  PTA16_OUT
#define DC     PTA15_OUT
#define D1     PTA17_OUT
#define D0     PTA19_OUT


#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xCF 



#define X_WIDTH 128
#define Y_WIDTH 64


 typedef unsigned char byte;
 typedef unsigned int word;
 extern byte beyond96x64[512];
 void LCD_WrDat(u8 data);
 void LCD_Set_Pos(byte x, byte y);
 void LCD_Init(void);
 void LCD_CLS(void);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);
 void LCD_P8x16Str(u8 x,u8 y,u8 ch[]);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);
 void LCD_PutPixel(byte x,byte y);
 void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void LCD_Fill(byte dat);
 void LCD_Char(byte x,byte y,byte ch);
#endif