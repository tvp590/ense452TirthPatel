/*
 * cli.c
 *
 *  Created on: Nov 14, 2024
 *      Author: tirthpatel
 */



#include "cli.h"

extern uint8_t RXBuffer[1];

void uartTransmit(const char* str) {
	 HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str),1000);
}

void uartReceive(uint8_t *buffer, uint16_t size) {
    HAL_UART_Receive_IT(&huart2, buffer, size);
}

void clearScreen(void) {
    uartTransmit(CLEAR_SCREEN);
}

void saveCursorPosition() {
	uartTransmit("\033[s");
}

void restoreCursorPosition() {
	uartTransmit("\033[u");
}

// Utility function to format the status line with dynamic padding
int calculatePadding(const char* status) {
    int lineWidth = 33;
    int baseTextLength = 10;        // "| Status: " is 10 characters long
    int statusLength = strlen(status);
    int padding = lineWidth - (baseTextLength + statusLength + 2);

    return padding;
}

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

void displayStatus(int elapsedTime, int currentFloor, const char* status) {
	char buffer[50];

	uartTransmit("\033[1;30H");
	uartTransmit("+------------------------------+\r\n");
	uartTransmit("\033[2;30H");
	uartTransmit("|         Elevator Status      |\r\n");
	uartTransmit("\033[3;30H");
	sprintf(buffer, "| Time Elapsed: %d seconds      |\r\n", elapsedTime);
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

void setupStatusWindow(void) {
	int elapsedTime = 0;
	clearScreen();
	drawFloors(FLOOR_1);
    displayStatus(elapsedTime, FLOOR_1, "Idle");
    displayInstructions();
    saveCursorPosition();
}

void setupScrollRegion(void) {
	uartTransmit("\x1b[21;36r");
    uartTransmit("\033[21;1H");	// Move cursor to the start of the scrollable region
    CLI_Prompt();
}


void CLI_Init(void) {
	setupStatusWindow();
	setupScrollRegion();
	uartReceive(RXBuffer, 1);
}

void CLI_Prompt(void) {
	char prompt[] = "\r\n>> ";
	uartTransmit(prompt);
}

