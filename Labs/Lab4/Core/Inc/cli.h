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
void CLI_Transmit(const char* message);
void CLI_TransmitResult(const char* description, uint32_t result);

#endif
