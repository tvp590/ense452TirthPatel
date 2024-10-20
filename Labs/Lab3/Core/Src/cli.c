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
static uint8_t RXBuffer[1];
extern volatile uint8_t txComplete;
int UpdateCounter = 0;

void CLI_Init(void) {
	setupScreen();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_UART_Receive_IT(&huart2, RXBuffer,1);
}

void transmitData(const char *data){
//	while (!txComplete) {}
//	txComplete = 0;
	uint8_t buffer[512];
	size_t data_len = strlen(data);
	strcpy((char*)buffer, data);
	buffer[data_len] = '\0';
	HAL_UART_Transmit(&huart2, buffer,data_len,5000);
//	if(HAL_UART_Transmit(&huart2, buffer,data_len,5000) !=HAL_OK){
//		Error_Handler();
//	}
}

void CLI_PrintPrompt(void) {
	char prompt[] = "\r\nCLI >";
	transmitData(prompt);
}

void CLI_PrintHelp(void) {
	const char helpMessage[] =
			 "\r\nAvailable commands:\r\n"
			  "1      : Turn on the LED\r\n"
			  "2      : Turn off the LED\r\n"
			  "3      : Query the state of the LED\r\n"
			  "4      : Help message\r\n";
	transmitData(helpMessage);
}

void CLI_TurnOnLED(void) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	ledState = 1;
	const char message[] = " LED is turned ON\r\n";
	transmitData(message);
}

void CLI_TurnOffLED(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    ledState = 0;
    const char message[] = " LED is turned OFF\r\n";
    transmitData(message);
}

void CLI_QueryLEDState(void) {
	char message[30];
	sprintf(message, " LED is currently %s\r\n", ledState ? "ON" : "OFF");
	transmitData(message);
}

void CLI_ExecuteCommand(int command) {
	// Restore the saved cursor position
	 char restoreCursor[] = "\x1b[u";
	 transmitData(restoreCursor);

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
            const char errorMessage[] = " Unknown command. Type 4 for help.\r\n";
            transmitData(errorMessage);
            break;
    }

	 CLI_PrintPrompt();

    char saveCursor[] = "\x1b[s";
    transmitData(saveCursor);
}

void setupScreen() {
	// Clear the screen
	char clearScreen[] = "\x1b[2J";
	transmitData(clearScreen);

	// Set the cursor at the top-left corner (row 0, column 0)
	char moveToTop[] = "\x1b[0;0H";
	transmitData(moveToTop);

	// Create the status window
	char statusWindow[] = "Status >";
	transmitData(statusWindow);

	// Create a scroll window starting at row 12
	char scrollWindow[] = "\x1b[10;r";
	transmitData(scrollWindow);

}

void updateStatusWindow() {
	char moveToTop[] = "\x1b[0;0H";
	transmitData(moveToTop);

	char clearStatus[] = "\x1b[2K";  // Clear current line
	transmitData(clearStatus);

	char status[] = "Status >";
	transmitData(status);

	//Print current Status
	CLI_QueryLEDState();


	char UpdateMessage[] = "\r\n -x- Screen Updated Every Second -x-";
	transmitData(UpdateMessage);

	char restoreCursor[] = "\x1b[u";
	transmitData(restoreCursor);
}


