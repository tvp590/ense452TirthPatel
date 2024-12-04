/******************************************************************************
 * File Name: external_control.c
 * Author: Tirth V Patel
 * Student ID: 200435378
 * Date: November 23, 2024
 *
 * Description:
 * Source file for handling external control of the elevator system. It includes
 * functions for controlling the elevator's button inputs and 7-segment display.
 *****************************************************************************/


#include "external_control.h"

// Function to clear the 7-segment display (reset all segments to off)
void clearDisplay(void)
{
	// Set all segments of the 7-segment display to off (GPIO_PIN_RESET)
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
    	case 0: // "0" for Maintenance Mode
            HAL_GPIO_WritePin(SEG_A_PORT, SEG_A_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(SEG_B_PORT, SEG_B_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(SEG_C_PORT, SEG_C_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(SEG_D_PORT, SEG_D_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(SEG_E_PORT, SEG_E_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(SEG_F_PORT, SEG_F_PIN, GPIO_PIN_SET);
            break;

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

		case 4: // "4" for Emergency Stop
			HAL_GPIO_WritePin(SEG_A_PORT, SEG_A_PIN, GPIO_PIN_SET); // Segment A
			HAL_GPIO_WritePin(SEG_F_PORT, SEG_F_PIN, GPIO_PIN_SET); // Segment F
			HAL_GPIO_WritePin(SEG_E_PORT, SEG_E_PIN, GPIO_PIN_SET); // Segment E
			HAL_GPIO_WritePin(SEG_D_PORT, SEG_D_PIN, GPIO_PIN_SET); // Segment D
			HAL_GPIO_WritePin(SEG_G_PORT, SEG_G_PIN, GPIO_PIN_SET); // Segment G
			break;

    	default:
    		clearDisplay();
        break;
    }
}

// Function to initialize the external control system
void ExternalControl_Init(void)
{
    clearDisplay();
    displayNumber(1);
}
