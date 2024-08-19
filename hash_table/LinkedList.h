// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: A simple linked list that implements a list of Car objects. A user can
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

/*
    I have reused my own code from my assignment 1 submission to write this class.
*/

// import statements go here
#include <iostream>
#include <iomanip>
#include <string>

// using statements go here
using namespace std;

struct Car
{
    string model, make;
    int vin;
    double price;
    struct Car *next;

    // constructor to initialize Car object
    Car(string model, string make, int vin, double price)
    {
        this->model = model;
        this->make = make;
        this->vin = vin;
        this->price = price;
        this->next = nullptr;
    }
};

class LinkedList
{
private:
    struct Car *head;
    int size; // a variable represents number of Cars inside the list
public:
    LinkedList();
    ~LinkedList();
    Car *getHead();
    int getSize();
    bool searchCar(int carVIN);
    bool insertCar(string model, string make, int vin, double price);
    bool deleteCar(string model, string make, int carVIN);
    void displayList();
};

// Constructor
LinkedList::LinkedList()
{
    //----
    size = 0;
    head = nullptr;
}

// Destructor
LinkedList::~LinkedList()
{
    //----
    struct Car *temp = head;

    while (temp != nullptr) // traverse the linked list
    {
        head = head->next;
        delete temp; // delete each node
        temp = head; // update temp pointer
    }
    // cout << "The number of deleted Car is: " << size << "\n";
    size = 0;
}

Car *LinkedList::getHead()
{
    //----
    return head;
}

// Return number of Cars inside the Linked list
int LinkedList::getSize()
{
    //----
    return size;
}

// This function does a linear search on the Car list with the given Car VIN
// it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN)
{
    //----
    struct Car *temp = head;

    while (temp != nullptr) // traverse the list
    {
        if (temp->vin == carVIN) // if a vin match is found, return true
        {
            return true;
        }
        temp = temp->next;
    }
    return false; // else, return false at the end of the method
}

// Insert the parameter Car at the head of the linked list.
// return true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price)
{
    //----
    struct Car *newCar = new Car(model, make, vin, price);

    if (head == nullptr)
    {
        head = newCar;
        size++;
        return true;
    }
    else
    {
        newCar->next = head;
        head = newCar;
        size++;
        return true;
    }
    return false;
}

// Delete the Car with the given Car VIN from the linked list.
// Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(string model, string make, int carVIN)
{
    //----
    if (head != nullptr) // if the list is not empty
    {
        if (model == head->model && make == head->make && carVIN == head->vin) // if the Car to be removed is at head, handle accordingly.
        {
            struct Car *temp = head;
            head = head->next; // update head pointer
            delete temp;       // then delete temp
            temp = head;       // set temp the same as head
            size--;
            return true;
        }
        else
        {
            struct Car *previous = nullptr;
            struct Car *temp = head;
            while (temp != nullptr) // if the Car to be removed is somewhere in the middle or the end
            // then run a loop
            {
                if (model == temp->model && make == temp->make && carVIN == temp->vin) // if Car found, then check if that Car is at the tail or in the middle.
                // update pointers for both scenarios accordingly.
                {
                    if (temp->next == nullptr)
                    {
                        previous->next = nullptr;
                        delete temp;
                        temp = nullptr;
                        size--;
                        return true;
                    }
                    else
                    {
                        previous->next = temp->next;
                        delete temp;
                        temp = previous->next;
                        size--;
                        return true;
                    }
                }
                else
                {
                    previous = temp; // traverse through each node
                    temp = temp->next;
                }
            }
        }
        return false;
    }
    else // if the list is empty, return false
    {
        return false;
    }
}

// This function displays the content of the linked list.
void LinkedList::displayList()
{
    struct Car *temp = head;
    if (head == nullptr)
    {
        // empty linked list, print nothing here
    }
    else
    {
        while (temp != nullptr)
        {
            cout << left << setw(18) << temp->model
                 << left << setw(18) << temp->make
                 << right << setw(8) << temp->vin
                 << setw(10) << fixed << setprecision(2) << temp->price << "\n";
            temp = temp->next;
        }
    }
}

// bool LinkedList::deleteCar(string model, string make, int carVIN)
// {
//     //----
//     if (head == nullptr) // if the list is empty, nothing to remove, so return false
//     {
//         // cout << "list empty; nothing to delete" << endl;
//         return false;
//     }
//     else if (model == head->model && make == head->make && carVIN == head->vin) // if the Car to be removed is at head, handle accordingly.
//     {
//         struct Car *temp = head;
//         head = head->next; // update head pointer
//         delete temp;       // then delete temp
//         temp = head;       // set temp the same as head
//         size--;
//         return true;
//     }
//     else
//     {
//         struct Car *previous = nullptr;
//         struct Car *temp = head;
//         while (temp != nullptr) // if the Car to be removed is somewhere in the middle or the end
//         // then run a loop
//         {
//             if (model == temp->model && make == temp->make && carVIN == temp->vin) // if Car found, then check if that Car is at the tail or in the middle.
//             // update pointers for both scenarios accordingly.
//             {
//                 if (temp->next == nullptr)
//                 {
//                     previous->next = nullptr;
//                     delete temp;
//                     temp = nullptr;
//                     size--;
//                     return true;
//                 }
//                 else
//                 {
//                     previous->next = temp->next;
//                     delete temp;
//                     temp = previous->next;
//                     size--;
//                     return true;
//                 }
//             }
//             else
//             {
//                 previous = temp; // traverse through each node
//                 temp = temp->next;
//             }
//         }
//     }
//     return false;
// }