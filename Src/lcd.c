#include "lcd.h"

extern const uint8_t Grotesk16x32[6080];
static uint8_t bitmap[16*32] = {0};

void LCD_IO_WriteMultipleData(uint8_t* command, uint16_t size)
{
    /* Reset LCD control line CS */
  SPI2_CS_LOW();
  
  /* Set LCD data/command line DC to High */
  SPI2_DC_HIGH();
  
  HAL_SPI_Transmit(&hspi2, command, size, 100);
  
}

void LCD_IO_WriteReg(uint8_t command)
{
    /* Reset LCD control line CS */
  SPI2_CS_LOW();
  
  /* Set LCD data/command line DC to Low */
  SPI2_DC_LOW();
  
  HAL_SPI_Transmit(&hspi2, &command, 1, 100);
}

void hx8357_WriteReg(uint8_t LCDReg, uint8_t LCDRegValue)
{
  LCD_IO_WriteReg(LCDReg);
  LCD_IO_WriteMultipleData(&LCDRegValue, 1);
}

void lcd_Init(void)
{    
  
  SPI2_CS_HIGH();
  uint8_t data = 0;
  //reset
  LCD_IO_WriteReg(0x01);
  HAL_Delay(10);
  
  // set command
  LCD_IO_WriteReg(0xB9); 
  data = 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x83;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x57;
  LCD_IO_WriteMultipleData(&data, 1);
  HAL_Delay(300);
  
  //rgb
  LCD_IO_WriteReg(0xB3); 
  data = 0x80;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x00;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x06;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x06;
  LCD_IO_WriteMultipleData(&data, 1);
  
  //voltage
  LCD_IO_WriteReg(0xB6); 
  data = 0x25;
  LCD_IO_WriteMultipleData(&data, 1);
  
  //oscylator
  LCD_IO_WriteReg(0xB0); 
  data = 0x68;
  LCD_IO_WriteMultipleData(&data, 1);
  
  //panel
  LCD_IO_WriteReg(0xCC); 
  data = 0x05;
  LCD_IO_WriteMultipleData(&data, 1);
  
  //pwr
  LCD_IO_WriteReg(0xB1); 
  data = 0x00;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x15;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x1C;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x1C;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x83;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0xAA;
  LCD_IO_WriteMultipleData(&data, 1);
  
  //setstba
  LCD_IO_WriteReg(0xC0); 
  data = 0x50;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x50;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x01;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x3C;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x1E;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x08;
  LCD_IO_WriteMultipleData(&data, 1);
  
  //setcyc
  LCD_IO_WriteReg(0xB4); 
  data = 0x02;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x40;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x00;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x2A;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x2A;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x0D;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x78;
  LCD_IO_WriteMultipleData(&data, 1);
  
  //setgamma
  LCD_IO_WriteReg(0xE0); 
  data = 0x02;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x0A;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x11;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x1d;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x23;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x35;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x41;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x4B;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x4B;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x42;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x3A;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x27;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x1B;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x08;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x09;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x03;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x02;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x0A;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x11;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x1D;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x23;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x35;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x41;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x4B;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x4B;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x42;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x3A;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x27;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x1B;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x08;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x09;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x03;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x00;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x01;
  LCD_IO_WriteMultipleData(&data, 1);
  
  /* Set color mode, 1 arg, no delay: 16-bit color */
  hx8357_WriteReg(0x3A, 0x55);
  //macctl
  hx8357_WriteReg(0x36, 0xC0);
  //teoff
  hx8357_WriteReg(0x35, 0x00);
  
  //tear line
  LCD_IO_WriteReg(0x44); 
  data = 0x00;
  LCD_IO_WriteMultipleData(&data, 1);
  data = 0x02;
  LCD_IO_WriteMultipleData(&data, 1);
  
  /* Out of sleep mode, 0 args, no delay */
  LCD_IO_WriteReg(0x11); 
  HAL_Delay(150);
  /* Normal display on, no args, no delay */
  LCD_IO_WriteReg(0x13);
  /* Main screen turn on, no delay */
  LCD_IO_WriteReg(0x29);
}

void lcd_SetCursor(uint16_t Xpos, uint16_t Ypos) //!!!!!!!!!!!
{
  uint8_t data = 0;
  LCD_IO_WriteReg(0x2A);
  data = (Xpos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  LCD_IO_WriteReg(0x2B); 
  data = (Ypos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
}

void hx8357_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode) //!!!!!!!!!!!!
{
  uint8_t data = 0;
  if((Xpos >= hx8357_LCD_PIXEL_WIDTH) || (Ypos >= hx8357_LCD_PIXEL_HEIGHT)) 
  {
    return;
  }
  
  /* Set Cursor */
  lcd_SetCursor(Xpos, Ypos);
  
  data = RGBCode >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = RGBCode;
  LCD_IO_WriteMultipleData(&data, 1);
} 

void hx8357_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  uint8_t data = 0;
  /* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1) */
  LCD_IO_WriteReg(0x2A);
  data = (Xpos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos + Width - 1) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Xpos + Width - 1) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  /* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1) */
  LCD_IO_WriteReg(0x2B);
  data = (Ypos) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos + Height - 1) >> 8;
  LCD_IO_WriteMultipleData(&data, 1);
  data = (Ypos + Height - 1) & 0xFF;
  LCD_IO_WriteMultipleData(&data, 1);
}

void fill_Screen(uint8_t color, uint16_t Xpos, uint16_t Ypos)
{
  //setdisplay(start lini, xpos, ypos)
  LCD_IO_WriteReg(0x2C);
  
  for (int j = 0; j < Xpos; j++)
  {
    bitmap[j] = color;
  }
  
  SPI2_DC_HIGH();
  
  for (int j = 0; j < Ypos; j++)
  {
    LCD_IO_WriteMultipleData(&bitmap[0], Xpos);
  }
  LCD_IO_WriteReg(0x00);
}

void lcd_PutChar(uint16_t value)
{
  uint16_t count = 0;
  uint16_t startValue = (value - 32) * 64;
  uint16_t endValue = startValue + 64;
  
  for (uint16_t i = startValue; i < endValue; i++)
  {
     for (uint8_t j = 0; j < 8; j++)
     {
       bitmap[count] = ((Grotesk16x32[i] << j) & 0x80) ? 255 : 0;
       count++;
     }
  }
  
  LCD_IO_WriteReg(0x2C);
  LCD_IO_WriteMultipleData(&bitmap[0], (uint16_t)(16*32));
}

void lcd_PutString(char *ch, uint16_t size, uint16_t row, uint16_t move)
{
  for( uint16_t i = 0; i < size; i++)
  {
   if (*(ch + i) == NULL) return; //check if this is the end of the string
   hx8357_SetDisplayWindow(i*10 + move, row*32, 8, 32);
   lcd_PutChar(*(ch + i));
  }
}

