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
static uint8_t RXBuffer[1];
extern UART_HandleTypeDef huart2;

void CLI_Init(void) {
	setupScreen();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_UART_Receive_IT(&huart2, RXBuffer,1);
}

void transmitData(const char *data){
	size_t data_len = strlen(data);
	HAL_UART_Transmit(&huart2, (uint8_t *)data, data_len, 3000);
}

void CLI_PrintPrompt(void) {
	char prompt[] = "\r\nNewPeriod >";
	transmitData(prompt);
}

void setupScreen() {
	// Clear the screen
	char clearScreen[] = "\x1b[2J";
	transmitData(clearScreen);

	// Set the cursor at the top-left corner (row 0, column 0)
	char moveToTop[] = "\x1b[0;0H";
	transmitData(moveToTop);

	// Create the status window
	char statusWindow[] = "Period > 500";
	transmitData(statusWindow);

	char scrollRegion[] = "\x1b[5;24r";
	transmitData(scrollRegion);

	// Create a scroll window starting at row 12
	char moveToScrollStart[] = "\x1b[5;0H";
	transmitData(moveToScrollStart);

}

void updateStatusWindow(char period_t[]) {

	char saveCursor[] = "\x1b[s";
	transmitData(saveCursor);

	char moveToTop[] = "\x1b[0;0H";
	transmitData(moveToTop);

	char clearStatus[] = "\x1b[2K";  // Clear current line
	transmitData(clearStatus);

	char status[] = "Period > ";
	transmitData(status);

	//Print current Period
	transmitData(period_t);

	char restoreCursor[] = "\x1b[u";
	transmitData(restoreCursor);
}


