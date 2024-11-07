/*
* Name: Tirth V Patel
* SID: 200435378
* FileName: sin_lookup_table.cpp
* Purpose: Initialize and access a sine lookup table for efficient sine calculations.
*/



# include "sin_lookup_table.h"
#include <cmath>
#include <cstdio>

int32_t sine_table[TABLE_SIZE];

void sin_table_init() {
    for (int i =0; i<TABLE_SIZE;i++){
        double angle = (i * RESOLUTION) - DEGREE_RANGE;
        sine_table[i] = static_cast<double>(sin(angle* M_PI / 180.0) * SCALE_FACTOR);
    }
} 

double getSineValue( double angle){
int index = static_cast<int>(std::round((angle + DEGREE_RANGE) / RESOLUTION));
    return sine_table[index] / SCALE_FACTOR;
}