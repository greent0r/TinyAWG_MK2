#include "lcd.h"

//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	 

/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 data)
{ 
	u8 buff = data;
	LCD_CS_CLR;     
	LCD_RS_CLR;	  
	spi_send_only(&buff, 1);
	LCD_CS_SET;	
	LCD_RS_SET;	
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 data)
{
    u8 buff = data;
    LCD_CS_CLR;
	spi_send_only(&buff, 1);
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}	   

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 


/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void Lcd_WriteData_16Bit(u16 Data)
{	
    u8 buff[2];
    buff[0] = Data>>8;
    buff[1] = Data&0xFF;
    LCD_CS_CLR;
    spi_send_only(buff, 2);
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y, u16 color)
{
	LCD_SetCursor(x,y);//设置光标位置 
	Lcd_WriteData_16Bit(color); 
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
    unsigned int i,m;  
    u8 buff[2];
    buff[0] = Color>>8;
    buff[1] = Color&0xFF;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   
	LCD_CS_CLR;
	LCD_RS_SET;
	for(i=0;i<lcddev.height;i++){
        for(m=0;m<lcddev.width;m++){	
                spi_send_only(buff, 2);
		}
	}
	LCD_CS_SET;
} 

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_RESET(void)
{
	LCD_RST_CLR;
	msleep(10);	
	LCD_RST_SET;
    LCD_BLK_SET;
	msleep(10);
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{  								 
//如果mcu的复位引脚没有引出来，则接PB8，调用下列复位函数	
 	LCD_RESET(); //LCD 复位
//*************3.5 ST7796S IPS初始化**********//	
	LCD_WR_REG(0x11);     

	msleep(120);                //Delay 120ms

	LCD_WR_REG(0x36);     // Memory Data Access Control MY,MX~~
	LCD_WR_DATA(0x48);   

	LCD_WR_REG(0x3A);     
	LCD_WR_DATA(0x55);   

	LCD_WR_REG(0xF0);     // Command Set Control
	LCD_WR_DATA(0xC3);   

	LCD_WR_REG(0xF0);     
	LCD_WR_DATA(0x96);   

	LCD_WR_REG(0xB4);     
	LCD_WR_DATA(0x02);   

	LCD_WR_REG(0xB7);     
	LCD_WR_DATA(0xC6);   

	LCD_WR_REG(0xC0);     
	LCD_WR_DATA(0xC0);   
	LCD_WR_DATA(0x00);   

	LCD_WR_REG(0xC1);     
	LCD_WR_DATA(0x13);   

	LCD_WR_REG(0xC2);     
	LCD_WR_DATA(0xA7);   

	LCD_WR_REG(0xC5);     
	LCD_WR_DATA(0x21);   

	LCD_WR_REG(0xE8);     
	LCD_WR_DATA(0x40);   
	LCD_WR_DATA(0x8A);   
	LCD_WR_DATA(0x1B);   
	LCD_WR_DATA(0x1B);   
	LCD_WR_DATA(0x23);   
	LCD_WR_DATA(0x0A);   
	LCD_WR_DATA(0xAC);   
	LCD_WR_DATA(0x33);   

	LCD_WR_REG(0xE0);     
	LCD_WR_DATA(0xD2);   
	LCD_WR_DATA(0x05);   
	LCD_WR_DATA(0x08);   
	LCD_WR_DATA(0x06);   
	LCD_WR_DATA(0x05);   
	LCD_WR_DATA(0x02);   
	LCD_WR_DATA(0x2A);   
	LCD_WR_DATA(0x44);   
	LCD_WR_DATA(0x46);   
	LCD_WR_DATA(0x39);   
	LCD_WR_DATA(0x15);   
	LCD_WR_DATA(0x15);   
	LCD_WR_DATA(0x2D);   
	LCD_WR_DATA(0x32);   

	LCD_WR_REG(0xE1);     
	LCD_WR_DATA(0x96);   
	LCD_WR_DATA(0x08);   
	LCD_WR_DATA(0x0C);   
	LCD_WR_DATA(0x09);   
	LCD_WR_DATA(0x09);   
	LCD_WR_DATA(0x25);   
	LCD_WR_DATA(0x2E);   
	LCD_WR_DATA(0x43);   
	LCD_WR_DATA(0x42);   
	LCD_WR_DATA(0x35);   
	LCD_WR_DATA(0x11);   
	LCD_WR_DATA(0x11);   
	LCD_WR_DATA(0x28);   
	LCD_WR_DATA(0x2E);   

	LCD_WR_REG(0xF0);     
	LCD_WR_DATA(0x3C);   
	LCD_WR_REG(0xF0);     
	LCD_WR_DATA(0x69);  

	msleep(120);                
	LCD_WR_REG(0x21);     
	LCD_WR_REG(0x29);

    LCD_direction(USE_HORIZONTAL);//设置LCD显示方向 
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd);

	LCD_WriteRAM_Prepare();	//开始写入GRAM			
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
			lcddev.rramcmd=0x2E;
			lcddev.dir = direction%4;
	switch(lcddev.dir){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x36,(1<<3)|(1<<6));
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<5));
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,(1<<3)|(1<<7));
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<6)|(1<<5));
		break;	
		default:break;
	}	
}	 




