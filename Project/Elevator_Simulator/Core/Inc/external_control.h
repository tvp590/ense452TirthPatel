/*
 * external_control.h
 *
 *  Created on: Nov 23, 2024
 *      Author: tirthpatel
 */

#ifndef EXTERNAL_CONTROL_H_
#define EXTERNAL_CONTROL_H_

#include "main.h"

// Define the pins for the 7-segment display
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

// Define the pins for the buttons
#define BUTTON_1_PIN GPIO_PIN_0
#define BUTTON_1_PORT GPIOA

#define BUTTON_2_PIN GPIO_PIN_1
#define BUTTON_2_PORT GPIOA

#define BUTTON_3_PIN GPIO_PIN_4
#define BUTTON_3_PORT GPIOA

#define BUTTON_4_PIN GPIO_PIN_0
#define BUTTON_4_PORT GPIOB

// Function Prototypes
void clearButtonPins(void);  // Function to clear/reset button pins
void clearDisplay(void);     // Function to clear the 7-segment display
void displayNumber(uint8_t num); // Function to display a number (1-3) on the 7-segment display
void ExternalControl_Init(void); // Initialization function

#endif /* EXTERNAL_CONTROL_H_ */
