/*
 * measurements.c
 *
 *  Created on: Nov 3, 2024
 *      Author: tirthpatel
 */


#include "measurements.h"
#include <stdlib.h>
#include <stdio.h>

#define TRIALS 100

typedef struct {
    int data[2];
} SmallStruct;	// 8 bytes (assuming int is 4 bytes)

typedef struct {
    int data[32];
} MediumStruct;  // 128 bytes

typedef struct {
    int data[256];
} LargeStruct;  // 1024 bytes

void initialize_struct(void* s, size_t size) {
    for (size_t i = 0; i < size / sizeof(int); i++) {
        ((int*)s)[i] = rand();
    }
}

// Measure 32-bit addition
void measure_add_32() {
	int32_t result;
	volatile int16_t elapsed_total = 0;
	volatile int16_t start, elapsed;
	volatile int32_t a,b;
	 for (int i = 0; i < TRIALS; i++) {
		 a = rand();
		 b = rand();
		 start = timer_start();
		 result = a + b;
		 elapsed = timer_stop(start);
		 elapsed_total += elapsed;
	 }
	 CLI_TransmitResult("Average time for 32-bit addition", elapsed_total / TRIALS);
}

// Measure 64-bit addition
void measure_add_64() {
    int64_t result;
    volatile int16_t elapsed_total = 0;
    volatile int16_t start, elapsed;
    volatile int64_t a,b;
    for (int i = 0; i < TRIALS; i++) {
        a = ((int64_t)rand() << 32) | rand(); // Generate random 64-bit value because rand() can only generate 2^31 -1
        b = ((int64_t)rand() << 32) | rand();
        start = timer_start();
        result = a + b;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Average time for 64-bit addition", elapsed_total / TRIALS);
}

// Measure 32-bit multiplication
void measure_multiply_32() {
    int32_t result;
    volatile int16_t elapsed_total = 0;
    volatile int16_t start, elapsed;
    volatile int32_t a,b;
    for (int i = 0; i < TRIALS; i++) {
        a = rand();
        b = rand();
        start = timer_start();
        result = a * b;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Average time for 32-bit multiplication", elapsed_total / TRIALS);
}

// Measure 64-bit multiplication
void measure_multiply_64() {
    int64_t result;
    volatile int16_t elapsed_total = 0;
    volatile int16_t start, elapsed;
    volatile int64_t a,b;
    for (int i = 0; i < TRIALS; i++) {
        a = ((int64_t)rand() << 32) | rand();
        b = ((int64_t)rand() << 32) | rand();
        start = timer_start();
        result = a * b;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Average time for 64-bit multiplication", elapsed_total / TRIALS);
}

// Measure 32-bit division
void measure_divide_32() {
    int32_t result;
    volatile int16_t elapsed_total = 0;
    volatile int16_t start, elapsed;
    volatile int32_t a, b;

    for (int i = 0; i < TRIALS; i++) {
        a = rand();
        b = rand();
        start = timer_start();
        result = (b != 0) ? (a / b) : 0;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Average time for 32-bit division", elapsed_total / TRIALS);
}



// Measure 64-bit division
void measure_divide_64() {
    int64_t result;
    volatile int16_t elapsed_total = 0;
    volatile int16_t start, elapsed;
    volatile int64_t a, b;

    for (int i = 0; i < TRIALS; i++) {
        a = ((int64_t)rand() << 32) | rand();
        b = ((int64_t)rand() << 32) | rand();
        start = timer_start();
        result = (b != 0) ? (a / b) : 0;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Average time for 64-bit division", elapsed_total / TRIALS);
}

// Measure time for copying 8 byte structs
void measure_copy_8() {
    SmallStruct* src = (SmallStruct*)malloc(sizeof(SmallStruct));
    SmallStruct* dest = (SmallStruct*)malloc(sizeof(SmallStruct));
    volatile int16_t elapsed_total = 0;
    volatile int16_t start, elapsed;

    for (int i = 0; i < TRIALS; i++) {
    	initialize_struct(src, sizeof(SmallStruct));

        start = timer_start();
        *dest = *src;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Average time for 8-byte struct copy", elapsed_total / TRIALS);

    free(src);
    free(dest);
}

// Measure time for copying 128-byte structs
void measure_copy_128() {
    MediumStruct* src = (MediumStruct*)malloc(sizeof(MediumStruct));
    MediumStruct* dest = (MediumStruct*)malloc(sizeof(MediumStruct));
    volatile int32_t elapsed_total = 0;
    volatile int16_t start, elapsed;

    for (int i = 0; i < TRIALS; i++) {
        initialize_struct(src, sizeof(MediumStruct));

        start = timer_start();
        *dest = *src;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Size:", sizeof(MediumStruct));
    CLI_TransmitResult("Average time for 128-byte struct copy", elapsed_total/TRIALS);

    free(src);
    free(dest);
}

// Measure time for copying 1024 byte structs
void measure_copy_1024() {
    LargeStruct* src = (LargeStruct*)malloc(sizeof(LargeStruct));
    LargeStruct* dest = (LargeStruct*)malloc(sizeof(LargeStruct));
    volatile int16_t elapsed_total = 0;
    volatile int16_t start, elapsed;

    for (int i = 0; i < TRIALS; i++) {
        initialize_struct(src, sizeof(LargeStruct));

        start = timer_start();
        *dest = *src;
        elapsed = timer_stop(start);
        elapsed_total += elapsed;
    }
    CLI_TransmitResult("Average time for 1024-byte struct copy", elapsed_total / TRIALS);

    free(src);
    free(dest);
}

void run_measurements() {

	 measure_add_32();
	 measure_add_64();
	 measure_multiply_32();
	 measure_multiply_64();
	 measure_divide_32();
	 measure_divide_64();
	 measure_copy_8();
	 measure_copy_128();
	 measure_copy_1024();
}
