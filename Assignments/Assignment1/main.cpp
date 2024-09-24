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
#include <cctype>
#include <regex>
using namespace std; // std namespace

void trim_whitespaces(char *str);

int main(){
    Complex z1,z2,result;
    char operation;
    int arg_count;
    char extra;
    char input[100]; // input buffer

    fprintf(stderr,"Type a letter to specify the arithmetic operator (A, S, M, D) followed by two complex numbers expressed as pairs of doubles. Type Q to quit.");

    while (1) {
    fprintf(stderr, "Enter command: ");
    fgets(input, sizeof(input), stdin);
    trim_whitespaces(input);

    arg_count = sscanf(input, "%c%lf%lf%lf%lf%c", &operation, &z1.real, &z1.imag, &z2.real, &z2.imag, &extra);

    // Convert to uppercase
    operation = toupper(operation);

    // Error 1: Illegal command
    if (!(operation == 'A' || operation == 'S' || operation == 'M' || operation == 'D' || operation == 'Q')) {
        fprintf(stdout, "error code: 1: illegal command\n");
        continue;
    }

    // Error 2: Missing arguments
    if (operation != 'Q' && arg_count < 5) {
        fprintf(stdout, "error code: 2: missing arguments\n"); 
        continue;
    }

    // Error 3: Extra arguments
    if ( (arg_count == 6 &&  extra !='\0' && extra !='\n')|| (operation == 'Q' && arg_count > 1)) {
        fprintf(stdout, "error code: 3: extra arguments\n");
        continue;
    }

    switch (operation)
    {
        case 'A':
            add(z1,z2,&result);
            fprintf(stdout, "%f + j %f\n", result.real, result.imag);
            break;
        
        case 'S':
            subtract(z1,z2,&result);
            fprintf(stdout, "%f + j %f\n", result.real, result.imag);
            break;
        
        case 'M':
            multiply(z1,z2,&result);
            fprintf(stdout, "%f + j %f\n", result.real, result.imag);
            break;
        
        case 'D':
            if (divide(z1, z2, &result) == 1) {
                fprintf(stdout, "error code: 4: divide by zero\n");
            } else {
                fprintf(stdout, "%f + j %f\n", result.real, result.imag);
            }
            break;

        case 'Q':
            return 0;
        
        default:
            break;
    }
  }
    return 0;
}

void trim_whitespaces(char *str) {
    // Check for null or empty string
    if (str == NULL || *str == '\0') {
        return;
    }

    // Trim leading whitespace
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    // Null-terminate the trimmed string
    *(end + 1) = '\0';

    if (start != str) {
        memmove(str, start, (end - start + 2) * sizeof(char)); // +2 for null terminator
    }
}
