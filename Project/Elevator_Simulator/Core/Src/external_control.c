/*
 * external_control.c
 *
 *  Created on: Nov 23, 2024
 *      Author: tirthpatel
 */


#include "external_control.h"

// Function to clear the button pins
void clearButtonPins(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); // Button 1
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); // Button 2
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // Button 3
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); // Button 4
}

// Function to clear the 7-segment display (reset all segments to off)
void clearDisplay(void)
{
    HAL_GPIO_WritePin(SEG_A_PORT, SEG_A_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG_B_PORT, SEG_B_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG_C_PORT, SEG_C_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG_D_PORT, SEG_D_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG_E_PORT, SEG_E_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG_F_PORT, SEG_F_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG_G_PORT, SEG_G_PIN, GPIO_PIN_RESET);
}

// Function to display numbers 1, 2, or 3 on the 7-segment display
void displayNumber(uint8_t num)
{
    clearDisplay();

    // Display the number based on the case
    switch (num)
    {
    case 1: // "1"
        HAL_GPIO_WritePin(SEG_B_PORT, SEG_B_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_C_PORT, SEG_C_PIN, GPIO_PIN_SET);
        break;

    case 2: // "2"
        HAL_GPIO_WritePin(SEG_A_PORT, SEG_A_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_B_PORT, SEG_B_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_G_PORT, SEG_G_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_E_PORT, SEG_E_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_D_PORT, SEG_D_PIN, GPIO_PIN_SET);
        break;

    case 3: // "3"
        HAL_GPIO_WritePin(SEG_A_PORT, SEG_A_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_B_PORT, SEG_B_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_G_PORT, SEG_G_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_C_PORT, SEG_C_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEG_D_PORT, SEG_D_PIN, GPIO_PIN_SET);
        break;

    default:
        clearDisplay();
        break;
    }
}

void ExternalControl_Init(void)
{
    clearButtonPins();
    clearDisplay();
}
