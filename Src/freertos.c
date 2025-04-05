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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

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

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void start_chassis_control(void *argument);
void start_run_ball(void *argument);

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
    osDelay(1);
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
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_run_ball */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

