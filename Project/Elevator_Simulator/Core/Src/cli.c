/******************************************************************************
 * File Name: cli.c
 * Author: Tirth V Patel
 * Student ID: 200435378
 * Date: November 14, 2024
 *
 * Description:
 * Implements the Command Line Interface (CLI) for the elevator control system,
 * handling UART communication, dynamic status updates, and user interactions.
 ******************************************************************************/

#include "cli.h"

// Transmit a string over UART
void uartTransmit(const char* str) {
	 HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str),1000);
}

// Receive data over UART in interrupt mode
void uartReceive(uint8_t *buffer, uint16_t size) {
    HAL_UART_Receive_IT(&huart2, buffer, size);
}

// Clear the terminal screen
void clearScreen(void) {
    uartTransmit(CLEAR_SCREEN);
}

// Save the current cursor position
void saveCursorPosition() {
	uartTransmit("\033[s");
}

// Restore the cursor to the previously saved position
void restoreCursorPosition() {
	uartTransmit("\033[u");
}
//
//void SysTick_Handler(void) {
//	totalTime++;
//}
//// Function to initialize SysTick timer
//void SysTick_Init(void) {
//	SysTick_Config(SystemCoreClock);
//}



// Calculate the padding needed to align the status string in the display
int calculatePadding(const char* status) {
    int lineWidth = 33;
    int baseTextLength = 10;        // "| Status: " is 10 characters long
    int statusLength = strlen(status);
    int padding = lineWidth - (baseTextLength + statusLength + 2);

    return padding;
}

// Draw the floor layout and highlight the current floor
void drawFloors(int currentFloor) {
	uartTransmit("\033[1;1H");
	for (int i = 1; i<=3; i++){
		if (i == currentFloor){
			uartTransmit(RED_TEXT "+-----------+\r\n" RESET_TEXT);
			uartTransmit(RED_TEXT "|    " RESET_TEXT);
			char floorNum[2];
			sprintf(floorNum, "%d", i);
			uartTransmit(floorNum);
			uartTransmit(RED_TEXT "      |\r\n" RESET_TEXT);
			uartTransmit(RED_TEXT "+-----------+\r\n" RESET_TEXT);
		}
		else{
			uartTransmit(GREEN_TEXT "+-----------+\r\n" RESET_TEXT);
			uartTransmit(GREEN_TEXT "|    " RESET_TEXT);
			char floorNum[2];
			sprintf(floorNum, "%d", i);
			uartTransmit(floorNum);
			uartTransmit(GREEN_TEXT "      |\r\n" RESET_TEXT);
			uartTransmit(GREEN_TEXT "+-----------+\r\n" RESET_TEXT);
		}
	}
}

// Display available commands and instructions for the user
void displayInstructions(void) {
	uartTransmit("\033[10;H");
	uartTransmit("\n+--------------------------------------------------------------------------+\r\n");
	uartTransmit("| To select 1st floor ~ TYPE: '1'                                          |\r\n");
	uartTransmit("| To select 2nd floor ~ TYPE: '2'                                          |\r\n");
	uartTransmit("| To select 3rd floor ~ TYPE: '3'                                          |\r\n");
	uartTransmit("| To open door ~ TYPE: 'open'                                              |\r\n");
	uartTransmit("| To close door ~ TYPE: 'close'                                            |\r\n");
	uartTransmit("| For emergency stop ~ Press: 'User Button PC13'. To continue press again! |\r\n");
	uartTransmit("| For maintenance ~ TYPE: 'M'.                                             |\r\n");
	uartTransmit("| To resume ~ TYPE: 'R'.                                                   |\r\n");
	uartTransmit("+--------------------------------------------------------------------------+\r\n");
}

// Display the current status of the elevator (time elapsed, floor, status)
void displayStatus(int currentFloor, const char* status) {
	char buffer[50];

	uartTransmit("\033[1;30H");
	uartTransmit("+------------------------------+\r\n");
	uartTransmit("\033[2;30H");
	uartTransmit("|         Elevator Status      |\r\n");
	uartTransmit("\033[3;30H");
	sprintf(buffer, "| Time Elapsed: %d seconds      |\r\n", 0);
	uartTransmit(buffer);
	uartTransmit("\033[4;30H");
	sprintf(buffer, "| Floor: %d                     |\r\n", currentFloor);
	uartTransmit(buffer);
	uartTransmit("\033[5;30H");

	int padding = calculatePadding(status);

	sprintf(buffer, "| Status: %s%*s|\r\n", status, padding, "");
	uartTransmit(buffer);
	uartTransmit("\033[6;30H");
	uartTransmit("+------------------------------+\r\n");
}

// Set up the initial status window (clear screen, draw initial floor, display status)
void setupStatusWindow(void) {
	clearScreen();
	drawFloors(FLOOR_1);
    displayStatus(FLOOR_1, "Idle");
    displayInstructions();
    saveCursorPosition();
}

// Set up the scrollable region and prompt the user for input
void setupScrollRegion(void) {
	uartTransmit("\x1b[21;36r");
    uartTransmit("\033[21;1H");	// Move cursor to the start of the scrollable region
    CLI_Prompt();
}

// Initialize the CLI system
void CLI_Init(void) {
	setupStatusWindow();
	setupScrollRegion();
	uartReceive(RXBuffer, 1);
}

// Display the command prompt for the user
void CLI_Prompt(void) {
	char prompt[] = "\r\n>> ";
	uartTransmit(prompt);
}

