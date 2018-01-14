#include "lcd.h"

extern const uint8_t Grotesk16x32[6080];  /* font's table */
static uint8_t bitmap[16*32] = {0}; /* pixel's table */

/* sending the data */
void hx8357_WriteMultipleData(uint8_t* data, uint16_t size)
{
/* Reset LCD control line CS */
  SPI2_CS_LOW();
  
/* Set LCD data/command line DC to High */
  SPI2_DC_HIGH();
  
  HAL_SPI_Transmit(&hspi2, data, size, 100);
}

/* writing commands to the register */
void hx8357_WriteReg(uint8_t command)
{
/* Reset LCD control line CS */
  SPI2_CS_LOW();
  
/* Set LCD data/command line DC to Low */
  SPI2_DC_LOW();
  
  HAL_SPI_Transmit(&hspi2, &command, 1, 100);
}

/* writing command with parametre */
void hx8357IO_WriteComPar(uint8_t LCDReg, uint8_t LCDRegValue)
{
  hx8357_WriteReg(LCDReg);
  hx8357_WriteMultipleData(&LCDRegValue, 1);
}

/* initialization of the display */
void lcd_Init(void)
{    
  
  SPI2_CS_HIGH();
  uint8_t data = 0;
  /* reset */
  hx8357_WriteReg(0x01);
  HAL_Delay(10);
  
  /* setextc */
  hx8357_WriteReg(0xB9); 
  data = 0xFF;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x83;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x57;
  hx8357_WriteMultipleData(&data, 1);
  HAL_Delay(30);
  
  /* setrgb */
  hx8357_WriteReg(0xB3); 
  data = 0x80;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x00;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x06;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x06;
  hx8357_WriteMultipleData(&data, 1);
  
  /* setcom */
  hx8357_WriteReg(0xB6); 
  data = 0x25;
  hx8357_WriteMultipleData(&data, 1);
  
  /* srtosc */
  hx8357_WriteReg(0xB0); 
  data = 0x68;
  hx8357_WriteMultipleData(&data, 1);
  
  /* set panel */
  hx8357_WriteReg(0xCC); 
  data = 0x05;
  hx8357_WriteMultipleData(&data, 1);
  
  /* set power */
  hx8357_WriteReg(0xB1); 
  data = 0x00;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x15;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x1C;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x1C;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x83;
  hx8357_WriteMultipleData(&data, 1);
  data = 0xAA;
  hx8357_WriteMultipleData(&data, 1);
  
  /* setstba */
  hx8357_WriteReg(0xC0); 
  data = 0x50;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x50;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x01;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x3C;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x1E;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x08;
  hx8357_WriteMultipleData(&data, 1);
  
  /* setcyc */
  hx8357_WriteReg(0xB4); 
  data = 0x02;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x40;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x00;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x2A;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x2A;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x0D;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x78;
  hx8357_WriteMultipleData(&data, 1);
  
  /* setgamma */
  hx8357_WriteReg(0xE0); 
  data = 0x02;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x0A;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x11;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x1d;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x23;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x35;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x41;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x4B;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x4B;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x42;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x3A;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x27;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x1B;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x08;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x09;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x03;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x02;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x0A;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x11;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x1D;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x23;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x35;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x41;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x4B;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x4B;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x42;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x3A;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x27;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x1B;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x08;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x09;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x03;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x00;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x01;
  hx8357_WriteMultipleData(&data, 1);
  
  /* Set color mode, 1 arg, no delay: 16-bit color */
  hx8357IO_WriteComPar(0x3A, 0x55);
  /* macctl */
  hx8357IO_WriteComPar(0x36, 0xC0);
  /* teoff */
  hx8357IO_WriteComPar(0x35, 0x00);
  
  /* tear line */
  hx8357_WriteReg(0x44); 
  data = 0x00;
  hx8357_WriteMultipleData(&data, 1);
  data = 0x02;
  hx8357_WriteMultipleData(&data, 1);
  
  /* Out of sleep mode, 0 args, no delay */
  hx8357_WriteReg(0x11); 
  HAL_Delay(15);
  /* Normal display on, no args, no delay */
  hx8357_WriteReg(0x13);
  
  /* Begin writing to the memory - fill whole screen black*/
  hx8357_WriteReg(0x2C);
  for (int j = 0; j < hx8357_LCD_PIXEL_HEIGHT; j++)
  {
    hx8357_WriteMultipleData(&bitmap[0], hx8357_LCD_PIXEL_WIDTH);
  }
  
  /* Main screen turn on, no delay */
  hx8357_WriteReg(0x29);
}



void hx8357_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  uint8_t data = 0;
  /* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1) */
  hx8357_WriteReg(0x2A);
  data = (Xpos) >> 8;
  hx8357_WriteMultipleData(&data, 1);
  data = (Xpos) & 0xFF;
  hx8357_WriteMultipleData(&data, 1);
  data = (Xpos + Width - 1) >> 8;
  hx8357_WriteMultipleData(&data, 1);
  data = (Xpos + Width - 1) & 0xFF;
  hx8357_WriteMultipleData(&data, 1);
  /* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1) */
  hx8357_WriteReg(0x2B);
  data = (Ypos) >> 8;
  hx8357_WriteMultipleData(&data, 1);
  data = (Ypos) & 0xFF;
  hx8357_WriteMultipleData(&data, 1);
  data = (Ypos + Height - 1) >> 8;
  hx8357_WriteMultipleData(&data, 1);
  data = (Ypos + Height - 1) & 0xFF;
  hx8357_WriteMultipleData(&data, 1);
}
/* clearing the display */
void hx8357_fillScreen(uint8_t color, uint16_t Xpos, uint16_t Ypos)
{
  hx8357_SetDisplayWindow(0, 0, Xpos, Ypos);
  
  for (int j = 0; j < Xpos; j++)
  {
    bitmap[j] = color;
  }
  /* begin writing to memory */
  hx8357_WriteReg(0x2C); 
  for (int j = 0; j < Ypos; j++)
  {
    hx8357_WriteMultipleData(&bitmap[0], Xpos);
  }
  /* stop writing */
  hx8357_WriteReg(0x00);
}
/* displaying the char on the screen */
void hx8357_putChar(uint16_t value, uint8_t color)
{
  uint16_t count = 0; 
  uint16_t startValue = (value - 32) * 64;
  uint16_t endValue = startValue + 64;
  
  for (uint16_t i = startValue; i < endValue; i++)
  {
     for (uint8_t j = 0; j < 8; j++)
     {
       bitmap[count] = ((Grotesk16x32[i] << j) & 0x80) ? color : 0;
       count++;
     }
  }
  
  hx8357_WriteReg(0x2C);
  hx8357_WriteMultipleData(&bitmap[0], (uint16_t)(16*32));
}

/* displaying the string on the screen */
void hx8357_putString(char *ch, uint16_t size, uint16_t row, uint16_t move, uint8_t color)
{
  for( uint16_t i = 0; i < size; i++)
  {
   if (*(ch + i) == NULL) return; //check if this is the end of the string
   hx8357_SetDisplayWindow(i*10 + move, row*32, 8, 32);
   hx8357_putChar(*(ch + i), color);
  }
}

