//********************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: This is the header file that defines an undirected graph
//              with an array of vertice and edges
//********************************************************************

// include necessary header file here
//----
#include "Edge.h"
#include <iomanip>
#include <iostream>
#include <string>

// using statements go here
using namespace std;

class Graph
{
private:
   int V, E;      // number of vertice and edges in the graph
   City *cityArr; // an array of City objects
   Edge *edgeArr; // an array of Edge objects

public:
   Graph(int numOfCities, int numOfEdges, City *cityArray, Edge *edgeArray);
   void destructor();
   void make_set(City *aCity);
   City *find_set(City *aCity);
   void link(City *aCity, City *bCity);
   void Union(City *aCity, City *bCity);

   // add any auxiliary functions in case you need them
   int partition(int start, int end);  // quick sort partition
   void quickSort(int start, int end); // quick sort
   void sortEdges();

   void MST_Kruskal();
};

// finish each function according to above definition
//----
Graph::Graph(int numOfCities, int numOfEdges, City *cityArray, Edge *edgeArray)
{
   V = numOfCities;
   E = numOfEdges;
   cityArr = cityArray;
   edgeArr = edgeArray;
}

void Graph::destructor()
{
   V = 0;
   E = 0;
   delete[] cityArr; // delete memory allocated to city array
   delete[] edgeArr; // delete memory allocated to edge array
}

// make empty set with aCity in it
void Graph::make_set(City *aCity)
{
   aCity->parent = aCity;
   aCity->rank = 0;
}

// find representative the set aCity is in
City *Graph::find_set(City *aCity)
{
   if (aCity != aCity->parent) // aCity is not equal to its parent
   {
      aCity->parent = find_set(aCity->parent); // traverse upwards till aCity equals its parent
   }
   return aCity->parent;
}

// link aCity set and bCity set
void Graph::link(City *aCity, City *bCity)
{
   if (aCity->rank > bCity->rank) // compare ranks and set element with higher rank as the parent
   {
      bCity->parent = aCity;
   }
   else if (aCity->rank < bCity->rank)
   {
      aCity->parent = bCity;
   }
   else
   {
      bCity->rank = bCity->rank + 1;
      aCity->parent = bCity;
   }
}

void Graph::Union(City *aCity, City *bCity)
{
   link(find_set(aCity), find_set(bCity)); // link representatives of aCity set and bCity set
}

int Graph::partition(int start, int end)
{
   double pivot = edgeArr[end].getDistance(); // select pivot as last element of edgeArray
   int i = start - 1;
   for (int j = start; j <= end - 1; j++)
   {
      if (edgeArr[j].getDistance() <= pivot)
      {
         i++;
         Edge temp = edgeArr[i]; // swap edgeArr[i] and edgeArr[j] whenever edgeArr[j] <= pivot
         edgeArr[i] = edgeArr[j];
         edgeArr[j] = temp;
      }
   }
   Edge tempEdge = edgeArr[i + 1];
   edgeArr[i + 1] = edgeArr[end];
   edgeArr[end] = tempEdge;

   return i + 1;
}

void Graph::quickSort(int start, int end)
{
   if (start >= end)
   {
      // do nothing
   }
   else // if start < end, then call quicksort on both subarrays
   {
      int parVal = partition(start, end); // do partition
      quickSort(start, parVal - 1);       // sort left subarray
      quickSort(parVal + 1, end);         // sort right subarray
   }
}

void Graph::sortEdges()
{
   // cout << "flag 10; number of edges: " << E << endl;
   quickSort(0, E - 1); // call quicksort on 0, E-1 (last index)
   // cout << "flag 11" << endl;
}

//*******************************************************************
// This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n"
        << endl;

   double totalDistance = 0.0;

   for (int i = 0; i < V; i++)
   {
      make_set(&cityArr[i]); // make set for every city in cityArr
   }
   // cout << "flag 0; make_set happening correctly" << endl;
   sortEdges(); // sort edges of edgeArr in increasing order
   // cout << "flag 1; sortEdges() happening correctly" << endl;

   for (int i = 0; i < E; i++)
   {
      if (find_set(edgeArr[i].getCity1())->cityName != find_set(edgeArr[i].getCity2())->cityName)
      {
         totalDistance += edgeArr[i].getDistance(); // update total distance
         edgeArr[i].printEdge();                    // print each edge that is selected to be safe
         Union(edgeArr[i].getCity1(), edgeArr[i].getCity2());
      }
   }

   cout << "=================================================" << endl;
   cout << "Total Distance: " << totalDistance << endl;
}