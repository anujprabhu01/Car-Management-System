//************************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// ASU ID: 1225065855
// Name: Anuj Prabhu
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

// include necessary header file here
//---
#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <string>

// using statements go here
using namespace std;

void getArrCityInfo(string oneArrCityInfo, string &arrCityName, double &distance);
int searchCity(City *oneCityArray, int size, string oneCityName);

int main()
{
   int V, E; // number of vertices and edges

   // cout << "Enter number of vertices and edges: " << endl;
   cin >> V >> E;
   cin.ignore(20, '\n');

   // a City array used to store all vertices (Cities) of the graph
   City *cityArray = new City[V];

   // an array used to store all edges of the graph
   Edge *edgeArray = new Edge[E];

   //----

   int i = 0, j = 0; // index for cityArray and edgeArray

   // local variables
   City *city1;
   City *city2;
   // Edge *aNewEdge;
   City tempCity1;
   City tempCity2;
   Edge tempEdge;

   string oneLine;
   string delimeter = "";
   string token = "";
   int pos = -1;
   string arrCityName;
   double distance;

   // cout << "Enter one departure and its arrival city info." << endl;
   getline(cin, oneLine);

   while (oneLine.compare("End") != 0)
   {
      // get one line of the input, extract the first token
      // create a City object if it does not exist in cityArray,
      // insert it inside the cityArray. This will be first vertex of the 'aNewEdge'
      //----
      delimeter = ",";
      pos = oneLine.find(delimeter);
      token = oneLine.substr(0, pos);
      // cout << "flag 2; first vertex: " << token << endl;
      //  city1 = new City(token);
      if (searchCity(cityArray, V, token) == -1)
      {
         // tempCity1 = City(token);
         // city1 = &tempCity1;
         cityArray[i] = City(token);
         city1 = &cityArray[i];
         i++;
      }
      else
      {
         city1 = &cityArray[searchCity(cityArray, V, token)];
      }
      // cout << "flag 9; city1 address: " << city1 << endl;
      //  cout << "flag 9; &tempCity1 address: " << &tempCity1 << endl;
      oneLine.erase(0, pos + delimeter.length());

      // extract the arrival city info. check whether it exists in
      // cityArray or not, if not, create a new City, add it inside.
      // This city will be the second point of the 'aNewEdge'
      //----
      pos = oneLine.find(delimeter);
      while (pos != std::string::npos) // traverse until "," is not found
      {
         token = oneLine.substr(0, pos);
         // cout << "flag 3; arrival info.: " << token << endl;

         if (token == "") // if token is empty, do not process it
         {
            break;
         }
         else
         {
            getArrCityInfo(token, arrCityName, distance);
            // cout << "flag 4; arrCityName: " << arrCityName << endl;
            // cout << "flag 5; distance: " << distance << endl;
            //  city2 = new City(arrCityName);
            if (searchCity(cityArray, V, arrCityName) == -1)
            {
               // tempCity2 = City(arrCityName);
               // city2 = &tempCity2;
               cityArray[i] = City(arrCityName);
               city2 = &cityArray[i];
               i++;
            }
            else
            {
               city2 = &cityArray[searchCity(cityArray, V, arrCityName)];
            }
            // cout << "flag 10; city2 address: " << city2 << endl;
            //  cout << "flag 8; city1: " << city1->cityName << endl;
            //   tempEdge = Edge(city1, city2, distance);
            edgeArray[j] = Edge(city1, city2, distance);
            // edgeArray[j] = *aNewEdge;
            j++;

            oneLine.erase(0, pos + delimeter.length());
            pos = oneLine.find(delimeter);
         }
      }
      // cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
      //   get next line
      getline(cin, oneLine);
   } // repeat until the 'End'

   /*for (int i = 0; i < V; i++)
   {
      cout << "flag 6; cityArray[" << i << "]: " << cityArray[i].cityName << endl;
   }*/

   /*for (int j = 0; j < E; j++)
   {
      cout << "flag 7; edgeArray[" << j << "]: " << endl;
      edgeArray[j].printEdge();
   }*/

   // Create a Graph object by using cityArray and edgeArray
   //----
   Graph *graph = new Graph(V, E, cityArray, edgeArray);

   // Run Kruskal MST algorithm on above graph
   //----
   graph->MST_Kruskal();

   graph->destructor();
}

//****************************************************************
// By giving a string, for example 'Dallas(1456.5)', this function
// extract the arrival city name 'Dallas' and distance '1456.5'
// Note: the delimiter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string &arrCityName, double &distance)
{
   //----
   string delimeter = "(";
   int pos = oneArrCityInfo.find(delimeter);
   string token = oneArrCityInfo.substr(0, pos);
   arrCityName = token; // get arrival city name
   oneArrCityInfo.erase(0, pos + delimeter.length());

   delimeter = ")";
   pos = oneArrCityInfo.find(delimeter);
   token = oneArrCityInfo.substr(0, pos);
   distance = stod(token); // get distance of edge
   oneArrCityInfo.erase(0, pos + delimeter.length());
}

//*********************************************************************
// Given a city name, this function searches cityArray and it return the
// index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCity(City *oneCityArray, int arraySize, string oneCityName)
{
   //---
   for (int i = 0; i < arraySize; i++)
   {
      if (oneCityArray[i].cityName == oneCityName)
      {
         return i;
      }
   }
   return -1;
}
