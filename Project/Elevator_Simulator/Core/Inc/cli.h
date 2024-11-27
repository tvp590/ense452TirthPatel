/******************************************************************************
 * File Name: cli.h
 * Author: Tirth V Patel
 * Student ID: 200435378
 * Date: November 14, 2024
 *
 * Description:
 * Header file for the Command Line Interface (CLI) of the elevator control
 * system, defining function prototypes, and global variables.
 ******************************************************************************/

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "main.h"
#include "elevator_control.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>


extern UART_HandleTypeDef huart2;

// ** ANSI escape codes **
#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
#define RESET_TEXT "\x1B[0m"
#define CLEAR_SCREEN "\033[H\033[J"

// ** Global Variables **
extern UART_HandleTypeDef huart2; // UART handle
extern uint8_t RXBuffer[1];       // Buffer for receiving UART data

// ** Function Prototypes **

/**
 * @brief Transmits a string over UART.
 * @param str: Pointer to the null-terminated string to transmit.
 */
void uartTransmit(const char* str);

/**
 * @brief Initializes UART receive in interrupt mode.
 * @param buffer: Pointer to the buffer where received data will be stored.
 * @param size: Size of the receive buffer.
 */
void uartReceive(uint8_t *buffer, uint16_t size);

/**
 * @brief Clears the terminal screen using an ANSI escape sequence.
 */
void clearScreen(void);

/**
 * @brief Saves the current cursor position on the terminal.
 */
void saveCursorPosition(void);

/**
 * @brief Restores the cursor position to the previously saved location.
 */
void restoreCursorPosition(void);

/**
 * @brief Draws the elevator floors in the terminal.
 *        Highlights the current floor in red, and other floors in green.
 * @param currentFloor: The current floor where the elevator is located.
 */
void drawFloors(int currentFloor);

/**
 * @brief Displays CLI usage instructions on the terminal.
 */
void displayInstructions(void);

/**
 * @brief Updates and displays the elevator status window in the CLI.
 * @param currentFloor: The current floor where the elevator is located.
 * @param status: A string representing the current elevator status.
 */
void displayStatus(int currentFloor, const char* status);

/**
 * @brief Sets up the initial CLI display, including the status window and instructions.
 */
void setupStatusWindow(void);

/**
 * @brief Configures a scrollable region on the terminal for dynamic updates.
 */
void setupScrollRegion(void);

/**
 * @brief Initializes the CLI interface.
 *        Clears the screen, sets up the initial display, and starts UART receive in interrupt mode.
 */
void CLI_Init(void);

/**
 * @brief Displays the command prompt in the CLI.
 */
void CLI_Prompt(void);

/**
 * @brief Calculates the padding required for centering the status text.
 * @param status: A string representing the elevator status.
 * @return The calculated padding as an integer.
 */
int calculatePadding(const char* status);

#endif /* INC_CLI_H_ */
