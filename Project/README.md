# Elevator Control System

This project implements an elevator control system using a combination of hardware peripherals and software tasks. The system is designed to control the movement of an elevator, manage emergency stops, and handle user inputs via buttons and UART commands. It also includes a 7-segment display for showing floor information and other statuses.

## Overview

The elevator control system integrates with external hardware components such as buttons, a 7-segment display, and GPIO pins for managing elevator movement, emergency stops, and floor displays. It uses FreeRTOS for multitasking, allowing different functionalities to run concurrently.

#### Key features include:

- Emergency stop mechanism via GPIO interrupt.
- UART communication for receiving and sending elevator control commands.
- User interface with buttons for floor selection and a 7-segment display for floor indications. This hardware interface mimics the buttons on each floor and the display in an elevator system.
- CLI support for remotely controlling the elevator. This CLI interface simulates the operation inside the elevator.

## Hardware Setup

The following components are used in the hardware setup:
- **GPIO Pins:**
    - **7-segment display pins** connected to the following GPIO pins on the microcontroller:
        - `SEG_A_PIN` (GPIO_PIN_10, GPIOA)
        - `SEG_B_PIN` (GPIO_PIN_6, GPIOB)
        - `SEG_C_PIN` (GPIO_PIN_9, GPIOA)
        - `SEG_D_PIN` (GPIO_PIN_4, GPIOB)
        - `SEG_E_PIN` (GPIO_PIN_10, GPIOB)
        - `SEG_F_PIN` (GPIO_PIN_5, GPIOB)
        - `SEG_G_PIN` (GPIO_PIN_8, GPIOA)
    
    - **Button pins** for user input:
      - `BUTTON_1_PIN` (GPIO_PIN_0, GPIOA)
      - `BUTTON_2_PIN` (GPIO_PIN_1, GPIOA)
      - `BUTTON_3_PIN` (GPIO_PIN_4, GPIOA)
      - `BUTTON_4_PIN` (GPIO_PIN_0, GPIOB)
  
- **External Interrupt:** GPIO pin PC13 is used for the emergency stop, triggering an interrupt to stop elevator operations.

## Software Design

The software is structured around multiple tasks that communicate via queues and interrupts. The system is built with FreeRTOS for real-time multitasking.

### Tasks
- **Emergency Stop Task**: This task handles emergency stop actions when triggered by an interrupt. If the emergency stop button is pressed, the elevator halts, and the current position is saved.
- **Elevator Control Task**: Responsible for managing elevator movement based on user input 
- **CLI Receive Task**: Handles UART commands and sends them to the Elevator Control Task queue upon the ENTER key press.
- **Button Check Task**: Monitors button inputs for floor selection. When a button is pressed, the elevator moves to the corresponding floor.

## Installation and Usage
To install and use the Elevator Control System:

1. Clone the repository to your local machine.
2.  Set up the `STM32F103RB` microcontroller and connect the hardware components (7-segment display, buttons, UART, etc.).
3. Build the project using the appropriate IDE and toolchain for your STM32F103RB microcontroller (e.g., `STM32CubeIDE` or `KEIL`).
4. Flash the firmware to the microcontroller using a programmer like ST-Link.
5. Use a terminal application (e.g., **CMD** on Windows or **Terminal** on macOS/Linux) to send commands via UART or interact with the elevator system using the physical buttons.

