/*
 * timer.h
 *
 *  Created on: Nov 3, 2024
 *      Author: tirthpatel
 */

#ifndef TIMER_H
#define TIMER_H


#include "stdint.h"

void timer_init(void);
int16_t timer_start(void);
int16_t timer_stop(int16_t start_time);



#endif /* TIMER_H */
