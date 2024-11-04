/*
* Name : Tirth V Patel
* SID : 200435378
* File Name : measurements.h
* Purpose : Declare the functions to measure the time taken for 32-bit and 64-bit addition, multiplication, division and copying of 8, 128 and 1024 byte structs
*/
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include "timer.h"
#include "cli.h"
#include <stdint.h>
#include <stddef.h>

void initialize_struct(void* s, size_t size);
void measure_add_32();
void measure_add_64();
void measure_multiply_32();
void measure_multiply_64();
void measure_divide_32();
void measure_divide_64();
void measure_copy_8();
void measure_copy_128();
void measure_copy_1024();
void run_measurements();


#endif /* MEASUREMENTS_H */
