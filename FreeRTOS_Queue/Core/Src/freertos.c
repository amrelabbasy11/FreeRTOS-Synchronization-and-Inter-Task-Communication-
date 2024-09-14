/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include <stdio.h>
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
/* Definitions for Task_One */
osThreadId_t Task_OneHandle;
const osThreadAttr_t Task_One_attributes = {
  .name = "Task_One",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_Two */
osThreadId_t Task_TwoHandle;
const osThreadAttr_t Task_Two_attributes = {
  .name = "Task_Two",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskOne(void *argument);
void TaskTwo(void *argument);

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

  /* Create the queue(s) */
  /* creation of myQueue01 */

  myQueue01Handle = osMessageQueueNew (5, sizeof(uint16_t), &myQueue01_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_One */
  Task_OneHandle = osThreadNew(TaskOne, NULL, &Task_One_attributes);

  /* creation of Task_Two */
  Task_TwoHandle = osThreadNew(TaskTwo, NULL, &Task_Two_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_TaskOne */
/**
  * @brief  Function implementing the Task_One thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskOne */
void TaskOne(void *argument)
{
  /* USER CODE BEGIN TaskOne */
  uint32_t Task_Counter = 0;
  osStatus_t Ret_Val = 0;
  /* Infinite loop */
  for(;;)
  {
	Ret_Val = osMessageQueuePut(myQueue01Handle, &Task_Counter, NULL, 500);
	if(Ret_Val == osOK){
		printf("TaskOne is running : %i , RetVal : %i",(signed int)Task_Counter,(signed int)Ret_Val);
		Task_Counter++;
		if(Task_Counter == 4){
			Task_Counter = 0;
		}
		else{
			/* Nothing */
		}
	}
	else{
		printf("TaskOne is running With error Value : %i",(signed int)Ret_Val);
	}

    osDelay(1000);
  }
  /* USER CODE END TaskOne */
}

/* USER CODE BEGIN Header_TaskTwo */
/**
* @brief Function implementing the Task_Two thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskTwo */
void TaskTwo(void *argument)
{
  /* USER CODE BEGIN TaskTwo */
	uint32_t Task_Counter = 0;
	osStatus_t Ret_Val = 0;
  /* Infinite loop */
  for(;;)
  {
	Ret_Val = osMessageQueueGet(myQueue01Handle, &Task_Counter, NULL, 500);
	if(Ret_Val == osOK){
		printf("TaskTwo is Receiving : %i ",(signed int)Task_Counter);
		Task_Counter++;
	}
	else{
		printf("TaskTwo is running With error Value : %i",(signed int)Ret_Val);
	}
    osDelay(1000);
  }
  /* USER CODE END TaskTwo */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
