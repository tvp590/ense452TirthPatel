/*
    Name        : Tirth V Patel
    SID         : 200435378
    Course      : ENSE 452
    Assignment  : 1
    File        : complex.h
    purpose     : This file contains the function prototypes for the complex number operations.
*/

#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex
{
    float real;
    float imag;
};

// Function prototypes
void add(Complex z1, Complex z2, Complex* result);
void subtract(Complex z1, Complex z2, Complex* result);
void multiply(Complex z1, Complex z2, Complex* result);
int divide(Complex z1, Complex z2, Complex* result);


#endif