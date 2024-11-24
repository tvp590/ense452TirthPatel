/*
 * elevator_control.h
 *
 *  Created on: Nov 14, 2024
 *      Author: tirthpatel
 */

#ifndef INC_ELEVATOR_CONTROL_H_
#define INC_ELEVATOR_CONTROL_H_

#include "cli.h"

#define FLOOR_1 1
#define FLOOR_2 2
#define FLOOR_3 3

// Elevator states
typedef enum {
    ELEVATOR_IDLE,
    ELEVATOR_MOVING_UP,
	ELEVATOR_MOVING_DOWN,
    ELEVATOR_DOORS_OPEN,
    ELEVATOR_DOORS_CLOSED,
	ELEVATOR_MAINTENANCE_MODE,
	ELEVATOR_EMERGENCY_STOP
} ElevatorState;

extern volatile int currentFloor;
extern ElevatorState elevatorState;

// Elevator movement functions
void moveElevatorToFloor(int targetFloor);

// Door control functions
void openDoor(void);
void closeDoor(void);
void activateDoorOpening(void);
void activateDoorClosing(void);

// Elevator operations
void emergencyStopOperations(void);
void resumeElevatorOperations(void);
void maintenanceMode(void);

// Helper functions
int isElevatorOnSameFloor(int targetFloor);
int isValidFloor(int floor);
const char* getElevatorStateString(ElevatorState state);


// Utility functions for floor checks
int isElevatorOnSameFloor(int targetFloor);
int isValidFloor(int floor);


#endif /* INC_ELEVATOR_CONTROL_H_ */
