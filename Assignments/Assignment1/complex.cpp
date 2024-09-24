/*
    Name        : Tirth V Patel
    SID         : 200435378
    Course      : ENSE 452
    Assignment  : 1
    File        : complex.cpp
    purpose     : This file contains the function definitions for the complex number operations.
*/

#include "complex.h"
#include <cstdio>

// Function to add two complex numbers
void add (Complex z1, Complex z2, Complex* result)
{
    result->real = z1.real + z2.real;
    result->imag = z1.imag + z2.imag;
}

// Function to subtract two complex numbers
void subtract (Complex z1, Complex z2, Complex* result)
{
    result->real = z1.real - z2.real;
    result->imag = z1.imag - z2.imag;
}

// Function to multiply two complex numbers
void multiply (Complex z1, Complex z2, Complex* result)
{
    result->real = z1.real * z2.real - z1.imag * z2.imag;
    result->imag = z1.real * z2.imag + z1.imag * z2.real;
}

// Function to divide two complex numbers
int divide (Complex z1, Complex z2, Complex* result)
{
    double denominator = z2.real * z2.real + z2.imag * z2.imag;
    if (denominator == 0)
    {
        // handle divide by zero error
        return 1;
    }
    result->real = (z1.real * z2.real + z1.imag * z2.imag) / denominator;
    result->imag = (z1.imag * z2.real - z1.real * z2.imag) / denominator;

    return 0;
}
