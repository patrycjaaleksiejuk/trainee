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
volatile diodeState buttonState; // variable used as iterator of state machine, range: 0-2
static uint32_t pulseVal = 1600;  // duty cycle of PWM
volatile uint8_t isChanged = pdTRUE;

/* defines used for checking the touch sensor state and position */
#define LINEAR_DETECT ((MyLinRots[0].p_Data->StateId == TSL_STATEID_DETECT) || \
                       (MyLinRots[0].p_Data->StateId == TSL_STATEID_DEB_RELEASE_DETECT))
#define LINEAR_POSITION (MyLinRots[0].p_Data->Position)
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  TIM_OC_InitTypeDef sConfigOC;
  tsl_user_status_t tsl_status;  // enum defining of touch sensor
  uint32_t move = 0;
  
  char ch[]="Controlled diode(s):";
  char color[maxState][6]={"Green", "Red  ", "Both ", "Move "};
  char str[17] = "PWM: 100%";
    
  fill_Screen(0, hx8357_LCD_PIXEL_WIDTH, hx8357_LCD_PIXEL_HEIGHT);
  /* Infinite loop */
  for(;;)
  {
    if (isChanged == pdTRUE)
    {
      lcd_PutString(ch, sizeof(ch), 0, move);
      lcd_PutString(color[buttonState], sizeof(color[buttonState]), 1, move);
      sprintf((char*)str, "PWM: %d%% ", (int)pulseVal/16);
      lcd_PutString(str, sizeof(str), 2, move);
      isChanged = pdFALSE;
    }
    
    tsl_status = tsl_user_Exec();  // fetching data from sensor and returning its state
    if (tsl_status != TSL_USER_STATUS_BUSY)  // checking if sensor is not busy
    {
// enabling brightness based on position of touch sensor
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
// setting of PWM duty cycles for both diodes        
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim22, TIM_CHANNEL_1);
        sConfigOC.OCMode = TIM_OCMODE_PWM1;
        sConfigOC.Pulse = pulseVal;
        sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
        HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
        HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC, TIM_CHANNEL_1);
      }
    }
// main state machine for enabling diodes based on pressed button 
    switch (buttonState)
    {
      case greenDiode:                                         // enabling green diode 
        TIMx_EnableGreenDiodeMode();
      break;
      
      case redDiode:                                         // enabling red diode
        TIMx_EnableRedDiodeMode();
      break;
       
      case bothDiode:                                         // enabling both diodes
        TIMx_EnableBothDiodeMode();
      break;
      
      case moveScreen:
        move = pulseVal / 80;
      
      default:
        assert_param(0);
      break;
    }
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
