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

The unit test for the enhanced queue is implemented in the `testq.cpp` file. The test case visually prints the expected data and the queue data to ensure correctness during the test run.

```cpp
void testInsertFunction() {
    fprintf(stdout, "Testing insert function\n");
    Queue q2;

    q2.insert(Data(1,2));
    q2.insert(Data(3,4));
    q2.insert(Data(5,6));
    q2.insert(Data(-2,-3), 1);
    q2.insert(Data(-4,-5), 3);

    vector<Data> expectedData;
    expectedData.push_back(Data(1, 2));
    expectedData.push_back(Data(-2, -3));
    expectedData.push_back(Data(3, 4));
    expectedData.push_back(Data(-4, -5));
    expectedData.push_back(Data(5, 6));

    assert(testQueueEquality(q2, expectedData)); 

    // insert at the beginning
    q2.insert(Data(7,8), 0);
    expectedData.insert(expectedData.begin(), Data(7,8));
    assert(testQueueEquality(q2, expectedData));

    // insert at the end
    q2.insert(Data(9,10), q2.size());
    expectedData.insert(expectedData.end(), Data(9,10));
    printExpectedData(expectedData);  // Visual print of expected data
    printf("Queue data:    ");
    q2.print();  // Visual print of queue data

    // insert at size - 1
    q2.insert(Data(11,12), q2.size()-1);
    expectedData.insert(expectedData.end()-1, Data(11,12));
    printExpectedData(expectedData);  // Visual print of expected data
    printf("Queue data:    ");
    q2.print();  // Visual print of queue data
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