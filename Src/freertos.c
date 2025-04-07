/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "PID_MODEL.h"
#include "rtwtypes.h"
#include <math.h>
#include "bsp_fdcan.h"
#include "motorctrl.h"
#include "stdio.h"
#include "math.h"
#include "dm_motor_drv.h"
#include "dm_motor_ctrl.h"
#include "UPPER_LOCATION.h"
#include "stdio.h"
#include "string.h"
#include "sbus.h"
#include "R1_dribble.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t key_sig[10]={1};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for chassis_control */
osThreadId_t chassis_controlHandle;
const osThreadAttr_t chassis_control_attributes = {
  .name = "chassis_control",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for run_ball */
osThreadId_t run_ballHandle;
const osThreadAttr_t run_ball_attributes = {
  .name = "run_ball",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for shoot_ball */
osThreadId_t shoot_ballHandle;
const osThreadAttr_t shoot_ball_attributes = {
  .name = "shoot_ball",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void start_chassis_control(void *argument);
void start_run_ball(void *argument);
void start_shoot_ball(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of chassis_control */
  chassis_controlHandle = osThreadNew(start_chassis_control, NULL, &chassis_control_attributes);

  /* creation of run_ball */
  run_ballHandle = osThreadNew(start_run_ball, NULL, &run_ball_attributes);

  /* creation of shoot_ball */
  shoot_ballHandle = osThreadNew(start_shoot_ball, NULL, &shoot_ball_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_start_chassis_control */
/**
  * @brief  Function implementing the chassis_control thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_start_chassis_control */
void start_chassis_control(void *argument)
{
  /* USER CODE BEGIN start_chassis_control */
  /* Infinite loop */
  for(;;)
  {
		control_chassis();
  }
  /* USER CODE END start_chassis_control */
}

/* USER CODE BEGIN Header_start_run_ball */
/**
* @brief Function implementing the run_ball thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_run_ball */
void start_run_ball(void *argument)
{
  /* USER CODE BEGIN start_run_ball */
	TickType_t previous_wake_time = xTaskGetTickCount();
	
  /* Infinite loop */
  for(;;)
  {
		if(key_sig[0]){
			going_up();
			vTaskDelayUntil(&previous_wake_time,pdMS_TO_TICKS(1000));
			dribbling();
			key_sig[0]=0;
		}
	
  }
  /* USER CODE END start_run_ball */
}

/* USER CODE BEGIN Header_start_shoot_ball */
/**
* @brief Function implementing the shoot_ball thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_shoot_ball */
void start_shoot_ball(void *argument)
{
  /* USER CODE BEGIN start_shoot_ball */
	TickType_t previous_wake_time = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
    if(key_sig[1]){

			vTaskDelayUntil(&previous_wake_time,pdMS_TO_TICKS(1000));

			key_sig[1]=0;
		}
  }
  /* USER CODE END start_shoot_ball */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

