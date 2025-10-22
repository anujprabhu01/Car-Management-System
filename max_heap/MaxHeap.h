// Assignment: ASU CSE310 HW#3 Spring 2024
// Your Name: Anuj Prabhu
// ASU ID: 1225065855
// ASU Email address: adprabh1@asu.edu
// Description: MaxHeap.h file; this file contains all member variables and functions that ensure full functionality of a Max Heap.
//********************************************************

// import statements go here
#include <iostream>
#include <iomanip>
#include <string>
// #include <cmath>

// using statements go here
using namespace std;

// struct which represents a car
//  Each Car will have a unique Vin
struct Car
{
	string model, make;
	int vin; // Vehicle Identification Number
	double price;
};

// class MaxHeap represents a max heap that contains Car objects. The underline data structure
// is a one dimensional array of Cars.
class MaxHeap
{
private:
	struct Car *carArr; // an array of Cars
	int capacity, size; // capacity and size of the max heap

public:
	MaxHeap(int capacity);
	~MaxHeap();

	Car *getCarArr();
	int getSize();
	void setSize(int size);
	int getCapacity();
	int isFound(int aVin);
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
	bool heapInsert(int vin, string model, string make, double price);
	void heapify(int index);
	Car getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

// Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
	// Add your own code
	carArr = new Car[capacity]; // initialize carArr with specified capacity
	this->capacity = capacity;	//(?)
	size = 0;
}

// Destructor
// Before termination, the destructor is called to free the associated memory occupied by the heap.
// and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	// Add your own code
	delete[] carArr;
	cout << "\nThe number of deleted cars is: " << size << endl;
	size = 0;
}

// getter method to get carArr
Car *MaxHeap::getCarArr()
{
	return carArr;
}

// getter method to get heap size
int MaxHeap::getSize()
{
	return size;
}

// setter method to set heap size
void MaxHeap::setSize(int size)
{
	this->size = size;
}

// getter method to get heap capacity
int MaxHeap::getCapacity()
{
	return capacity;
}

// method that returns index of Car with specified VIN if found; else, it returns -1
int MaxHeap::isFound(int aVin)
{
	for (int i = 0; i < size; i++)
	{
		if (carArr[i].vin == aVin)
		{
			return i;
		}
	}
	return -1;
}

// method that returns the index of the left child of the given parent index
int MaxHeap::leftChild(int parentIndex)
{
	return (parentIndex * 2) + 1;
}

// method that returns the index of the right child of the given parent index
int MaxHeap::rightChild(int parentIndex)
{
	return (parentIndex * 2) + 2;
}

// method that returns the index of the parent of the given child index
int MaxHeap::parent(int childIndex)
{
	return (childIndex - 1) / 2;
}

//****************************************************
// increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
	if (index < 0 || index >= size) // if index is out of bounds
	{
		cout << "\nIncrease VIN error: index out of range" << endl; // print error message
		return false;
	}

	// Add your own code
	else
	{
		carArr[index].vin = oneCarWithNewVIN.vin; // set Car at index's vin to newl, specified vin
		// carArr[index] = oneCarWithNewVIN;
		while (index > 0 && carArr[parent(index)].vin < carArr[index].vin) // loop till index is in range and parent vin is less than child vin
		// ie loop ends when the carArr is again a max heap
		{
			struct Car temp = carArr[index]; // exchange parent with child
			carArr[index] = carArr[parent(index)];
			carArr[parent(index)] = temp;

			index = parent(index); // update index to index's parent to see if index is at the correct position
		}
		return true;
	}
	// return false;
}

// Add your own code to finish other functions
//----
//----
// method that inserts a Car object inside a heap based on given Car parameters.
bool MaxHeap::heapInsert(int vin, string model, string make, double price)
{
	if (isFound(vin) != -1) // if Car with specified VIN aldready exists inside the heap, print error messsgaes as VINs are unique.
	{
		cout << "Duplicated Car. Not added" << endl;
		return false;
	}
	if (size == capacity) // if heap size equals heap capacity, that means additional capacity is needed. So, double heap capacity.
	{
		struct Car *newCarArr = new Car[size]; // initialize new array of Cars
		for (int i = 0; i < size; i++)
		{
			newCarArr[i] = carArr[i]; // store all cars from carArr in temporary newCarArr
		}
		delete[] carArr;

		capacity *= 2;
		carArr = new Car[capacity]; // delete carArr and allocate additional, doubled capacity for it
		for (int i = 0; i < size; i++)
		{
			carArr[i] = newCarArr[i]; // copy elements from temporary array back into carArr
		}
		delete[] newCarArr; // free memory for newCarArr
		cout << "Reach the capacity limit, double the capacity now." << endl;
		cout << "The new capacity now is " << capacity << endl;
	}
	size++; // increase size of heap as additional node will be inserted into the heap

	struct Car dummyCar;
	dummyCar.vin = -10000;
	dummyCar.model = model;
	dummyCar.make = make;
	dummyCar.price = price;

	carArr[size - 1] = dummyCar; // place a dummy car as the last node of the heap with a very small VIN

	struct Car temp;
	temp.vin = vin;
	temp.model = model;
	temp.make = make;
	temp.price = price;

	bool result = heapIncreaseVIN(size - 1, temp); // increase the VIN of the last node of the heap (new node) with the Car passed in
	// the parameter.
	if (result == true)
	{
		return true;
	}
	return false;
}

// method that floats a node at given index down to its correct position in a MaxHeap
void MaxHeap::heapify(int index)
{
	int leftChildIndex = leftChild(index);	 // get left child of index
	int rightChildIndex = rightChild(index); // get right child of index
	int largestNodeIndex = 0;				 //(?)

	// see which node has the biggest VIN out of the parent, left child, and right child.
	if (leftChildIndex <= (size - 1) && carArr[leftChildIndex].vin > carArr[index].vin) // if leftChild is a left child index is > size - 1,
	// that means node at index is a leaf node / at its correct position
	{
		largestNodeIndex = leftChildIndex;
	}
	else
	{
		largestNodeIndex = index;
	}

	if (rightChildIndex <= (size - 1) && carArr[rightChildIndex].vin > carArr[largestNodeIndex].vin)
	{
		largestNodeIndex = rightChildIndex;
	}

	if (largestNodeIndex != index) // if a child is bigger than the parent, swap child and parent and call heapify
	{
		struct Car temp = carArr[index];
		carArr[index] = carArr[largestNodeIndex];
		carArr[largestNodeIndex] = temp;
		heapify(largestNodeIndex);
	}
}

// method that returns the root node of the max heap
Car MaxHeap::getHeapMax()
{
	return carArr[0];
}

// method that extracts the root node of the max heap
void MaxHeap::extractHeapMax()
{
	/*if (size < 1)
	{
		cout << "Empty heap, can NOT extract max" << endl;
	}*/
	// else
	//{
	struct Car max = carArr[0];
	carArr[0] = carArr[size - 1]; // set last leaf node as max heap root and float it down to its correct position; thus, making
	// a max heap again.
	size--; // decrement size of the heap as root node is extracted
	heapify(0);
	//}
}

// method that prints the contents of the max heap
void MaxHeap::printHeap()
{
	if (size == 0) // if an empty heap, relay empty heap message
	{
		cout << "Empty heap. no elements" << endl;
	}
	else
	{
		cout << "Heap capacity = " << capacity << endl;
		cout << "Heap size = " << size << endl;

		for (int i = 0; i < size; i++)
		{
			cout << left;
			cout << setw(8) << carArr[i].vin
				 << setw(12) << carArr[i].model
				 << setw(12) << carArr[i].make
				 << setw(8) << fixed << setprecision(2) << carArr[i].price << endl;
		}
	}
}