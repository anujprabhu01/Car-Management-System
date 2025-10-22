//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

// using  statements go here
using namespace std;

// Arrival represents an arrival address with distance and road
// category info. from a specific departure address
struct Arrival
{
    string arrAddress;
    double distance;     // miles from the departure address to this arrival address
    string roadCategory; // Interstates, Arterials, Collectors or Local streets
    struct Arrival *next;
};

// class ArrivalList contains a linked list of Arrival objects
class ArrivalList
{
private:
    struct Arrival *head;

public:
    ArrivalList();
    ~ArrivalList();
    Arrival *getHead();
    Arrival *findArrival(string oneAddress);
    bool addArrival(string oneAddress, double distance, string roadCategory);
    void printArrivalList();
};

ArrivalList::ArrivalList()
{
    head = nullptr;
}

//*****************************************************************************************************
// Destructor. Before termination, the destructor is called to free the associated memory occupied by the
// existing linked list. It deletes all the Arrivals including the head and finally prints the number of
// Arrival deleted by it.
//----
ArrivalList::~ArrivalList()
{
    // add your own code
    int arrivalsCount = 0;

    struct Arrival *temp = head;

    while (temp != nullptr) // traverse the linked list
    {
        head = head->next;
        delete temp; // delete each node
        temp = head; // update temp pointer
        arrivalsCount++;
    }
    cout << "The number of deleted arrival addresses are: " << arrivalsCount << "\n";
}

// According to above class definition, define all functions accordingly
//----
Arrival *ArrivalList::getHead()
{
    return head;
}

Arrival *ArrivalList::findArrival(string oneAddress)
{
    struct Arrival *temp = head;

    while (temp != nullptr) // traverse the list
    {
        if (temp->arrAddress == oneAddress) // if an address match is found, return the Arrival object
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr; // else, return NULL at the end of the method
}

bool ArrivalList::addArrival(string oneAddress, double distance, string roadCategory)
{
    if (findArrival(oneAddress) != nullptr) // check if addres are same; if yes, duplicate arrival, so no point in going ahead, terminate process.
    {
        cout << "Duplicate Address. Not added.\n";
        return false;
    }
    else
    {
        struct Arrival *newArrival = new Arrival();
        newArrival->arrAddress = oneAddress;
        newArrival->distance = distance;
        newArrival->roadCategory = roadCategory;
        newArrival->next = nullptr;

        if (head == nullptr)
        {
            head = newArrival;
            return true;
        }
        else if (oneAddress.compare(head->arrAddress) < 0)
        {
            newArrival->next = head;
            head = newArrival;
            return true;
        }
        else
        {
            struct Arrival *previous = nullptr;
            struct Arrival *temp = head;

            while (temp != nullptr && oneAddress.compare(temp->arrAddress) > 0)
            {
                previous = temp; // correctly advance previous and temp pointers.
                temp = temp->next;
            }

            if (previous->next == nullptr) // Once you have found where to insert your Car object,
            // check if that position is a boundary case. If yes, handle accordingly.
            {
                previous->next = newArrival;
                return true;
            }
            else
            { // If no, do a generic add.
                previous->next = newArrival;
                newArrival->next = temp;
                return true;
            }
        }
    }
}

// Prints all the arrival address in the linked list starting from the head.
void ArrivalList::printArrivalList()
{
    //----
    if (head == nullptr)
    {
        cout << "Arrival list is empty\n";
    }
    else
    {
        struct Arrival *temp = head;
        while (temp != nullptr)
        {
            cout << temp->arrAddress
                 << fixed << setprecision(2) << "(" << temp->distance << "/" << temp->roadCategory << "),";
            temp = temp->next;
        }
        cout << "\n";
    }
}