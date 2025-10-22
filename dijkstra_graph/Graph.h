//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: This is the header file that defines a weighted directed graph. It consists of functions that define graph operations like
// initializing source path, relaxing the edges between two vertices, and more.
//********************************************************************

// include necessary header file here
//----
#include "MinPriorityQueue.h"
#include <string>
#include <iostream>
#include <iomanip>

// using statements go here
using namespace std;

// Graph class
class Graph
{
private:
   int numOfNode;
   MinPriorityQueue *departureHeap; // adjacency list of the graph, it is a min-heap
                                    // of Departure objects based on d value
   // int tempNumOfNodes; //number of nodes the heap

public:
   Graph(int numOfNode, MinPriorityQueue *departureHeap);
   ~Graph();
   MinPriorityQueue *getDepartureHeap();
   void printGraph();
   int speed(Arrival *arrivalNode);
   double weight(Departure u, Departure v);
   void initialize_single_source(string sourceDepAddress);
   void relax(Departure u, Departure v);
   int findOneDeparture(string aDepAddress);
   void dijkstra(string sourceDepAddress);
   void printDijkstraPath(string sourceDepAddress);

   // add any auxiliary functions here in case you need them
   //----
};

//*******************************************************************
// Constructor
Graph::Graph(int numOfNode, MinPriorityQueue *departureHeap)
{
   //----
   this->numOfNode = numOfNode;
   this->departureHeap = departureHeap; // Will I build a MinPriorityQueue in main method and pass that to the constructor here?
   // this->tempNumOfNodes = numOfNode;
}

//*******************************************************************
// Destructor Graph::~Graph()
Graph::~Graph()
{
   departureHeap->~MinPriorityQueue();
   numOfNode = 0;
   // tempNumOfNodes = 0;
}

MinPriorityQueue *Graph::getDepartureHeap()
{
   return departureHeap; // return statement that returns departure heap
}

//*******************************************************************
// void printGraph();
// This function prints the graph. It traverse through the vertex list,
// then for each vertex, it print its adjacent list from head to tail.
void Graph::printGraph()
{
   if (numOfNode == 0) // if empty graph
   {
      cout << "Graph is empty. There are 0 nodes (vertices) in graph's adjacency list." << endl;
   }
   else
   {
      departureHeap->printHeap();
   }
}

int Graph::speed(Arrival *arrivalNode)
{
   int speed = 0;
   string roadCategory = arrivalNode->roadCategory; // road category of arrival node
   if (roadCategory == "I")                         // if road category is Interstate
   {
      speed = 65;
   }
   else if (roadCategory == "A") // if road category is Arterial
   {
      speed = 55;
   }
   else if (roadCategory == "C") // if road category is Connector
   {
      speed = 45;
   }
   else if (roadCategory == "L") // if road category is Local roads
   {
      speed = 25;
   }
   else // else none
   {
      cout << "road category is weird! speed = -1" << endl;
      speed = -1;
   }
   return speed;
}

double Graph::weight(Departure u, Departure v) // this function helps calculater the weigths using the time = distance/speed.
{
   double weight = 0.0;

   if (u.arrList->findArrival(v.depAddress) != nullptr)
   {
      weight = ((double)u.arrList->findArrival(v.depAddress)->distance) / ((double)speed(u.arrList->findArrival(v.depAddress)));
      // time = distance / speed.
   }
   else
   {
      cout << "arrival object (v) not found! weight = -1" << endl;
      weight = -1;
   }
   return weight;
}

// According to above class definition, define all other functions accordingly
//----
void Graph::initialize_single_source(string sourceDepAddress) // this function initilizzes
{
   for (int i = 0; i < numOfNode; i++)
   {
      if (departureHeap->getDepartureArr()[i].depAddress == sourceDepAddress)
      {
         departureHeap->getDepartureArr()[i].d = 0;
         departureHeap->getDepartureArr()[i].pi = nullptr;
      }
      else
      {
         departureHeap->getDepartureArr()[i].d = 10000 + i; // infinity is represented by 50000
         departureHeap->getDepartureArr()[i].pi = nullptr;
      }
   }
   departureHeap->build_min_heap(); // need to build geap to ensure proper order
}

// this method takes two departure objects and updates the .d and .pi of the V departure obj if necessary
void Graph::relax(Departure u, Departure v)
{
   int vInd = findOneDeparture(v.depAddress);
   Departure *uPtr;
   uPtr->d = u.d;
   uPtr->arrList = u.arrList;
   uPtr->depAddress = u.depAddress;
   if (v.d > u.d + weight(u, v))
   {                            // the new total time is better than the previous one.
      v.d = u.d + weight(u, v); // try uPtr
      v.pi = uPtr;
      departureHeap->decreaseKey(vInd, v); // ensuring order
   }
}

int Graph::findOneDeparture(string aDepAddress)
{
   return departureHeap->isFound(aDepAddress); // this func. returns -1 if ntg found.
}

void Graph::dijkstra(string sourceDepAddress)
{

   initialize_single_source(sourceDepAddress); // initializing according to the source dep address.

   // loop through the list, extract min, and perform relax operations on it.
   while (departureHeap->getSize() != 0) // departureHeap->getSize()
   {
      Departure u = departureHeap->getHeapMin();
      departureHeap->extractHeapMin();
      // numOfNode--;
      Arrival *temp = u.arrList->getHead();
      while (temp != nullptr)
      {
         int index = departureHeap->isFound(temp->arrAddress);
         if (index != -1)
         {
            relax(u, departureHeap->getDepartureArr()[index]); // perform relax on the two dapartures
         }
         temp = temp->next;
      }
   }
   // delete Q;
   //}
   // else
   //{
   // cout << sourceDepAddress << " does NOT exist" << endl;
   //}
}

// void Graph::printDijkstraPath(string sourceDepAddress)
// {
//    dijkstra(sourceDepAddress);
//    departureHeap->setSize(tempNumOfNodes);
//    departureHeap->build_min_heap();
//    int index = departureHeap->isFound(sourceDepAddress);
//    if (index == -1)
//    {
//       cout << "departure address does not exist inside the departure heap!" << endl;
//    }
//    else
//    {
//       cout << "Departure address: " << sourceDepAddress << endl;
//       cout << "\n";
//       cout << left;
//       cout << setw(15) << "Arrival"
//            << setw(24) << "Shortest Time(h)"
//            << "Shortest Path" << endl;

//       Departure u = departureHeap->getDepartureArr()[index];
//       Arrival *temp = u.arrList->getHead();
//       while (temp != nullptr)
//       {
//          // get all needed info here
//          // shortest time
//          int indexArr = departureHeap->isFound(temp->arrAddress);
//          Departure v = departureHeap->getDepartureArr()[indexArr];
//          int count = 0;
//          // double shortestTime = 0.0;

//          while (v.pi != nullptr)
//          {
//             // shortestTime += v.d;
//             count++;

//             piTemp.arrList = v.pi->arrList;
//             piTemp.d = v.pi->d;
//             piTemp.depAddress = v.pi->depAddress;
//             piTemp.pi = v.pi->pi;
//             v = piTemp;
//          }

//          Departure *pathArr = new Departure[count];
//          indexArr = departureHeap->isFound(temp->arrAddress);
//          v = departureHeap->getDepartureArr()[indexArr];
//          int i = 0;
//          while (v != NULL && i < count)
//          {
//             pathArr[i] = v;
//             Departure piTemp2;
//             piTemp2.arrList = v.pi->arrList;
//             piTemp2.d = v.pi->d;
//             piTemp2.depAddress = v.pi->depAddress;
//             piTemp2.pi = v.pi->pi;
//             v = piTemp2;
//             i++;
//          }
//          // print here
//          string path = "";
//          for (int i = count - 1; i >= 1; i--)
//          {
//             path = path + pathArr[i].depAddress + "->";
//          }
//          path += pathArr[0].depAddress;

//          indexArr = departureHeap->isFound(temp->arrAddress);
//          v = departureHeap->getDepartureArr()[indexArr];

//          cout << left;
//          cout << setw(15) << temp->arrAddress
//               << setw(24) << setprecision(2) << v.d
//               << path << endl;
//          delete[] pathArr;
//       }
//    }
// }

void Graph::printDijkstraPath(string sourceDepAddress)
{
   // dijkstra(sourceDepAddress);
   departureHeap->setSize(numOfNode); //,manually updating size
   departureHeap->build_min_heap();
   // dijkstra(sourceDepAddress);

   // int index = departureHeap->isFound(sourceDepAddress);
   //  if (index != -1)
   //{
   cout << "Print the Dijkstra algorithm running result" << endl;
   cout << "\n";
   cout << "Departure address: " << sourceDepAddress << endl;
   cout << "\n";
   cout << left;
   cout << setw(15) << "Arrival"
        << setw(24) << "Shortest Time(h)"
        << "Shortest Path" << endl;

   string arrAddress = "";
   double shortestTime = 0.0;
   string path = "";
   // looping thorugh the departure list, getting the root and printing it out.
   while (departureHeap->getSize() != 0)
   {
      Departure u = departureHeap->getHeapMin();
      departureHeap->extractHeapMin();

      arrAddress = u.depAddress;
      shortestTime = u.d;

      Departure piTemp;
      while (u.pi != nullptr)
      {
         path = u.depAddress + string("->") + path;
         piTemp.arrList = u.pi->arrList;
         piTemp.d = u.pi->d;
         piTemp.depAddress = u.pi->depAddress;
         piTemp.pi = u.pi->pi;
         u = piTemp;
      }
      path = u.depAddress + string("->") + path;
      if (path != "")
      {
         path = path.substr(0, path.length() - 2);
      }
      else
      {
         path = "None exist";
      }
      cout << left;
      cout << setw(15) << arrAddress
           << setw(24) << setprecision(2) << shortestTime
           << path << endl;
   }
   //}
   // else
   //{
   // cout << sourceDepAddress << " does NOT exist" << endl;
   //}
}