Complex Number Calculator - README

Overview : 
    This command-line complex number calculator is designed to perform basic arithmetic operations (Addition, Subtraction, Multiplication, and Division) on complex numbers. It operates in a Read-Evaluate-Print Loop (REPL) format, allowing users to input commands interactively.

Usage: 
    Users can input commands in the following format:

    Enter exp: <Command> <Real1> <Imaginary1> <Real2> <Imaginary2>

    where:
        <Command> is one of the following:
            - add: Addition of two complex numbers
            - sub: Subtraction of two complex numbers
            - mul: Multiplication of two complex numbers
            - div: Division of two complex numbers
        <Real1> and <Imaginary1> are the real and imaginary parts of the first complex number, respectively
        <Real2> and <Imaginary2> are the real and imaginary parts of the second complex number, respectively

    <command> can be: 
    - A or a for addition
    - S or s for subtraction
    - M or m for multiplication
    - D or d for division
    - Q or q for quit    

    Example:
    To add two complex numbers 1+2j and 3+4j, the user would input:
        Enter exp: add 1 2 3 4
        Output: 4 + j 6
    
Limitations:
    Command input is case-insensitive; however, only specified commands (A, S, M, D, Q) are valid.

Error Handling:
    The calculator includes basic error handling for erroneous input:
    - Error 1: Illegal command (output error code: 1: illegal command)
    - Error 2: Missing arguments (output error code: 2: missing arguments)
    - Error 3: Extra arguments (output error code: 3: extra arguments)
    - Error 4: Division by zero (output error code: 4: divide by zero)

Build Instructions:
    The calculator can be built using the provided Makefile. To build the calculator, navigate to the directory containing the Makefile and run the following command:
        make

    To clean the build files, run:
        make clean

    The calculator executable will be generated as 'as1' in the same directory.

