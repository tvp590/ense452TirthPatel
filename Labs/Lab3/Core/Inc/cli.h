/*
    Name : Tirth V Patel
    SID  : 200435378
    File : cli.h
    Description : This file contains the declaration of the CLI module.
*/

#ifndef __CLI_H
#define __CLI_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"

void CLI_Init(void);
void CLI_ExecuteCommand(int command);
void CLI_PrintPrompt(void);
void CLI_PrintHelp(void);
void CLI_TurnOnLED(void);
void CLI_TurnOffLED(void);
void CLI_QueryLEDState(void);
void transmitData(const char *data);
void setupScreen();
void updateStatusWindow();

#endif
