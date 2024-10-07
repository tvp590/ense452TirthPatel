/**
   Project: Implementation of a Queue in C++.
   Programmer: Karim Naqvi
   Course: enel452
   Description: test code
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

#include "queue.h"
using namespace std;

/**
   Compare the given queue to the given array of data elements.  Return
   true if they are all equal.
 */
bool testQueueEquality( Queue & q, std::vector<Data> const & array)
{
    if (q.size() != array.size())
	return false;

    for (unsigned i = 0; i < q.size(); ++i)
    {
        Data d(0,0);
	q.remove(&d);
	if ( !d.equals(array[i]) )
	    return false;
	q.insert(d);
    }
    return true;
}

void printExpectedData(const std::vector<Data>& expectedData) {
    vector<Data>::size_type i = 0;
    printf("Expected data: ");
    
    while (i < expectedData.size()) {
        printf("%lu:(%d,%d) ", i, expectedData[i].x, expectedData[i].y);
        i++;
    }
    printf("\n");
}

/*
* Test the insert function
* return void
*/
void testInsertFunction(){
    fprintf(stdout, "Testing insert function\n");
    Queue q2;

    q2.insert(Data(1,2));
    q2.insert(Data(3,4));
    q2.insert(Data(5,6));
    q2.insert(Data(-2,-3),1);
    q2.insert(Data(-4,-5),3);

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
    //assert(testQueueEquality(q2, expectedData));
    printExpectedData(expectedData);
    printf("Queue data:    ");
    q2.print();

    // insert at size - 1
    q2.insert(Data(11,12), q2.size()-1);
    expectedData.insert(expectedData.end()-1, Data(11,12));
    //assert(testQueueEquality(q2, expectedData));
    printExpectedData(expectedData);
    printf("Queue data:    ");
    q2.print();

}

int main()
{
    cout << "Testing queue.\n";
    Queue q1;

    q1.insert(Data(1,1));
    q1.insert(Data(3,3));
    q1.insert(Data(5,5));

    q1.print();

    vector<Data> dataVec;
    dataVec.push_back(Data(1,1));
    dataVec.push_back(Data(3,3));
    dataVec.push_back(Data(5,5));

    assert(testQueueEquality(q1, dataVec));

    Data d44(4, 4);
    bool found = q1.search(d44);
    assert(found == false);


    q1.insert(d44);  // now is (1,1),(3,3),(5,5),(4,4)
    found = q1.search(d44);
    assert(found == true);

    // now queue is(1,1),(3,3),(5,5),(4,4) and 
    // dataVec has (1,1),(3,3),(5,5).  Not equal
    assert(testQueueEquality(q1, dataVec) == false);

    Data temp;
    q1.remove(&temp);  // now q1 is (3,3),(5,5),(4,4)

    Data temp2(1,1);
    assert(temp.equals(temp2));  // (1,1) == (1,1)

    Data temp3(6,6);
    found = q1.search(temp3);
    assert(found == false);

    testInsertFunction();       // test insert function
}
