#ifndef SIN_LOOKUP_TABLE_H
#define SIN_LOOKUP_TABLE_H

#include <stdint.h>

#define SCALE_FACTOR 100000
#define DEGREE_RANGE 360.0
#define RESOLUTION 0.5
#define TABLE_SIZE ((int)(2 * DEGREE_RANGE / RESOLUTION) + 1)

using namespace std;

void sin_table_init();
double getSineValue(double angle);

#endif