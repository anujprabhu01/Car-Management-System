// ASU CSE310 Spring 2024 Assignment #1
// Name: Anuj Prabhu
// ASU ID: 1225065855
// Description: LinkedList.h file; this file contains the Car struct and LinkedList class.
// This class  contains all member methods that provide the linkedlist's complete functionality.

// library imports go here
#include <iostream>
#include <iomanip>
#include <string>

// using statements go here
using namespace std;

// Car represents a Car information
struct Car
{
    string model, make;
    int vin; // vehicle identification number
    double price;
    struct Car *next; // pointer that stores next Car's address

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

// class LinkedList will contains a linked list of Cars
class LinkedList
{
    // private members
private:
    struct Car *head;

    // public members
public:
    LinkedList();
    ~LinkedList();
    bool findCar(int aVin);
    bool addCar(string model, string make, int vin, double price);
    bool removeByVin(int aVin);
    bool removeByModelAndMake(string model, string make);
    bool changeCarInfo(int aVin, string newModelAndMake);
    bool updateCarPrice(int aVin, double newPrice);
    void printCarListByMake(string make);
    void printCarList();
};

// Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    // add your own code
    head = nullptr;
}

// Destructor
// Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
// It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
// Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    // add your own code
    int carCount = 0;

    struct Car *temp = head;

    while (temp != nullptr) // traverse the linked list
    {
        head = head->next;
        delete temp; // delete each node
        temp = head; // update temp pointer
        carCount++;
    }
    cout << "The number of deleted Car is: " << carCount << "\n";
}

// A function to identify if the parameterized Car is inside the LinkedList or not.
// Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
    // add your own code
    struct Car *temp = head;

    while (temp != nullptr) // traverse the list
    {
        if (temp->vin == aVin) // if a vin match is found, return true
        {
            return true;
        }
        temp = temp->next;
    }
    return false; // else, return false at the end of the method
}

// Creates a new Car and inserts it into the list at the right place.
// It also maintains an alphabetical ordering of Cars by their make and model, i.e.
// first by make, if two cars have same makes, then we will list them by model. Note: each Car
// has a unique vin, the vehicle identification number, but may have the same make and model.
// In case two Cars have same make and model, they should be inserted according to the
// increasing order of their vins.
// Return value: true if it is successfully inserted and false in case of failures.

/*
1.) check if vins are same; if yes, duplicate car, so no point in going ahead, terminate process.
2.) else, if the list in empty, assign the new node as head of the list.
3.) else, check if node should be added to head. If yes, handle accordingly.
4.) Else, loop the list till you find the correct position to insert the node alphabetically.
5.) Once you have found where to insert your Car object, check if that position is a boundary case. If yes, handle accordingly.
    If no, do a generic add.
*/
bool LinkedList::addCar(string model, string make, int vin, double price)
{
    if (findCar(vin) == true) // check if vins are same; if yes, duplicate car, so no point in going ahead, terminate process.
    {
        cout << "Duplicate Car. Not added.\n";
        return false;
    }
    else
    {
        struct Car *newCar = new Car(model, make, vin, price);

        if (head == nullptr) // else, if the list in empty, assign the new node as head of the list.
        {
            head = newCar;
            return true;
        }
        else if ( // else, check if node should be added to head. If yes, handle accordingly.
                  // Check for all scenarios for a valid alphabetical insertion.
            (make.compare(head->make) < 0) ||
            (make.compare(head->make) == 0 && model.compare(head->model) < 0) ||
            (make.compare(head->make) == 0 && model.compare(head->model) == 0 && vin < head->vin))
        {
            newCar->next = head;
            head = newCar;
            return true;
        }
        else
        {
            struct Car *previous = nullptr;
            struct Car *temp = head;

            while ( // Else, loop the list till you find the correct position to insert the node alphabetically.
                temp != nullptr &&
                ((make.compare(temp->make) > 0) ||
                 (make.compare(temp->make) == 0 && model.compare(temp->model) > 0) ||
                 (make.compare(temp->make) == 0 && model.compare(temp->model) == 0 && vin > temp->vin)))
            {
                previous = temp; // correctly advance previous and temp pointers.
                temp = temp->next;
            }

            if (previous->next == nullptr) // Once you have found where to insert your Car object,
            // check if that position is a boundary case. If yes, handle accordingly.
            {
                previous->next = newCar;
                return true;
            }
            else
            { // If no, do a generic add.
                previous->next = newCar;
                newCar->next = temp;
                return true;
            }
        }
    }
    return false; // if none of the above cases are met, return false.
}
// Removes the specified Car from the list, releases the memory and updates pointers.
// Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
{
    // add your own code
    if (head == nullptr) // if the list is empty, nothing to remove, so return false
    {
        return false;
    }
    else if (aVin == head->vin) // if the Car to be removed is at head, handle accordingly.
    {
        struct Car *temp = head;
        head = head->next; // update head pointer
        delete temp;       // then delete temp
        temp = head;       // set temp the same as head
        return true;
    }
    else
    {
        struct Car *previous = nullptr;
        struct Car *temp = head;
        while (temp != nullptr) // if the Car to be removed is somewhere in the middle or the end
        // then run a loop
        {
            if (aVin == temp->vin) // if Car found, then check if that Car is at the tail or in the middle.
            // update pointers for both scenarios accordingly.
            {
                if (temp->next == nullptr)
                {
                    previous->next = nullptr;
                    delete temp;
                    temp = nullptr;
                    return true;
                }
                else
                {
                    previous->next = temp->next;
                    delete temp;
                    temp = previous->next;
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

// Removes the given Car from the list, releases the memory and updates pointers.
// Return true if it is successfully removed, false otherwise. Note: all Cars with
// the same model and make should be removed from the list.
bool LinkedList::removeByModelAndMake(string model, string make)
{
    // add your own code
    if (head == nullptr) // if empty list, no cars to remove
    {
        // cout << "No cars to remove." << endl;
        return false;
    }
    else
    {
        bool isRemoved = false; // keep a bool counter to check if atleast one car
        // with make and model exists

        struct Car *previous = nullptr;
        struct Car *current = head;
        while (current != nullptr) // traverse through all Cars
        {
            if (model.compare(current->model) == 0 && make.compare(current->make) == 0) // if a match is found, delete the Car
            {
                if (current == head) // if Car is at head
                {
                    head = head->next; // update head and delete current
                    delete current;
                    current = head;
                    isRemoved = true;
                }
                else if (current->next == nullptr) // if Car is at tail
                {
                    previous->next = nullptr; // make previous the new tail and delete current
                    delete current;
                    current = nullptr; // current goes to nullptr as no more Cars in the list
                    isRemoved = true;
                }
                else
                { // else, do a generic remove and update current pointer to the node after the deleted node
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                    isRemoved = true;
                }
            }
            else
            { // if make and model is no the same, keep traversing
                previous = current;
                current = current->next;
            }
        }
        if (isRemoved == true) // if atleast one car is removed, return true
        {
            return true;
        }
        else
        { // else, return false
            cout << "No such Car found.\n";
            return false;
        }
    }
}

// Modifies the data of the given Car. Return true if it modifies successfully and
// false otherwise. Note: after changing a Car model and make, the linked list must still
// maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
    // split newModelAndMake string to get model and make accordingly
    int delimIndex = 0;

    string model = "";
    string make = "";

    delimIndex = newModelAndMake.find(" "); // find the index of " " token that separates model and make using std::find

    model = newModelAndMake.substr(0, delimIndex); // use substring method to get new model and make
    make = newModelAndMake.substr(delimIndex + 1, newModelAndMake.length());
    // add your own code
    if (findCar(aVin) == false) // if Car to update doesn't exist, output error
    {
        // cout << "Car with vin doesn't exist" << endl;
        return false;
    }
    else
    {
        double carPrice = 0.0;
        struct Car *temp = head;
        while (temp != nullptr)
        {
            if (aVin == temp->vin)
            {
                carPrice = temp->price; // if Car found, store its price
                break;
            }
            temp = temp->next;
        }
        removeByVin(aVin);                   // remove that Car
        addCar(model, make, aVin, carPrice); // add it again. This way, the Car with the new model and make gets added
        return true;                         // alphabetically.
    }
    return false;
}

bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
    // add your own code
    if (findCar(aVin) == false)
    {
        cout << "Car is NOT inside the list, cannot change its price.\n";
        return false;
    }
    else
    {
        struct Car *temp = head;
        while (temp != nullptr)
        {
            if (aVin == temp->vin) // if Car is found, update its price
            {
                temp->price = newPrice;
                break;
            }
            temp = temp->next;
        }
        return true;
    }
    return false;
}

// Prints all Cars in the list with the same make.
void LinkedList::printCarListByMake(string make)
{
    // add your own code
    if (head == nullptr)
    {
        cout << "The list in empty\n";
    }
    else
    {
        bool foundMake = false; // bool counter to check if atleast once Car with specified make found

        struct Car *temp = head;
        while (temp != nullptr)
        {
            if (make.compare(temp->make) == 0) // if Car with make found, print it
            {
                foundMake = true;
                cout << left << setw(12) << temp->model
                     << left << setw(12) << temp->make
                     << right << setw(8) << temp->vin
                     << setw(10) << fixed << setprecision(2) << temp->price << "\n";
            }

            temp = temp->next;
        }
        if (foundMake == false)
        {
            cout << "No Cars with the specified make found.\n";
        }
    }
}

// Prints all Cars in the linked list starting from the head node.
void LinkedList::printCarList()
{
    // add your own code
    if (head == nullptr) // if the list is empty, output the same
    {
        cout << "The list is empty\n";
    }
    else
    {
        struct Car *temp = head;

        while (temp != nullptr) // traverse through each Car and print that Car object
        {
            cout << left << setw(12) << temp->model
                 << left << setw(12) << temp->make
                 << right << setw(8) << temp->vin
                 << setw(10) << fixed << setprecision(2) << temp->price << "\n";

            temp = temp->next;
        }
    }
}

/*bool LinkedList::addCar(string model, string make, int vin, double price)
bool LinkedList::addCar(string model, string make, int vin, double price)
{
    if (findCar(vin) == true)
    {
        cout << "Duplicate Car. Not added.\n";
        return false;
    }
    else
    {
        struct Car *newCar = new Car(model, make, vin, price);

        if (head == nullptr)
        {
            head = newCar;
            return true;
        }
        else
        {
            if (make.compare(head->make) == 0)
            {
                if (model.compare(head->model) == 0)
                {
                    if (vin < head->vin)
                    {
                        newCar->next = head;
                        head = newCar;
                        return true;
                    }
                    else
                    {
                        struct Car *previous = nullptr;
                        struct Car *temp = head;
                        while (temp != nullptr)
                        {
                            if (make.compare(temp->make) == 0 && model.compare(temp->model) == 0 && vin > temp->vin)
                            {
                                previous = temp;
                                temp = temp->next;
                            }
                            else
                            {
                                break;
                            }
                            // cout << "Infinite loop." << endl;
                        }
                        if (previous->next == nullptr)
                        {
                            previous->next = newCar;
                            return true;
                        }
                        else
                        {
                            previous->next = newCar;
                            newCar->next = temp;
                            return true;
                        }
                    }
                }
                else if (model.compare(head->model) < 0)
                {
                    newCar->next = head;
                    head = newCar;
                    return true;
                }
                else
                {
                    struct Car *previous = nullptr;
                    struct Car *temp = head;
                    while (temp != nullptr)
                    {
                        if (make.compare(temp->make) == 0 && model.compare(temp->model) > 0)
                        {
                            previous = temp;
                            temp = temp->next;
                        }
                        else
                        {
                            break;
                        }
                        // cout << "Infinite loop." << endl;
                    }
                    if (previous->next == nullptr)
                    {
                        previous->next = newCar;
                        return true;
                    }
                    else
                    {
                        previous->next = newCar;
                        newCar->next = temp;
                        return true;
                    }
                }
            }
            else if (make.compare(head->make) < 0)
            {
                newCar->next = head;
                head = newCar;
                return true;
            }
            else
            {
                struct Car *previous = nullptr;
                struct Car *temp = head;
                while (temp != nullptr)
                {
                    if (make.compare(temp->make) > 0)
                    {
                        previous = temp;
                        temp = temp->next;
                    }
                    else
                    {
                        break;
                    }
                    // cout << "Infinite loop." << endl;
                }
                if (previous->next == nullptr)
                {
                    previous->next = newCar;
                    return true;
                }
                else
                {
                    previous->next = newCar;
                    newCar->next = temp;
                    return true;
                }
            }
        }
        // return false;
    }
}
*/