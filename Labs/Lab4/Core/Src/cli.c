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

extern UART_HandleTypeDef huart2;

void CLI_Init(void) {
	CLI_Transmit("Initializing CLI...\r\n");
	CLI_Transmit("Measurement System Initialized.\r\n");
	CLI_Transmit("All measurements are averages of 100 trials.\r\n");
}

void CLI_Transmit(const char* message) {
	HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), 5000);
}

void CLI_TransmitResult(const char* description, uint32_t result) {
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "%s: %u ticks\r\n", description, result);
	CLI_Transmit(buffer);
}
