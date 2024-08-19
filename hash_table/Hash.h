// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

// only include necessary header file here
//----
#include "LinkedList.h"
#include <cstdlib>

// using statements go here
using namespace std;

class Hash
{
private:
   LinkedList *hashTable; // hashTable is a one-dimensional array of LinkedList
   int m;                 // slots number of the hash table
public:
   Hash(int size);
   ~Hash();
   bool hashSearch(string model, string make, int vin);
   bool hashInsert(string model, string make, int vin, double price);
   bool hashDelete(string model, string make, int vin);
   int hashLoadFactor();
   void hashDisplay();
   int getVin(string carInfo);
   int hashFunction(string key);
};

// constructor
Hash::Hash(int size)
{
   //----
   m = size;                      // initialize m to given size
   hashTable = new LinkedList[m]; // initialize hash table as a 1D array of linked lists
}

// Destructor
Hash::~Hash()
{
   //----
   for (int i = 0; i < m; i++)
   {
      hashTable[i].~LinkedList(); // delete and free memory for every linked list inside the hash table
   }
   delete[] hashTable; // delete and free the memory allocated for hash table
}

// This function searches for a key inside the hash table and
// return true if it is found and false otherwise
// Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin)
{
   string key = model + make + to_string(vin); // key is combination of model, make, and vin
   int index = hashFunction(key);              // get index by hashing key

   bool success = hashTable[index].searchCar(vin); // search for car

   if (success == true) // if search is successful
   {
      cout << "\n"
           << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is found inside the hash table." << endl;
      return true;
   }
   else // if search is unsuccessful
   {
      cout << "\n"
           << left
           << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is NOT found inside the hash table." << endl;
      return false;
   }
}

// hashInsert inserts a Car with the relevant info. into the hashTable.
// it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price)
{
   //----
   string key = model + make + to_string(vin); // key is combination of model, make, and vin
   int index = hashFunction(key);              // get index by hashing key

   // hashTable[index] = new LinkedList();

   bool success = hashTable[index].insertCar(model, make, vin, price); // insert car

   if (success) // if insert is successful
   {
      // cout << "insertion successful" << endl;
      return true;
   }
   // cout << "insertion failed" << endl;
   return false;
}

// hashDelete deletes a Car with the relevant key from the hashTable.
// it returns true if it is deleted successfully and false otherwise
// Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin)
{
   string key = model + make + to_string(vin); // get key by combining model, make, and vin
   int index = hashFunction(key);              // get index by hashing key

   bool success = hashTable[index].deleteCar(model, make, vin); // delete car at index

   if (success) // if deletion successful, print success message
   {
      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is found inside the hash table." << endl;

      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is deleted from hash table." << endl;
      return true;
   }
   else // else, print failure message
   {
      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is NOT found inside the hash table." << endl;

      cout << "\n";
      cout << setw(18) << model
           << setw(18) << make
           << setw(8) << vin
           << " is NOT deleted from hash table." << endl;
      return false;
   }
}

// This function computes your hash table real load factor
// it is the longest linked list size
int Hash::hashLoadFactor()
{
   //----
   int maxSize = hashTable[0].getSize(); // set longest linked list to be first linked list

   for (int i = 1; i < m; i++)
   {
      if (hashTable[i].getSize() > maxSize) // if any other linked list found to be longer,
      {
         maxSize = hashTable[i].getSize(); // set maxSize to that linked list's size
      }
   }
   return maxSize; // return maxSize
}

// This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
   //----
   for (int i = 0; i < m; i++) // for every linked list in hash table
   {
      if (hashTable[i].getSize() == 0) // if linked list empty
      {
         cout << "" << endl;
         cout << "HashTable[" << i << "] is empty, size = 0" << endl;
      }
      else // else
      {
         cout << "" << endl;
         cout << "HashTable[" << i << "], size = " << hashTable[i].getSize() << endl;
         hashTable[i].displayList();
      }
   }
}

// This is the hash function you need to design. Given a
// string key, the function should return the slot number
// where we will hash the key to
int Hash::hashFunction(string key) // key is combination of model, make, amd vin
{
   int sumAsciiValues, index;

   sumAsciiValues = int(key[0]) * 31; // convert each character of key to its ascii value and multiply that by a prime number
   for (int i = 1; i < key.length(); i++)
   {
      sumAsciiValues = sumAsciiValues + (int(key[i]) * 31); // sum ascii value of every character * 31 for all characters in key
   }

   index = sumAsciiValues % m; // get index by modding sum by m
   return index;
}

// int Hash::hashFunction(string key)
// {
//    //----
//    int vin = 0;
//    int index = 0;
//    int resultOfSub = 0;

//    vin = getVin(key);

//    string vinStr = to_string(vin);

//    if (vinStr.length() < 2)
//    {
//       resultOfSub = vin;
//    }

//    else
//    {
//       resultOfSub = vinStr[0] - '0';
//       for (int i = 1; i < vinStr.length(); i++)
//       {
//          resultOfSub -= (vinStr[i] - '0');
//       }
//    }
//    resultOfSub = abs(resultOfSub);

//    index = resultOfSub % m;

//    return index;
// }

int Hash::getVin(string carInfo) // get vin from key by modifying model function given by Professor Feng
{
   string model, make = "";
   int vin = -999;

   string delimiter = ",";
   int pos = carInfo.find(delimiter);
   string token = carInfo.substr(0, pos);
   model = token;
   carInfo.erase(0, pos + delimiter.length());

   pos = carInfo.find(delimiter);
   token = carInfo.substr(0, pos);
   make = token;
   carInfo.erase(0, pos + delimiter.length());

   pos = carInfo.find(delimiter);
   token = carInfo.substr(0, pos);
   vin = stoi(token);
   carInfo.erase(0, pos + delimiter.length());

   return vin;
}

// bool Hash::hashDelete(string model, string make, int vin)
// {
//    string key = model + "," + make + "," + to_string(vin);
//    int index = hashFunction(key);

//    bool successfulSearch = hashTable[index].searchCar(vin);

//    // bool success = hashTable[index].deleteCar(vin);

//    if (successfulSearch)
//    {
//       cout << "\n";
//       cout << setw(18) << model
//            << setw(18) << make
//            << setw(8) << vin
//            << " is found inside the hash table." << endl;

//       bool successfulDelete = hashTable[index].deleteCar(vin);
//       if (successfulDelete)
//       {
//          cout << "\n";
//          cout << setw(18) << model
//               << setw(18) << make
//               << setw(8) << vin
//               << " is deleted from hash table." << endl;
//          return true;
//       }
//       else
//       {
//          cout << "\n";
//          cout << setw(18) << model
//               << setw(18) << make
//               << setw(8) << vin
//               << " is NOT deleted from hash table." << endl;
//          return false;
//       }
//    }
//    else
//    {
//       cout << "\n";
//       cout << setw(18) << model
//            << setw(18) << make
//            << setw(8) << vin
//            << " is NOT found inside the hash table." << endl;

//       cout << "\n";
//       cout << setw(18) << model
//            << setw(18) << make
//            << setw(8) << vin
//            << " is NOT deleted from hash table." << endl;
//       return false;
//    }
// }