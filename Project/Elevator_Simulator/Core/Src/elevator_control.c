/*
 * elevator_control.c
 *
 *  Created on: Nov 14, 2024
 *      Author: tirthpatel
 */


#include "elevator_control.h"
#include "external_control.h"
#include "string.h"

volatile int currentFloor = FLOOR_1;
ElevatorState elevatorState = ELEVATOR_IDLE;


int isElevatorOnSameFloor(int targetFloor) {
    return currentFloor == targetFloor;
}

int isValidFloor(int floor) {
    return (floor == FLOOR_1 || floor == FLOOR_2 || floor == FLOOR_3);
}


// Function to open the elevator door
void openDoor(void) {
    elevatorState = ELEVATOR_DOORS_OPEN;
    displayStatus(0, currentFloor, getElevatorStateString(elevatorState));
}

void activateDoorOpening(void){
	if (elevatorState == ELEVATOR_IDLE) {
		saveCursorPosition();
		openDoor();
		osDelay(1800);
		restoreCursorPosition();
	}

}
// Function to close the elevator door
void closeDoor(void) {
    elevatorState = ELEVATOR_DOORS_CLOSED;
    displayStatus(0, currentFloor, getElevatorStateString(elevatorState));
}


void activateDoorClosing(void){
	if (elevatorState == ELEVATOR_DOORS_OPEN){
		saveCursorPosition();
		closeDoor();
		osDelay(1800);
		resumeElevatorOperations();
		restoreCursorPosition();
	}
}

// Function to perform an emergency stop
void emergencyStopOperations(void) {
    elevatorState = ELEVATOR_EMERGENCY_STOP;
    displayStatus( 0, currentFloor, getElevatorStateString(elevatorState));
}

void resumeElevatorOperations(void){
	elevatorState =  ELEVATOR_IDLE;
	displayStatus( 0, currentFloor, getElevatorStateString(elevatorState));
}

// Function to perform maintenance mode
void maintenanceMode(void) {
	elevatorState = ELEVATOR_MAINTENANCE_MODE;
	displayStatus( 0, currentFloor, getElevatorStateString(elevatorState));
}

const char* getElevatorStateString(ElevatorState state) {
	switch (state) {
	    case ELEVATOR_IDLE:         return "Idle";
	    case ELEVATOR_MOVING_UP:    return "Moving Up";
	    case ELEVATOR_MOVING_DOWN:  return "Moving Down";
	    case ELEVATOR_DOORS_OPEN:   return "Doors Open";
	    case ELEVATOR_DOORS_CLOSED: return "Doors Closed";
	    case ELEVATOR_MAINTENANCE_MODE:  return "Maintenance";
	    case ELEVATOR_EMERGENCY_STOP:    return "Emergency Stop";
	    default:                    return "Unknown State";
	}
}

void moveElevatorToFloor(int targetFloor) {
	if (!isValidFloor(targetFloor)) {
	   uartTransmit(" Invalid floor entered. Please enter a valid floor (1, 2, or 3).");
	   return;
	}

	if (elevatorState == ELEVATOR_EMERGENCY_STOP){
		uartTransmit(" Emergency stop activated.");
		return;
	}

	if (elevatorState == ELEVATOR_MAINTENANCE_MODE){
		uartTransmit(" Maintenance mode activated.");
		return;
	}

	// Save the cursor position at the start
	saveCursorPosition();

	if (isElevatorOnSameFloor(targetFloor)) {
		openDoor();
		osDelay(1800);
		closeDoor();
		osDelay(1800);
		displayStatus( 0, currentFloor, getElevatorStateString(ELEVATOR_IDLE));
		displayNumber(currentFloor);
	}
	else {
		while (currentFloor != targetFloor){
			__disable_irq();  // Disable all interrupts
			if (currentFloor < targetFloor) {
				currentFloor++;
				elevatorState = ELEVATOR_MOVING_UP;
			} 
			else if (currentFloor > targetFloor) {
				currentFloor--;
				elevatorState = ELEVATOR_MOVING_DOWN;
			}

			drawFloors(currentFloor);
			displayNumber(currentFloor);
			displayStatus(0, currentFloor, getElevatorStateString(elevatorState));

			__enable_irq();   // Re-enable interrupts

			osDelay(1800);	// Simulate time taken to move between floors
		}
		drawFloors(currentFloor);
		displayStatus( 0, currentFloor, getElevatorStateString(ELEVATOR_IDLE));
		displayNumber(currentFloor);

		osDelay(1800);
		displayStatus( 0, currentFloor, getElevatorStateString(ELEVATOR_DOORS_OPEN));
		osDelay(1800);
		displayStatus( 0, currentFloor, getElevatorStateString(ELEVATOR_DOORS_CLOSED));
		osDelay(1800);
		elevatorState=ELEVATOR_IDLE;
		displayStatus( 0, currentFloor, getElevatorStateString(elevatorState));
	}
	// Restore the cursor position after updating the floor and status
	restoreCursorPosition();
}
