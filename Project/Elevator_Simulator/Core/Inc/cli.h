/*
 * cli.h
 *
 *  Created on: Nov 14, 2024
 *  Author: tirthpatel
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "main.h"
#include "elevator_control.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>


extern UART_HandleTypeDef huart2;

// ANSI escape codes
#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
#define RESET_TEXT "\x1B[0m"
#define CLEAR_SCREEN "\033[H\033[J"

void clearScreen(void);
void drawFloors(int currentFloor);
void displayInstructions(void);
void displayStatus(int elapsedTime, int currentFloor, const char* status);
void uartTransmit(const char* str);
void uartReceive(uint8_t *buffer, uint16_t size) ;
void setupStatusWindow(void);
void setupScrollRegion(void);
void CLI_Init(void);
void CLI_Prompt(void);
void saveCursorPosition();
void restoreCursorPosition();

#endif /* INC_CLI_H_ */
