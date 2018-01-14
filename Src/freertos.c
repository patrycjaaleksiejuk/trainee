/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "tsl_user.h"
#include "lcd.h"
#include "tim.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* USER CODE BEGIN Variables */
volatile diodeState buttonState; /* variable used as iterator of state machine, range: 0-3 */
static uint32_t pulseVal = 1600;  /* duty cycle of PWM */
volatile uint8_t isChanged = pdTRUE;  /* detection touching the touch sensor */

/* defines used for checking the touch sensor state and position */
#define LINEAR_DETECT ((MyLinRots[0].p_Data->StateId == TSL_STATEID_DETECT) || \
                       (MyLinRots[0].p_Data->StateId == TSL_STATEID_DEB_RELEASE_DETECT))
#define LINEAR_POSITION (MyLinRots[0].p_Data->Position)
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void)
  {
  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  }

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  tsl_user_status_t tsl_status;  /* enum defining of touch sensor */
  uint32_t move = 0;  /* shift the display */
  uint8_t color = 255;  /* set color for string */
  
  /* char tables for displaying strings */
  char ch[]="Controlled diode(s):"; 
  char colorName[maxState][9]={"G R E E N", "R E D    ", "B O T H  ", "M O V E  "};
  char str[17] = "PWM: 100%";

  /* Infinite loop */
  for(;;)
  {
    tsl_status = tsl_user_Exec();  /* fetching data from sensor and returning its state */
    if (tsl_status != TSL_USER_STATUS_BUSY)  /* checking if sensor is not busy */
    {
/* enabling brightness based on position of touch sensor */
      if (LINEAR_DETECT)
      {
        isChanged = pdTRUE;
        if (LINEAR_POSITION <= 4)
        {
          pulseVal = 200;
        }
        else if (LINEAR_POSITION <= 8)
        {
          pulseVal = 800;
        }
        else if (LINEAR_POSITION <= 12)
        {
          pulseVal = 1200;
        }
        else
        {
          pulseVal = 1600;
        }
        PWM_setting(pulseVal);
      }
    }
/* main state machine for enabling diodes based on pressed button */
    switch (buttonState)
    {
      case greenDiode:                                        // enabling green diode 
        color = GREEN_COLOR;
        TIMx_EnableGreenDiodeMode();
      break;
      
      case redDiode:                                         // enabling red diode
        color = RED_COLOR;
        TIMx_EnableRedDiodeMode();
      break;
       
      case bothDiode:                                        // enabling both diodes
        color = YELLOW_COLOR;
        TIMx_EnableBothDiodeMode();
      break;
      
      case moveScreen:                                      // enabling moving screen
        color = WHITE_COLOR;
        move = pulseVal / 20;
      break;
      
      default:
        assert_param(0);
      break;
    }
/* detection touch sensor */
    if (isChanged == pdTRUE)
    {
      /* detection state of the button */
      if (buttonState == moveScreen)
      {
        /* fill the display black color */
        hx8357_fillScreen(0, hx8357_LCD_PIXEL_WIDTH, hx8357_LCD_PIXEL_HEIGHT/5);
      }
      else
      {
        sprintf((char*)str, "PWM: %d%% ", (int)pulseVal/16);
      }
      /* printing strings */
      hx8357_putString(ch, sizeof(ch), 0, move, WHITE_COLOR);
      hx8357_putString(colorName[buttonState], sizeof(colorName[buttonState]), 1, move, color);
      hx8357_putString(str, sizeof(str), 2, move, WHITE_COLOR);
      isChanged = pdFALSE;
    }
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
