// ASU CSE310 Spring 2024 Assignment #1
// Name: Anuj Prabhu
// ASU ID: 1225065855
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

// import statements go here
#include <iostream>
#include <string>
#include "LinkedList.h"

// using statements go here
using namespace std;

// forward declarations go here
void printMenu();

int main()
{
   // local variables, can be accessed anywhere from the main method
   char input1 = 'Z';
   // string inputInfo;
   string model, make, newModelAndMake;
   int vin;
   double price;
   string makeToDisplay = "";
   bool successA = false;
   bool successC = false;
   bool successF = false;
   bool successS = false;

   // instantiate a Linked List object
   LinkedList *list1 = new LinkedList();

   printMenu();

   do // ask for user input
   {
      cout << "\nWhat action would you like to perform?\n";
      cin.get(input1);
      input1 = toupper(input1); // change it to upper case
      cin.ignore(20, '\n');     // flush the buffer

      // matches one of the following cases
      switch (input1)
      {
      case 'A': // Add the Car
         cout << "Please enter the Car information:\n";
         cout << "Enter Car Model:\n";
         getline(cin, model);
         cout << "Enter Car Make:\n";
         getline(cin, make);
         cout << "Enter Car Vin:\n";
         cin >> vin;

         cout << "Enter Car Price:\n";
         cin >> price;
         cin.ignore(20, '\n'); // flush the buffer

         // add your own code
         successA = list1->addCar(model, make, vin, price);

         if (successA == true) // if successful add
            cout << "Car \"" << model << " " << make << "\" is added\n";
         else // if unsuccessful add
            cout << "Car \"" << model << " " << make << "\" is NOT added\n";
         break;

      case 'C': // Change Car model and make
         cout << "Please enter the Car vin which you want to change the model and make:\n";
         cin >> vin;
         cin.ignore(20, '\n'); // flush the buffer
         cout << "\nPlease enter the new model and make: ";
         getline(cin, newModelAndMake);

         // add your own code to finish this case
         successC = list1->changeCarInfo(vin, newModelAndMake);

         if (successC == true) // if successful change
         {
            cout << "Car VIN #: " << vin << " model and make was changed\n";
         }
         else
         {
            cout << "Car is NOT inside the list, cannot change Car make and model.\n";
            cout << "\nCar VIN #: " << vin << " does not exist\n";
         }

         break;

      case 'D': // Display all Cars
         // add your own code
         list1->printCarList(); // call printCarList()

         break;

      case 'E': // Display Cars by make
         cout << "\nPlease enter Car make which you want to display:\n";
         // add your own code
         cin >> makeToDisplay; // get input from user
         cin.ignore(20, '\n'); // flush the buffer
         list1->printCarListByMake(makeToDisplay);

         break;

      case 'F': // Find a Car
         cout << "\nPlease enter the car VIN you want to search:\n";
         cin >> vin;
         cin.ignore(20, '\n'); // flush the buffer

         // add your own code
         successF = list1->findCar(vin);

         if (successF == true) // if successful find
         {
            cout << "Car with VIN #: " << vin << " was found\n";
         }
         else
         {
            cout << "Car with VIN #: " << vin << " was NOT found\n";
         }

         break;

      case 'P': // Update a Car price
         cout << "\nPlease enter the Car VIN you want to update the price:\n";
         cin >> vin;
         cin.ignore(20, '\n'); // flush the buffer

         // add your own code
         if (list1->findCar(vin) == false) // if Car is not in list
         {
            cout << "Car with VIN #: " << vin << " does NOT exist\n";
         }
         else // else, get new price from user
         {
            double updatedPrice = 0.0;
            cout << "\nPlease enter the new price:\n";
            cin >> updatedPrice;
            cin.ignore(20, '\n'); // flush the buffer

            list1->updateCarPrice(vin, updatedPrice);
            cout << "Car with VIN #: " << vin << " price was updated\n";
         }

         break;

      case 'R': // Remove a Car from the list by VIN
         cout << "\nPlease enter the Car VIN to remove:\n";
         cin >> vin;
         cin.ignore(20, '\n'); // flush the buffer

         // add your own code
         if (list1->findCar(vin) == true)
         {
            list1->removeByVin(vin); // if Car found, remove it and output success message
            cout << "Car with VIN #: " << vin << " was removed\n";
         }
         else
         {
            cout << "Car with VIN #: " << vin << " does NOT exist\n";
         }

         break;

      case 'S': // Remove a Car from the list by model and make
         cout << "Please enter Car model you want to remove:\n";
         getline(cin, model);
         cout << "Please enter Car make you want to remove:\n";
         getline(cin, make);

         // add your own code
         successS = list1->removeByModelAndMake(model, make); // call removeByModelAndMake()
         if (successS == false)                               // if remove is unsuccessul
         {
            cout << "Car: " << make << " " << model << " does NOT exist\n";
         }
         else
         {
            cout << "Car: " << make << " " << model << " was removed\n";
         }

         break;

      case 'Q':        // Quit
         delete list1; // if users wants to terminal program, call destructor and delete the list
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

/** The method printMenu displays the menu to a user**/
void printMenu()
{
   cout << "Choice\t\tAction\n";
   cout << "------\t\t------\n";
   cout << "A\t\tAdd A Car\n";
   cout << "C\t\tChange A Car Model and Make\n";
   cout << "D\t\tDisplay All Cars\n";
   cout << "E\t\tDisplay Cars by Make\n";
   cout << "F\t\tFind A Car\n";
   cout << "P\t\tUpdate Car price\n";
   cout << "R\t\tRemove Car by VIN\n";
   cout << "S\t\tRemove Car by Model and Make\n";
   cout << "Q\t\tQuit\n";
   cout << "?\t\tDisplay Help\n\n";
}