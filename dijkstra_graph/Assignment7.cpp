//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name: Anuj Prabhu
// ASU ID: 1225065855
// Description: //---- is where you should add your own code
//********************************************************************

// include necessary header file here
//----
#include <string>
#include <iostream>
#include <iomanip>
#include "Graph.h"

// using statements go here
using namespace std;

void getDepartureInfo(string oneLine, string &depAddress, ArrivalList *arrList);
void getArrivalInfo(string oneArrivalInfo, string &arrAddress, double &distance, string &roadCategory); //**optional

int main()
{
   int count; // a variable for number of nodes
   string oneLine, sourceDepAddress;
   string userDepAddress;
   string answer = "yes"; // a variable to decide whether to run Dijkstra multiple times or not

   // cout << "Enter number of departure address: ";
   cin >> count;
   cin.ignore(20, '\n');

   // Create an array called 'departureArr' that holds 'count' number of Departure objects
   //----
   Departure *departureArr = new Departure[count];

   // Initialize departureArr. Note: you will need to initialize each of the instance variable
   // including arrival list
   for (int i = 0; i < count; i++)
   {
      departureArr[i].d = 10000.0 + i;
      departureArr[i].depAddress = "";
      // arrList = new ArrivalList();
      departureArr[i].arrList = new ArrivalList();
      departureArr[i].pi = nullptr;
   }

   // get input line by line and create the departureArr
   for (int i = 0; i < count; i++)
   {
      getline(cin, oneLine);
      //----
      // arrList = new ArrivalList();
      getDepartureInfo(oneLine, sourceDepAddress, departureArr[i].arrList); // do I have to create by pointer first?
      departureArr[i].depAddress = sourceDepAddress;
   }

   MinPriorityQueue *minHeap = new MinPriorityQueue(count);
   for (int i = 0; i < count; i++)
   {
      minHeap->insert(departureArr[i]);
   }

   // create a Graph object
   //----
   Graph *graph = new Graph(count, minHeap);

   // print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
   //----
   graph->printGraph();

   // Next you need to design a sentinel-value controlled while loop base on 'answer'
   // If user answer is 'yes', get departure address, run Dijkstra algorithm, print
   // shortest traveling time and path, then ask the user whether he want to continue or not...
   do
   {
      cout << "Enter departure address:" << endl;
      getline(cin, userDepAddress);
      // cin.ignore(20, '\n');
      if (graph->findOneDeparture(userDepAddress) != -1)
      {
         graph->dijkstra(userDepAddress);
         graph->printDijkstraPath(userDepAddress);
      }
      else
      {
         cout << userDepAddress << " does NOT exist" << endl;
      }
      cout << "\n";
      cout << "Find shortest path for another departure address(yes or no):" << endl;
      getline(cin, answer);
   } while (answer != "no");
   cout << "Program terminate" << endl;
   for (int i = 0; i < count; i++)
   {
      if (departureArr[i].arrList != nullptr)
      {
         delete departureArr[i].arrList;
         // departureArr[i].arrList = nullptr;
      }
   }
   delete[] departureArr;
   if (minHeap != nullptr)
   {
      delete minHeap;
      // minHeap = nullptr;
   }
}

//********************************************************************************
// Give one line in input file, this function extract tokens and get departure address
// and all arrival info.
void getDepartureInfo(string oneLine, string &depAddress, ArrivalList *arrList)
{
   //----
   // Tokenize the line using comma as delimiter
   string delimeter = ",";
   int pos = oneLine.find(delimeter);
   string token = oneLine.substr(0, pos);
   depAddress = token;
   oneLine.erase(0, pos + delimeter.length());

   // Process the rest of the tokens (arrival info)
   pos = oneLine.find(delimeter);
   while (pos != std::string::npos)
   {
      token = oneLine.substr(0, pos);
      if (token != "")
      { // If the token is not empty
         string arrAddress;
         double distance;
         string roadCategory;
         // Extract arrival info from this token
         getArrivalInfo(token, arrAddress, distance, roadCategory);
         // Add the arrival info to the arrival list
         arrList->addArrival(arrAddress, distance, roadCategory);
         oneLine.erase(0, pos + delimeter.length());
         pos = oneLine.find(delimeter);
      }
      else
      {
         break;
      }
   }
}

//******************************************************************************************
// Given such as Y(1803.2/I), this function extracts arrival Address "Y", distance 1803.2
// and roadCategory "I" info. out
void getArrivalInfo(string oneArrivalInfo, string &arrAddress, double &distance, string &roadCategory)
{
   //----
   string delimeter = "(";
   int pos = oneArrivalInfo.find(delimeter);
   string token = oneArrivalInfo.substr(0, pos);
   arrAddress = token;
   oneArrivalInfo.erase(0, pos + delimeter.length());

   delimeter = "/";
   pos = oneArrivalInfo.find(delimeter);
   token = oneArrivalInfo.substr(0, pos);
   distance = stod(token);
   oneArrivalInfo.erase(0, pos + delimeter.length());

   delimeter = ")";
   pos = oneArrivalInfo.find(delimeter);
   token = oneArrivalInfo.substr(0, pos);
   roadCategory = token;
   oneArrivalInfo.erase(0, pos + delimeter.length());
}