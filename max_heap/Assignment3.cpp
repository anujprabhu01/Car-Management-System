// Assignment: ASU CSE310 HW#3 Spring 2024
// Name: Anuj Prabhu
// ASU ID: 1225065855
// ASU Email Address: adprabh1@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

// only include the necessary header file
//----
#include "MaxHeap.h"

// using statements go here
using namespace std;

// forward declarations go here
void printMenu();
void heapSort(MaxHeap *oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int vin;
	int oldVIN, newVIN;
	string model, make;
	double price;
	int capacity, index = -1; // array capacity and index

	// declare any other variables in case you need them
	//----
	int successF;
	int successI;

	Car carK;
	Car carM;

	// instantiate an empty Heap
	MaxHeap *heap1 = nullptr;
	printMenu();

	do
	{
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n'); // flush the buffer

		// matches one of the cases
		switch (input1)
		{
		case 'C': // create empty Heap with the relevant capacity
			cout << "\nPlease enter the heap capacity: ";
			cin >> capacity;
			cin.ignore(20, '\n'); // flush the buffer

			// Add your own code
			heap1 = new MaxHeap(capacity);

			break;

		case 'D': // delete the heap, call the destructor explicitly
			cout << "\nDelete the heap" << endl;
			// Add your own code
			heap1->~MaxHeap();

			heap1 = new MaxHeap(5);
			break;

		case 'E': // Extract the maximum node
			// Add your own code
			if (heap1 == nullptr || heap1->getSize() < 1) // if heap is empty or heap is not initialized
			{
				cout << "Empty heap, can NOT extract max" << endl; // print error message
			}
			else // else extract heap max
			{
				cout << "Before extract heap max operation:" << endl;
				heap1->printHeap();
				heap1->extractHeapMax();
				cout << "After extract heap max operation:" << endl;
				heap1->printHeap();
			}
			break;

		case 'F': // Find a Car
			cout << "\nEnter the car VIN you want to search: ";
			cin >> vin;
			cin.ignore(20, '\n'); // flush the buffer

			// Add your own code
			//----
			successF = heap1->isFound(vin);

			if (successF != -1)
			{
				cout << "Car with VIN: " << vin << " is found" << endl;
			}
			else
			{
				cout << "Car with VIN: " << vin << " is NOT found" << endl;
			}
			break;

		case 'I':							   // Insert a Car
			cout << "\nEnter the car model: "; // get all Car information/parameters
			cin >> model;

			cout << "\nEnter the car make: ";
			cin >> make;

			cout << "\nEnter the car VIN: ";
			cin >> vin;
			cout << "\nEnter the car price: ";
			cin >> price;
			cin.ignore(20, '\n'); // flush the buffer

			// Add your own code
			successI = heap1->heapInsert(vin, model, make, price); // insert Car into heap
			if (successI == true)								   // check if insertion was successful or not
			{
				cout << "Car \"" << model << " " << make << "\" is added" << endl;
			}
			else
			{
				cout << "Car \"" << model << " " << make << "\" is NOT added" << endl;
			}

			break;

		case 'K': // increase the vin
			cout << "\nEnter the old car VIN you want to increase: ";
			cin >> oldVIN;
			cout << "\nEnter the new car VIN: ";
			cin >> newVIN;
			cin.ignore(20, '\n'); // flush the buffer

			// Add your own code
			if (newVIN <= oldVIN) // check boundary cases
			{
				cout << "Increase VIN error: new vin is smaller than current vin" << endl;
			}
			else if (heap1->isFound(oldVIN) == -1)
			{
				cout << "The old VIN you try to increase does not exist" << endl;
			}
			else if (heap1->isFound(newVIN) != -1)
			{
				cout << "The new VIN you entered already exist, increase VIN operation failed" << endl;
			}
			else
			{
				index = heap1->isFound(oldVIN);
				carK.vin = newVIN;
				cout << "Before increase VIN operation:" << endl;
				heap1->printHeap();
				heap1->heapIncreaseVIN(index, carK);
				cout << "Car with old VIN: " << oldVIN << " is increased to new VIN: " << newVIN << endl;
				cout << "After increase VIN operation:" << endl;
				heap1->printHeap();
			}
			break;

		case 'M': // get maximum node

			// Add your own code
			if (heap1->getSize() < 1) // if heap is empty, no max node, so relay an error message
			{
				cout << "Empty heap, can NOT get max node" << endl;
			}
			else
			{
				carM = heap1->getHeapMax();
				cout << "The maximum heap node is:" << endl;
				cout << left;
				cout << setw(8) << carM.vin
					 << setw(12) << carM.model
					 << setw(12) << carM.make
					 << setw(8) << fixed << setprecision(2) << carM.price << endl;
			}

			break;

		case 'P': // Print heap contents

			// Add your own code
			if (heap1->getSize() < 1)
			{
				cout << "Empty heap, no elements" << endl;
			}
			else
			{
				heap1->printHeap();
			}

			break;

		case 'S': // HeapSort
			cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
			// Add your own code
			heapSort(heap1); // heap sort heap1

			break;

		case 'Q': // Quit
			delete heap1;
			break;

		case '?': // Display Menu
			printMenu();
			break;

		default:
			cout << "Unknown action\n";
			break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
// Given a max heap, we want to sort it in increasing order according to Car VIN, put the
// sorting result inside another array and print it out
void heapSort(MaxHeap *oneMaxHeap)
{
	// Add your own code
	int size = oneMaxHeap->getSize();
	// struct Car *carArr = oneMaxHeap->getCarArr();
	struct Car *tempArr = new Car[size]; // create a temporary Car array to store the sorted array
	for (int i = size - 1; i >= 0; i--)	 // iterate from last element index of the heap to the first element index
	{
		tempArr[i] = oneMaxHeap->getHeapMax(); // store the largest element in last index of the sorted array, second largest
		// in the second last index, and so on (sort in ascending order)
		oneMaxHeap->extractHeapMax(); // every time after the root is retrieved, extract the root, set last leaf node as new
									  // root and heapfipy the new root, thus creating a max heap again.
									  //  struct Car temp = carArr[0];
									  //  carArr[0] = carArr[i];
									  //  carArr[i] = temp;

		// tempArr[i] = carArr[i];

		// oneMaxHeap->setSize(i);

		//  size--;
		// oneMaxHeap->heapify(0);
		// carArr = oneMaxHeap->getCarArr();
	}
	for (int i = 0; i < size; i++) // print the sorted array
	{
		cout << left;
		cout << setw(8) << tempArr[i].vin
			 << setw(12) << tempArr[i].model
			 << setw(12) << tempArr[i].make
			 << setw(8) << fixed << setprecision(2) << tempArr[i].price << endl;
	}
	delete[] tempArr;
}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
