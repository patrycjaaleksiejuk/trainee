#ifndef __LCD_H
#define __LCD_H

#include "stm32l0xx_hal.h"
#include "spi.h"
#include <stdio.h>

#define  hx8357_LCD_PIXEL_WIDTH    ((uint16_t)320)
#define  hx8357_LCD_PIXEL_HEIGHT   ((uint16_t)960)

#define SPI2_DC_LOW()    HAL_GPIO_WritePin(SPI2_DC_GPIO_Port, SPI2_DC_Pin, GPIO_PIN_RESET)
#define SPI2_DC_HIGH()   HAL_GPIO_WritePin(SPI2_DC_GPIO_Port, SPI2_DC_Pin, GPIO_PIN_SET)
#define SPI2_CS_LOW()    HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET)
#define SPI2_CS_HIGH()   HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET)
#define WHITE_COLOR      255
#define RED_COLOR        200
#define GREEN_COLOR      100
#define YELLOW_COLOR     198

void hx8357_WriteMultipleData(uint8_t* data, uint16_t size);
void hx8357_WriteReg(uint8_t command);
void hx8357IO_WriteComPar(uint8_t LCDReg, uint8_t LCDRegValue);
void lcd_Init(void);
void hx8357_fillScreen(uint8_t color, uint16_t width, uint16_t height);
void hx8357_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void hx8357_putChar(uint16_t value, uint8_t color);
void hx8357_putString(char *ch, uint16_t size, uint16_t row, uint16_t move, uint8_t color);
#endif /* __LCD_H */
