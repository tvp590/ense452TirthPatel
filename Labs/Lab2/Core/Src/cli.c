/*
    Name : Tirth V Patel
    SID  : 200435378
    File : cli.c
    Description : This file contains the implementation of the CLI module.
 */



#include "cli.h"
#include <string.h>
#include <stdio.h>
#include "main.h"

static uint8_t ledState = 0;
extern UART_HandleTypeDef huart2;

void CLI_Init(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void CLI_PrintPrompt(void) {
	char prompt[] = "\r\nCLI > \r\n";
	HAL_UART_Transmit(&huart2, (uint8_t *)prompt, strlen(prompt), 5000);
}

void CLI_PrintHelp(void) {
	char helpMessage[] =
			 " Available commands:\r\n"
			  "1      : Turn on the LED\r\n"
			  "2      : Turn off the LED\r\n"
			  "3      : Query the state of the LED\r\n"
			  "4      : Display this help message\r\n";

	HAL_UART_Transmit(&huart2, (uint8_t *)helpMessage, strlen(helpMessage), 5000);

}

void CLI_TurnOnLED(void) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	ledState = 1;
	char message[] = " LED is turned ON\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), 5000);
}

void CLI_TurnOffLED(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    ledState = 0;
    char message[] = " LED is turned OFF\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), 5000);
}

void CLI_QueryLEDState(void) {
	char message[30];
	sprintf(message, " LED is currently %s\r\n", ledState ? "ON" : "OFF");
	HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), 5000);

}

void CLI_ExecuteCommand(int command) {
    switch(command) {
        case 1:
            CLI_TurnOnLED();
            break;
        case 2:
            CLI_TurnOffLED();
            break;
        case 3:
            CLI_QueryLEDState();
            break;
        case 4:
            CLI_PrintHelp();
            break;
        default:
            // Send an error message for unknown commands
            char errorMessage[] = " Unknown command. Type 4 for help.\r\n";
            HAL_UART_Transmit(&huart2, (uint8_t *)errorMessage, strlen(errorMessage), 5000);
            break;
    }
}

