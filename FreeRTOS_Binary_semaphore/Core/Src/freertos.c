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
uint32_t shared_var;
/* USER CODE END Variables */
/* Definitions for Task_one */
osThreadId_t Task_oneHandle;
const osThreadAttr_t Task_one_attributes = {
  .name = "Task_one",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_two */
osThreadId_t Task_twoHandle;
const osThreadAttr_t Task_two_attributes = {
  .name = "Task_two",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_Three */
osThreadId_t Task_ThreeHandle;
const osThreadAttr_t Task_Three_attributes = {
  .name = "Task_Three",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_Four */
osThreadId_t Task_FourHandle;
const osThreadAttr_t Task_Four_attributes = {
  .name = "Task_Four",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};
/* Definitions for myBinarySem02 */
osSemaphoreId_t myBinarySem02Handle;
const osSemaphoreAttr_t myBinarySem02_attributes = {
  .name = "myBinarySem02"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskOne(void *argument);
void TaskTwo(void *argument);
void TaskThree(void *argument);
void TaskFour(void *argument);

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

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 0, &myBinarySem01_attributes);

  /* creation of myBinarySem02 */
  myBinarySem02Handle = osSemaphoreNew(1, 1, &myBinarySem02_attributes);

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
  /* creation of Task_one */
  Task_oneHandle = osThreadNew(TaskOne, NULL, &Task_one_attributes);

  /* creation of Task_two */
  Task_twoHandle = osThreadNew(TaskTwo, NULL, &Task_two_attributes);

  /* creation of Task_Three */
  Task_ThreeHandle = osThreadNew(TaskThree, NULL, &Task_Three_attributes);

  /* creation of Task_Four */
  Task_FourHandle = osThreadNew(TaskFour, NULL, &Task_Four_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_TaskOne */
/**
  * @brief  Function implementing the Task_one thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskOne */
void TaskOne(void *argument)
{
	 /* USER CODE BEGIN Task_One */
	 uint32_t Counter_Task = 0;
	 /* Infinite loop */
	 for(;;)
	 {
		osDelay(2000);
		printf("TaskTwo is running = %i \n",(signed int) Counter_Task);
		Counter_Task++;
		/* Release Semaphore 1 */
		osSemaphoreRelease(myBinarySem01Handle);
	 }
	 /* USER CODE END Task_One */
}

/* USER CODE BEGIN Header_TaskTwo */
/**
* @brief Function implementing the Task_two thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskTwo */
void TaskTwo(void *argument)
{
	/* USER CODE BEGIN Task_One */
		 uint32_t Counter_Task = 0;
		 /* Infinite loop */
		 for(;;)
		 {
			 /* the task will execute in three steps
			  * if the semaphore is available once it acquired
			  * if the blocking time ended
			  * if there external interrupt */
			osSemaphoreAcquire(myBinarySem01Handle,4000);
			printf("TaskTwo is running = %i \n",(signed int) Counter_Task);
			Counter_Task++;
		 }
		 /* USER CODE END Task_One */
}

/* USER CODE BEGIN Header_TaskThree */
/**
* @brief Function implementing the Task_Three thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskThree */
void TaskThree(void *argument)
{
  /* USER CODE BEGIN TaskThree */
  /* Infinite loop */
  for(;;)
  {
	osSemaphoreAcquire(myBinarySem02Handle,0);
	shared_var++;
	printf("TaskThree is running \n");
	osSemaphoreRelease(myBinarySem02Handle);
    osDelay(500);
  }
  /* USER CODE END TaskThree */
}

/* USER CODE BEGIN Header_TaskFour */
/**
* @brief Function implementing the Task_Four thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskFour */
void TaskFour(void *argument)
{
  /* USER CODE BEGIN TaskFour */
  /* Infinite loop */
  for(;;)
  {
	osSemaphoreAcquire(myBinarySem02Handle,0);
	printf("TaskFour is running %i \n",(signed int)TaskFour);
	osSemaphoreRelease(myBinarySem02Handle);
    osDelay(500);
  }
  /* USER CODE END TaskFour */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
