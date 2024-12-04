/******************************************************************************
 * File Name: external_control.h
 * Author: Tirth V Patel
 * Student ID: 200435378
 * Date: November 23, 2024
 *
 * Description:
 * Header file for controlling external hardware components of the elevator
 * system. It provides function prototypes and definitions for managing button
 * states, clearing the 7-segment display, and displaying numbers on it.
 * Includes initialization for external controls.
 ******************************************************************************/


#ifndef EXTERNAL_CONTROL_H_
#define EXTERNAL_CONTROL_H_

#include "main.h"

// ** Segment pins for the 7-segment display **
#define SEG_A_PIN GPIO_PIN_10
#define SEG_A_PORT GPIOA

#define SEG_B_PIN GPIO_PIN_6
#define SEG_B_PORT GPIOB

#define SEG_C_PIN GPIO_PIN_9
#define SEG_C_PORT GPIOA

#define SEG_D_PIN GPIO_PIN_4
#define SEG_D_PORT GPIOB

#define SEG_E_PIN GPIO_PIN_10
#define SEG_E_PORT GPIOB

#define SEG_F_PIN GPIO_PIN_5
#define SEG_F_PORT GPIOB

#define SEG_G_PIN GPIO_PIN_8
#define SEG_G_PORT GPIOA

// **  Pins for the buttons **
#define BUTTON_1_PIN GPIO_PIN_0
#define BUTTON_1_PORT GPIOA

#define BUTTON_2_PIN GPIO_PIN_1
#define BUTTON_2_PORT GPIOA

#define BUTTON_3_PIN GPIO_PIN_4
#define BUTTON_3_PORT GPIOA

#define BUTTON_4_PIN GPIO_PIN_0
#define BUTTON_4_PORT GPIOB

// ** Function Prototypes **

/**
 * @brief Clears the 7-segment display.
 *
 * Resets all segments of the 7-segment display to an off state.
 */
void clearDisplay(void);

/**
 * @brief Displays a number on the 7-segment display.
 *
 * Lights up the appropriate segments on the display to show the given number.
 * Supports numbers 1, 2, and 3.
 *
 * @param num The number to display (valid values: 1, 2, or 3).
 */
void displayNumber(uint8_t num);

/**
 * @brief Initializes the external control hardware.
 *
 * Clears the button pins and resets the 7-segment display.
 * Sets the default display number to 1.
 */
void ExternalControl_Init(void);

#endif /* EXTERNAL_CONTROL_H_ */
