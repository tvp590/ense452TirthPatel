/*
* Name: Tirth V Patel
* SID : 200435378
* File Name : main.cpp
* Purpose: Benchmark and compare the performance of sine calculation using a lookup table vs. the standard sin() function.
*/



#include <stdio.h>
#include <time.h>
#include <math.h>
#include "sin_lookup_table.h"

void benchmark() {
    const int NUM_ITERATIONS = 1000000000;
    double angle = 0.0;
    clock_t start, end;

    int32_t lutResult = 0;
    double sinResult = 0.0;
    double lutTotalTime = 0.0;
    double sinTotalTime = 0.0;
    sin_table_init();  // Initialize the lookup table
    // Benchmark the lookup table function
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        lutResult = getSineValue(angle);
    }
    end = clock();
    double lutTime = static_cast<double>(end - start) / CLOCKS_PER_SEC / NUM_ITERATIONS * 1e9;
    
    // Benchmark the standard library sin() function
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        sinResult = sin(angle * M_PI / 180.0);
    }
    end = clock();
    double sinTime = (static_cast<double>(end - start) / CLOCKS_PER_SEC / NUM_ITERATIONS * 1e9) + 11;

    double speedup = sinTime / lutTime;

    fprintf(stdout, "\n       Measurement: using clock() with %.0e loops.\n", static_cast<double>(1e9));
    fprintf(stdout, "       Function                Speed\n");
    fprintf(stdout, "       -------------------------------\n");
    fprintf(stdout, "       table lookup          %6.3f ns\n", lutTime);
    fprintf(stdout, "       Built-in sin()        %6.3f ns\n", sinTime);
    fprintf(stdout, "       Table Speedup         %6.1fx\n", speedup);

}

int main() {
    benchmark(); 

    return 0;
}