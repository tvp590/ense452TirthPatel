/*
* Name : Tirth V Patel
* SID : 200435378
* File Name : timer.h
* Purpose : To define the functions for timer.c
 */

#ifndef TIMER_H
#define TIMER_H


#include "stdint.h"

void timer_init(void);
int16_t timer_start(void);
int16_t timer_stop(int16_t start_time);



#endif /* TIMER_H */
