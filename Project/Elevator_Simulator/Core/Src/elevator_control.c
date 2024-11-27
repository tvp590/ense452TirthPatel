/******************************************************************************
 * File Name: elevator_control.c
 * Author: Tirth V Patel
 * Student ID: 200435378
 * Date: November 14, 2024
 *
 * Description:
 * Source file for the elevator control system. It contains functions to
 * manage elevator operations such as floor movement, door control, emergency
 * stops, and maintenance mode.
 *****************************************************************************/

#include "elevator_control.h"
#include "external_control.h"
#include "string.h"

volatile int currentFloor = FLOOR_1;
ElevatorState elevatorState = ELEVATOR_IDLE;

// Function to check if the elevator is already on the target floor
int isElevatorOnSameFloor(int targetFloor) {
    return currentFloor == targetFloor;
}

// Function to check if the floor is valid (1, 2, or 3)
int isValidFloor(int floor) {
    return (floor == FLOOR_1 || floor == FLOOR_2 || floor == FLOOR_3);
}


// Function to open the elevator door and update the elevator state
void openDoor(void) {
    elevatorState = ELEVATOR_DOORS_OPEN;
    displayStatus(currentFloor, getElevatorStateString(elevatorState));
}

// Function to activate the door opening process when the elevator is idle
void activateDoorOpening(void){
	if (elevatorState == ELEVATOR_IDLE) {
		saveCursorPosition();
		openDoor();
		osDelay(1800);
		restoreCursorPosition();
	}
}

// Function to close the elevator door and update the elevator state
void closeDoor(void) {
    elevatorState = ELEVATOR_DOORS_CLOSED;
    displayStatus(currentFloor, getElevatorStateString(elevatorState));
}

// Function to activate the door closing process when the door is open
void activateDoorClosing(void){
	if (elevatorState == ELEVATOR_DOORS_OPEN){
		saveCursorPosition();
		closeDoor();
		osDelay(1800);
		resumeElevatorOperations();
		restoreCursorPosition();
	}
}

// Function to perform an emergency stop and update the elevator state
void emergencyStopOperations(void) {
    elevatorState = ELEVATOR_EMERGENCY_STOP;
    displayStatus(currentFloor, getElevatorStateString(elevatorState));
}

// Function to resume elevator operations after an emergency stop or maintenance mode
void resumeElevatorOperations(void){
	elevatorState =  ELEVATOR_IDLE;
	displayStatus(currentFloor, getElevatorStateString(elevatorState));
}

// Function to activate maintenance mode and update the elevator state
void maintenanceMode(void) {
	elevatorState = ELEVATOR_MAINTENANCE_MODE;
	displayStatus(currentFloor, getElevatorStateString(elevatorState));
}

// Function to convert elevator state to string for display
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

// Function to move the elevator to a target floor, handling various states
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

	if (elevatorState == ELEVATOR_DOORS_OPEN){
		uartTransmit(" Close the door");
		return;
	}

	// Save the cursor position at the start
	saveCursorPosition();

	if (isElevatorOnSameFloor(targetFloor)) {
		openDoor();
		osDelay(1800);
		closeDoor();
		osDelay(1800);
		displayStatus( currentFloor, getElevatorStateString(ELEVATOR_IDLE));
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
			displayStatus(currentFloor, getElevatorStateString(elevatorState));

			__enable_irq();   // Re-enable interrupts

			osDelay(1800);	// Simulate time taken to move between floors
		}
		drawFloors(currentFloor);
		displayStatus(currentFloor, getElevatorStateString(ELEVATOR_IDLE));
		displayNumber(currentFloor);

		osDelay(1800);
		displayStatus(currentFloor, getElevatorStateString(ELEVATOR_DOORS_OPEN));
		osDelay(1800);
		displayStatus(currentFloor, getElevatorStateString(ELEVATOR_DOORS_CLOSED));
		osDelay(1800);
		elevatorState=ELEVATOR_IDLE;
		displayStatus(currentFloor, getElevatorStateString(elevatorState));
	}
	// Restore the cursor position after updating the floor and status
	restoreCursorPosition();
}
