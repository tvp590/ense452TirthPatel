## Sine Lookup Table Project

### Overview

This project implements a sine lookup table to efficiently approximate sine values for angles between -360.0 and +360.0 degrees in 0.5-degree increments. The lookup table is compared against the standard sin() function to measure performance. The program outputs the time taken for each method and the speedup factor of using the lookup table over the sin() function.

---

### How to Use the Makefile

1. Compile the Program: Run the following command in the terminal:
    ```c
    make
    ```

2. Run the Program:
   ```c
    ./as4
   ```

3. Clean Up: To remove the object files and executable, use:
    ```c
    make clean
    ```

---

### Sample Output

The program performs a benchmark to compare the speed of the sine lookup table versus the standard sin() function. Below is a sample output format:

```sql

    Measurement: using clock() with 1e9 loops.

        Function                Speed
       -------------------------------
       table lookup          2.251 ns
       Built-in sin()        13.187 ns
       Table Speedup         5.9x
```
