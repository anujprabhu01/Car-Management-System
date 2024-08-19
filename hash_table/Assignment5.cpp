// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.
My hash function gets each character of key one by one, coverts it to its ascii value, and multiplies that by a prime number 31.
Every time, this value is added to a running sum. At the end, the function gets hash table index by modding running sum by m.
I get input Car objects key by doing a simple string concatenation over model, make, and vin.

//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
Yes, my hash function performed well. The performance ration was always < 2.0.
performance ratio is: 1.88; longest linked list size: 6
performance ratio is: 1.66; longest linked list size: 9
performance ratio is: 1.75; longest linked list size: 9
performance ratio is: 1.69; longest linked list size: 8
performance ratio is: 1.83; longest linked list size: 8
performance ratio is: 1.44; longest linked list size: 25
performance ratio is: 1.48; longest linked list size: 25


//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
If I were to change my hash function to reduce number of collisions, I would make sure Im not multiplying the ascii values of my "key"
characters by 2^(anything) or 10^(anything). Moreover, I would make sure to multiply them by prime numbers rather, or mod them by prime numbers.
Lastly, I would try to near simple uniform hasing by exploiting order of VINs to my advantage, because each VIN is unique based on the order
of its digits.
********************************************************************************/

// import statements go here
#include "Hash.h"
#include <sstream>
#include <iostream>
// #include <string>
//  #include <iomanip>

// using statements go here
using namespace std;

// forward declarations for functions go here
void getKey(string oneLine, string &command, string &model, string &make, int &vin);
void getCarInfo(string oneLine, string &model, string &make, int &vin, double &price);

int main()
{
   int size = 0;
   int numOfCommand = 0;
   string model, make;
   int vin;
   double price;

   // declare any other necessary variables here
   //----
   string input;
   string command;
   int numCars = 0;
   double idealLoadFactor;
   double actualLoadFactor;
   double performanceRatio;
   bool successInsert, successDelete;

   cout << "Enter the size of the hash table: ";
   cin >> size; // get size from user
   cin.ignore(20, '\n');
   // cout << "size retrieved" << endl;

   // Instantiate the hash table with the relevant number of slots
   Hash *hashTable = new Hash(size);
   // cout << "hash table declared and initialized" << endl;

   // do
   //{
   //  use this do..while loop to repeatly get one line Car info. and extract tokens
   //  create one Car object and insert it inside the hashTable until seeing the message
   //"InsertionEnd" to terminate
   //----
   //----
   //}
   while (getline(cin, input) && input != "InsertionEnd") // get each line; loop till that line is not "InsertionEnd"
   {
      // cout << "newline character" << endl;
      getCarInfo(input, model, make, vin, price);                     // tokenize input
      successInsert = hashTable->hashInsert(model, make, vin, price); // pass tokens to insert function
      if (successInsert == true)                                      // if insert is successful
      {
         numCars++; // increment counter that keeps track of number of cars inserted in hash table
      }
   }

   // cout << "\nEnter number of commands: "; //***need to comment out in submitting
   cin >> numOfCommand; // get number of commands
   cin.ignore(20, '\n');

   for (int i = 0; i < numOfCommand; i++) // loop till all commands are extracted and implemented on
   {
      // get one line command, extract the first token, if only one token
      getline(cin, input);                      // get input
      getKey(input, command, model, make, vin); // tokenize input
      // pass tokens to functions
      if (command.compare("hashDisplay") == 0)
      {
         //----
         hashTable->hashDisplay();
      }
      else // more than one tokens, check the command name, extract the remaining tokens
      {
         //----
         //----
         if (command.compare("hashSearch") == 0)
         {
            //----
            hashTable->hashSearch(model, make, vin);
         }
         else if (command.compare("hashDelete") == 0)
         {
            //----
            successDelete = hashTable->hashDelete(model, make, vin);
            if (successDelete == true)
            {
               numCars--;
            }
         }
         else if (command.compare("hashLoadFactor") == 0)
         {
            //----
            idealLoadFactor = (double)numCars / size; // calculate ideal load factor by doing n/m
            actualLoadFactor = hashTable->hashLoadFactor();

            performanceRatio = (double)actualLoadFactor / idealLoadFactor; // calculate perfomance ratio by dividing actual/ideal load factor

            cout << fixed << setprecision(2);
            cout << "" << endl;
            cout << "The ideal load factor is: " << idealLoadFactor << endl;
            cout << "My hash table real load factor is: " << actualLoadFactor << endl;
            cout << "My hash table performance ratio is: " << performanceRatio << endl;
         }
         else
         {
            cout << "Invalid command" << endl;
         }
      }
   }                 // end for loop
   delete hashTable; // free memory allocated for hash table
   return 0;
}

//****************************************************************************************
// Given one line, this function extracts the model, make, vin info. of a Car
// This function is completed and given here as a study guide for extracting tokens
void getKey(string oneLine, string &command, string &model, string &make, int &vin)
{
   string delimiter = ",";
   int pos = oneLine.find(delimiter);
   if (pos != std::string::npos)
   {
      string token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      model = token;
      oneLine.erase(0, pos + delimiter.length());

      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      make = token;
      oneLine.erase(0, pos + delimiter.length());

      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      vin = stoi(token);
      oneLine.erase(0, pos + delimiter.length());
   }
   else
   {
      command = oneLine;
      model = "";
      make = "";
      vin = -999;
   }
}

// modified implementation of getKey() to tokenize input to pass to insert car method
void getCarInfo(string oneLine, string &model, string &make, int &vin, double &price)
{
   string delimiter = ",";
   int pos = oneLine.find(delimiter);
   string token = oneLine.substr(0, pos);
   model = token;
   oneLine.erase(0, pos + delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   make = token;
   oneLine.erase(0, pos + delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   vin = stoi(token);
   oneLine.erase(0, pos + delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   price = stod(token);
   oneLine.erase(0, pos + delimiter.length());
}