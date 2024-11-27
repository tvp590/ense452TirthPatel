/******************************************************************************
 * File Name: elevator_control.h
 * Author: Tirth V Patel
 * Student ID: 200435378
 * Date: November 14, 2024
 *
 * Description:
 * Header file for the elevator control system. It provides function prototypes
 * and necessary definitions for managing elevator operations such as floor
 * movement, door control, emergency stops, and maintenance mode.
 ******************************************************************************/


#ifndef INC_ELEVATOR_CONTROL_H_
#define INC_ELEVATOR_CONTROL_H_

#include "cli.h"
#include <stdint.h>

// ** Constants for Floors **
#define FLOOR_1 1
#define FLOOR_2 2
#define FLOOR_3 3

// ** Elevator States **
typedef enum {
    ELEVATOR_IDLE,
    ELEVATOR_MOVING_UP,
	ELEVATOR_MOVING_DOWN,
    ELEVATOR_DOORS_OPEN,
    ELEVATOR_DOORS_CLOSED,
	ELEVATOR_MAINTENANCE_MODE,
	ELEVATOR_EMERGENCY_STOP
} ElevatorState;

// ** Global Variables **
extern volatile int currentFloor;
extern ElevatorState elevatorState;

// ** Function Prototypes **
/**
 * @brief Check if the elevator is on the target floor.
 * @param targetFloor Target floor to check.
 * @return 1 if on the same floor, 0 otherwise.
 */
int isElevatorOnSameFloor(int targetFloor);

/**
 * @brief Check if the specified floor is valid.
 * @param floor Floor number to validate.
 * @return 1 if valid, 0 otherwise.
 */
int isValidFloor(int floor);

/**
 * @brief Open the elevator doors and update the state.
 */
void openDoor(void);

/**
 * @brief Close the elevator doors and update the state.
 */
void closeDoor(void);

/**
 * @brief Perform an emergency stop and update the state.
 */
void emergencyStopOperations(void);

/**
 * @brief Resume elevator operations after an emergency stop or maintenance.
 */
void resumeElevatorOperations(void);

/**
 * @brief Activate maintenance mode and update the state.
 */
void maintenanceMode(void);

/**
 * @brief Move the elevator to the specified target floor.
 * @param targetFloor The floor to move to.
 */
void moveElevatorToFloor(int targetFloor);

/**
 * @brief Get the string representation of the current elevator state.
 * @param state Elevator state.
 * @return Pointer to a string representing the state.
 */
const char* getElevatorStateString(ElevatorState state);

/**
 * @brief Activate door opening sequence with delay.
 */
void activateDoorOpening(void);

/**
 * @brief Activate door closing sequence with delay.
 */
void activateDoorClosing(void);


#endif /* INC_ELEVATOR_CONTROL_H_ */
