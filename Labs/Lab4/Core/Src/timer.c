/*
 * timer.c
 *
 *  Created on: Nov 3, 2024
 *      Author: tirthpatel
 */


#include "timer.h"
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim4;

void timer_init(void) {
	HAL_TIM_Base_Start(&htim4);
}

int16_t timer_start(void) {
	volatile int16_t timer_value = (int16_t) __HAL_TIM_GET_COUNTER(&htim4);
	return timer_value;
}

int16_t timer_stop(int16_t start_time) {
	volatile int16_t current_time = (int16_t) __HAL_TIM_GET_COUNTER(&htim4);

	if (current_time >= start_time) {
		return (int16_t)(current_time - start_time);
	}
	else{
		return (int16_t)((0xFFFF - start_time) + current_time + 1); //Wraparound case
	}
}
