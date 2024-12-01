/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdlib.h>
#include "cli.h"
#include "elevator_control.h"
#include "external_control.h"

#define BACKSPACE 8		//ASCII value
#define DELETE 127
#define ENTER_KEY 13	//ASCII value
uint8_t RXBuffer[1];
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char cliBufferRx[50];
int bufferIndex = 0;
int command=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

osThreadId EmergencyTaskHandle;
osThreadId EleVControlTaskHandle;
osThreadId cliReceiveHandle;
osThreadId ButtonCheckHandle;
osMessageQId Input_QueueHandle;
osMessageQId Emergency_StopHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
void Emergency_Stop_Task(void const * argument);
void Elevator_Control_Task(void const * argument);
void CLI_Receive_Task(void const * argument);
void ButtonCheck_Task(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim3);
  uartReceive(RXBuffer, 1);
  CLI_Init();
  ExternalControl_Init();
  /* USER CODE END 2 */

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
  /* definition and creation of Input_Queue */
  osMessageQDef(Input_Queue, 16, uint32_t);
  Input_QueueHandle = osMessageCreate(osMessageQ(Input_Queue), NULL);

  /* definition and creation of Emergency_Stop */
  osMessageQDef(Emergency_Stop, 8, ElevatorState);
  Emergency_StopHandle = osMessageCreate(osMessageQ(Emergency_Stop), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of EmergencyTask */
  osThreadDef(EmergencyTask, Emergency_Stop_Task, osPriorityHigh, 0, 128);
  EmergencyTaskHandle = osThreadCreate(osThread(EmergencyTask), NULL);

  /* definition and creation of EleVControlTask */
  osThreadDef(EleVControlTask, Elevator_Control_Task, osPriorityBelowNormal, 0, 128);
  EleVControlTaskHandle = osThreadCreate(osThread(EleVControlTask), NULL);

  /* definition and creation of cliReceive */
  osThreadDef(cliReceive, CLI_Receive_Task, osPriorityNormal, 0, 128);
  cliReceiveHandle = osThreadCreate(osThread(cliReceive), NULL);

  /* definition and creation of ButtonCheck */
  osThreadDef(ButtonCheck, ButtonCheck_Task, osPriorityNormal, 0, 128);
  ButtonCheckHandle = osThreadCreate(osThread(ButtonCheck), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin PA8 PA9 PA10 */
  GPIO_InitStruct.Pin = LD2_Pin|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
 * @brief Callback function for handling GPIO external interrupts.
 *        Triggered when a pin configured for external interrupt generates an event.
 *
 * @param GPIO_Pin The pin that caused the interrupt.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Check if the interrupt is triggered by pin PC13
    if (GPIO_Pin == GPIO_PIN_13)
    {
    	// Send a simple signal to the task
    	osMessagePut(Emergency_StopHandle, 1, osWaitForever);
    }
}

/**
 * @brief Callback function called when a UART transmission is complete.
 *
 * @param huart Pointer to the UART handle structure.
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {}
}

/**
 * @brief Callback function called when a UART reception is complete.
 *
 * @param huart Pointer to the UART handle structure.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	uartReceive(RXBuffer, 1);
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_Emergency_Stop_Task */
/**
  * @brief  Function implementing the EmergencyTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Emergency_Stop_Task */
void Emergency_Stop_Task(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	osEvent event = osMessageGet(Emergency_StopHandle, osWaitForever);
    if (event.status == osEventMessage)
    {
       restoreCursorPosition();
       saveCursorPosition();
       emergencyStopOperations();
       restoreCursorPosition();
    }
	osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Elevator_Control_Task */
/**
* @brief Function implementing the EleVControlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Elevator_Control_Task */
void Elevator_Control_Task(void const * argument)
{
  /* USER CODE BEGIN Elevator_Control_Task */
  /* Infinite loop */
  for(;;)
  {
	osEvent event = osMessageGet(Input_QueueHandle, osWaitForever);
	if (event.status == osEventMessage) {
	  char* inputMessage = (char*)event.value.v;
	  if (strcmp(inputMessage, "M") == 0) {
		  saveCursorPosition();
		  maintenanceMode();
		  restoreCursorPosition();
      }
	  else if (strcmp(inputMessage, "R") == 0){
		  saveCursorPosition();
		  resumeElevatorOperations();
		  restoreCursorPosition();
	  }
      else if (strcmp(inputMessage, "open") == 0){
    	  activateDoorOpening();
      }
      else if (strcmp(inputMessage, "close") == 0){
    	  activateDoorClosing();
      }
      else {
    	  int target = atoi(inputMessage);
    	  moveElevatorToFloor(target);
      }
	}
	osDelay(1);
    CLI_Prompt();
  }
  /* USER CODE END Elevator_Control_Task */
}

/* USER CODE BEGIN Header_CLI_Receive_Task */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CLI_Receive_Task */
void CLI_Receive_Task(void const * argument)
{
  /* USER CODE BEGIN CLI_Receive_Task */
  uartReceive(RXBuffer, 1);
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
    if (RXBuffer[0] != '\0') {
      if (RXBuffer[0] == ENTER_KEY) {
          cliBufferRx[bufferIndex] = '\0';  // Null-terminate the buffer
          if (bufferIndex > 0) {
              // Send the input to the Elevator Control Task
              osMessagePut(Input_QueueHandle, (uint32_t)cliBufferRx, osWaitForever);
              bufferIndex = 0;
          }
      } else if (RXBuffer[0] == BACKSPACE || RXBuffer[0] == DELETE) {
          if (bufferIndex > 0) {
              bufferIndex--;
              char data[] = "\b \b";  // Erase character on screen
              uartTransmit(data);
          }
      } else {
          if (bufferIndex < sizeof(cliBufferRx) - 1) {
              cliBufferRx[bufferIndex++] = RXBuffer[0];
              char echoChar[2] = {RXBuffer[0], '\0'};
              uartTransmit(echoChar);
          }
      }
    }

    // Clear RXBuffer for the next byte
    memset(RXBuffer, 0, sizeof(RXBuffer));

    // Start receiving the next byte
    uartReceive(RXBuffer, 1);

  }
  /* USER CODE END CLI_Receive_Task */
}

/* USER CODE BEGIN Header_ButtonCheck_Task */
/**
* @brief Function implementing the ButtonCheck thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonCheck_Task */
void ButtonCheck_Task(void const * argument)
{
  /* USER CODE BEGIN ButtonCheck_Task */
  ExternalControl_Init();
  /* Infinite loop */
  for(;;)
  {
	  // Check Button 1
      if (HAL_GPIO_ReadPin(BUTTON_1_PORT, BUTTON_1_PIN) == GPIO_PIN_RESET)
      {
          osDelay(50);
          if (HAL_GPIO_ReadPin(BUTTON_1_PORT, BUTTON_1_PIN) == GPIO_PIN_RESET)
          {
        	  moveElevatorToFloor(1);
          }
      }

      // Check Button 2
      if (HAL_GPIO_ReadPin(BUTTON_2_PORT, BUTTON_2_PIN) == GPIO_PIN_RESET)
      {
          osDelay(50);
          if (HAL_GPIO_ReadPin(BUTTON_2_PORT, BUTTON_2_PIN) == GPIO_PIN_RESET)
          {
        	  moveElevatorToFloor(2);
          }
      }

      // Check Button 3
      if (HAL_GPIO_ReadPin(BUTTON_3_PORT, BUTTON_3_PIN) == GPIO_PIN_RESET)
      {
          osDelay(50);
          if (HAL_GPIO_ReadPin(BUTTON_3_PORT, BUTTON_3_PIN) == GPIO_PIN_RESET)
          {
        	  moveElevatorToFloor(2);
          }
      }

      // Check Button 4
      if (HAL_GPIO_ReadPin(BUTTON_4_PORT, BUTTON_4_PIN) == GPIO_PIN_RESET)
      {
          osDelay(50);
          if (HAL_GPIO_ReadPin(BUTTON_4_PORT, BUTTON_4_PIN) == GPIO_PIN_RESET)
          {
        	  moveElevatorToFloor(3);
          }
      }
      osDelay(10);
  }
  /* USER CODE END ButtonCheck_Task */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
