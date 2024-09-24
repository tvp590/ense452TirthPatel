/*
    Name        : Tirth V Patel
    SID         : 200435378
    Course      : ENSE 452
    Assignment  : 1
    File        : main.cpp
    purpose     : This file contains the main function to perform complex number operations.
*/

#include "complex.h"
#include <cstdio>
#include <_ctype.h>

int main(){
    Complex z1,z2,result;
    char operation;
    int arg_count;
    char extra;
    char input[100]; // input buffer

    while (1) {
    fprintf(stderr, "Enter command: ");
    fgets(input, sizeof(input), stdin);
    extra = '\0';  // Initialize extra to null character

    arg_count = sscanf(input, "%c%f%f%f%f%c", &operation, &z1.real, &z1.imag, &z2.real, &z2.imag, &extra);

    // Convert to uppercase
    operation = toupper(operation);

    // Error 1: Illegal command
    if (!(operation == 'A' || operation == 'S' || operation == 'M' || operation == 'D' || operation == 'Q')) {
        fprintf(stderr, "error code: 1: illegal command\n");
        continue;
    }

    // Error 2: Missing arguments
    if (operation != 'Q' && arg_count < 5) {
        fprintf(stderr, "error code: 2: missing arguments\n"); 
        continue;
    }

    // Error 3: Extra arguments
    if ( (arg_count == 6 &&  extra !='\0' && extra !='\n')|| (operation == 'Q' && arg_count > 1)) {
        fprintf(stderr, "error code: 3: extra arguments\n");
        continue;
    }

    switch (operation)
    {
        case 'A':
            add(z1,z2,&result);
            fprintf(stdout, "%.2f + %.2fi\n",result.real,result.imag);
            break;
        
        case 'S':
            subtract(z1,z2,&result);
            fprintf(stdout, "%.2f + %.2fi\n",result.real,result.imag);
            break;
        
        case 'M':
            multiply(z1,z2,&result);
            fprintf(stdout, "%.2f + %.2fi\n",result.real,result.imag);
            break;
        
        case 'D':
            if (divide(z1, z2, &result) == 1) {
                fprintf(stderr, "error code: 4: divide by zero\n");
            } else {
                fprintf(stdout, "%.2f + %.2fi\n", result.real, result.imag);
            }
            break;

        case 'Q':
            fprintf(stdout, "Quitting...\n");
            return 0;
        
        default:
            break;
    }
  }
    return 0;
}