//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: //---- is where you should add your own code
//********************************************************************

// include necessary header file here
//----
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "ArrivalList.h"

// using statements go here
using namespace std;

// represent each node of the graph which is a departure location
// with all the relevant info.
struct Departure
{
    string depAddress;
    double d;
    struct Departure *pi;
    ArrivalList *arrList;
};

// class MinPriorityQueue represents a Min-heap that contains Departure objects.
class MinPriorityQueue
{
private:
    struct Departure *departureArr; // a Departure array
    int capacity, size;

public:
    MinPriorityQueue(int capacity);
    ~MinPriorityQueue();

    Departure *getDepartureArr();
    Departure getHeapMin();
    int getSize();
    void setSize(int size);
    int getCapacity();
    int leftChild(int parentIndex);
    int rightChild(int parentIndex);
    int parent(int childIndex);
    int isFound(string oneDepAddress);
    bool decreaseKey(int index, Departure oneDepartureWithNewDValue);
    void heapify(int index);
    bool insert(Departure oneDeparture);
    void extractHeapMin();
    void build_min_heap();
    void printHeap();

    // add other function definitions here if 100% necessary
    //----
};

MinPriorityQueue::MinPriorityQueue(int capacity)
{
    departureArr = new Departure[capacity]; // initialize departureArr with specified capacity
    this->capacity = capacity;
    size = 0;
}

MinPriorityQueue::~MinPriorityQueue()
{
    // for (int i = 0; i < size; i++)
    //{
    // departureArr[i].arrList->~ArrivalList(); // delete and free memory for every linked list inside the hash table
    //}
    delete[] departureArr;
    cout << "\nThe number of deleted departures is: " << size << endl;
    size = 0;
}

Departure *MinPriorityQueue::getDepartureArr()
{
    return departureArr;
}

Departure MinPriorityQueue::getHeapMin()
{
    return departureArr[0];
}

int MinPriorityQueue::getSize()
{
    return size;
}

void MinPriorityQueue::setSize(int size)
{
    this->size = size;
}

int MinPriorityQueue::getCapacity()
{
    return capacity;
}

// method that returns the index of the left child of the given parent index
int MinPriorityQueue::leftChild(int parentIndex)
{
    return (parentIndex * 2) + 1;
}

// method that returns the index of the right child of the given parent index
int MinPriorityQueue::rightChild(int parentIndex)
{
    return (parentIndex * 2) + 2;
}

// method that returns the index of the parent of the given child index
int MinPriorityQueue::parent(int childIndex)
{
    return (childIndex - 1) / 2;
}

int MinPriorityQueue::isFound(string oneDepAddress)
{
    for (int i = 0; i < size; i++)
    {
        if (departureArr[i].depAddress == oneDepAddress)
        {
            return i;
        }
    }
    return -1;
}

bool MinPriorityQueue::decreaseKey(int index, Departure oneDepartureWithNewDValue)
{
    if (index < 0 || index >= size) // if index is out of bounds
    {
        cout << "\ndecreaseKey error: index out of range" << endl; // print error message
        return false;
    }

    // Add your own code
    else
    {
        departureArr[index].d = oneDepartureWithNewDValue.d;                       // set Departure at index's d to newl, specified d
        while (index > 0 && departureArr[parent(index)].d > departureArr[index].d) // loop till index is in range and parent d is less than child d
        // ie loop ends when the departureArr is again a max heap
        {
            struct Departure temp = departureArr[index]; // exchange parent with child
            departureArr[index] = departureArr[parent(index)];
            departureArr[parent(index)] = temp;

            index = parent(index); // update index to index's parent to see if index is at the correct position
        }
        return true;
    }
}

void MinPriorityQueue::heapify(int index)
{
    int leftChildIndex = leftChild(index);   // get left child of index
    int rightChildIndex = rightChild(index); // get right child of index
    int smallestNodeIndex = 0;               //(?)

    // see which node has the biggest d out of the parent, left child, and right child.
    if (leftChildIndex <= (size - 1) && departureArr[leftChildIndex].d < departureArr[index].d) // if leftChild is a left child index is > size - 1,
    // that means node at index is a leaf node / at its correct position
    {
        smallestNodeIndex = leftChildIndex;
    }
    else
    {
        smallestNodeIndex = index;
    }

    if (rightChildIndex <= (size - 1) && departureArr[rightChildIndex].d < departureArr[smallestNodeIndex].d)
    {
        smallestNodeIndex = rightChildIndex;
    }

    if (smallestNodeIndex != index) // if a child is bigger than the parent, swap child and parent and call heapify
    {
        struct Departure temp = departureArr[index];
        departureArr[index] = departureArr[smallestNodeIndex];
        departureArr[smallestNodeIndex] = temp;
        heapify(smallestNodeIndex);
    }
}

//************************************************************
// when you create the dummy node, initialize its d value to be
// 50000 which represents infinite large
bool MinPriorityQueue::insert(Departure oneDeparture)
{
    if (isFound(oneDeparture.depAddress) != -1) // if Departure with specified d aldready exists inside the heap, print error messsgaes as ds are unique.
    {
        cout << "Duplicated Departure. Not added" << endl;
        return false;
    }
    if (size == capacity) // if heap size equals heap capacity, that means additional capacity is needed. So, double heap capacity.
    {
        struct Departure *newDepArr = new Departure[size]; // initialize new array of Departures
        for (int i = 0; i < size; i++)
        {
            newDepArr[i] = departureArr[i]; // store all Departures from departureArr in temporary newdepartureArr
        }
        delete[] departureArr;

        capacity *= 2;
        departureArr = new Departure[capacity]; // delete departureArr and allocate additional, doubled capacity for it
        for (int i = 0; i < size; i++)
        {
            departureArr[i] = newDepArr[i]; // copy elements from temporary array back into departureArr
        }
        delete[] newDepArr; // free memory for newdepartureArr
        cout << "Reach the capacity limit, double the capacity now." << endl;
        cout << "The new capacity now is " << capacity << endl;
    }
    size++; // increase size of heap as additional node will be inserted into the heap

    struct Departure dummyDeparture;
    dummyDeparture.d = 50000;
    dummyDeparture.pi = oneDeparture.pi;
    dummyDeparture.depAddress = oneDeparture.depAddress;
    dummyDeparture.arrList = oneDeparture.arrList;

    departureArr[size - 1] = dummyDeparture; // place a dummy Departure as the last node of the heap with a very small d

    struct Departure temp;
    temp.d = oneDeparture.d;
    temp.pi = oneDeparture.pi;
    temp.depAddress = oneDeparture.depAddress;
    temp.arrList = oneDeparture.arrList;

    bool result = decreaseKey(size - 1, temp); // increase the d of the last node of the heap (new node) with the Departure passed in
    // the parameter.
    if (result == true)
    {
        return true;
    }
    return false;
}

void MinPriorityQueue::extractHeapMin()
{
    struct Departure min = departureArr[0];
    departureArr[0] = departureArr[size - 1]; // set last leaf node as max heap root and float it down to its correct position; thus, making
    // a max heap again.
    size--; // decrement size of the heap as root node is extracted
    heapify(0);
}

//****************************************************************************
// Given the original departureArr, the function build a min-heap by using d value
void MinPriorityQueue::build_min_heap()
{
    //----
    for (int i = floor(size / 2) - 1; i >= 0; i--)
    {
        heapify(i);
    }
}

//*********************************************************
void MinPriorityQueue::printHeap()
{
    if (size == 0) // if an empty heap, relay empty heap message
    {
        cout << "Empty heap. no elements" << endl;
    }
    else
    {
        cout << "\nHeap size = " << getSize() << "\n"
             << endl;

        cout << left;
        cout << setw(15) << "Departure"
             << setw(12) << "d Value"
             << setw(15) << "PI"
             << "Arrival List" << endl;

        for (int i = 0; i < size; i++)
        {
            cout << left;
            cout << setw(15) << departureArr[i].depAddress
                 << setw(12) << setprecision(2) << departureArr[i].d;
            if (departureArr[i].pi != nullptr)
            {
                cout << setw(15) << departureArr[i].pi;
            }
            else
            {
                cout << setw(15) << "No Parent";
            }
            departureArr[i].arrList->printArrivalList();
        }
    }
}