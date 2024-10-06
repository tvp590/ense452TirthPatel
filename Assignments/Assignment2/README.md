# Assignment 2 README

## Overview

This assignment implements an enhanced queue data structure with an `insert` method that allows inserting elements at a specified position.

## New Functionality

### `insert(Data d, unsigned position)`

- **Description**: Inserts a `Data` element at the specified position in the queue.
- **Usage**:
  ```cpp
    q.insert(Data(5, 10), 2); // Inserts Data(5, 10) at position 2.
  ```

## Unit Test

The unit test for the enhanced queue is implemented in the `testq.cpp` file. The test cases are as follows:

```cpp
void testInsertFunction(){
    Queue q2;

    q2.insert(Data(1,2));
    q2.insert(Data(3,4));
    q2.insert(Data(5,6),1);
    ...
    assert(testQueueEquality(q2, {Data(1,2), Data(5,6), Data(3,4)}));
}
```

## Compilation and Execution
- To compile this program, run the following command:
  ```bash
    make
  ```
- To clean the build files, run:
    ```bash
        make clean
    ```
- To run the program, execute the following command:
  ```bash
    ./testq
  ```