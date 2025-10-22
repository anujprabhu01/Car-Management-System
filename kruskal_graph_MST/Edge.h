//******************************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Name of Author: Anuj Prabhu
// ASU ID: 1225065855
// Description: this header file defines an edge in the graph. Each edge
//              has 3 attributes, namely two Cities and the distance between them
//*******************************************************************************
// import statements go here
#include <iostream>
#include <iomanip>
#include <string>

// using statements go here
using namespace std;

// City represents one vertex of the graph
struct City
{
   string cityName;
   int rank;
   struct City *parent;

   // constructor
   City(string name) // City overloaded constructor
   {
      cityName = name;
      rank = 0;
      parent = nullptr;
   }

   // default constructor. C++ don't provide one, need it here.
   City() // City default constructor
   {
      cityName = "";
      rank = 0;
      parent = nullptr;
   }
};

// class Edge represents one edge of the graph which connects two City objects
class Edge
{
private:
   struct City *city1;
   struct City *city2;
   double distance; // distance between city1 and ciy2; weight of the edge

public:
   Edge(City *cityOne, City *cityTwo, double distanceGiven);
   Edge(); // default constructor
   ~Edge();
   City *getCity1();
   void setCity1(City *city1);
   City *getCity2();
   void setCity2(City *city2);
   double getDistance();
   void setDistance(double distance);
   void printEdge();
};

// finish each function according to above definition
//----
Edge::Edge(City *cityOne, City *cityTwo, double distanceGiven)
{
   city1 = cityOne;
   city2 = cityTwo;
   distance = distanceGiven;
}

Edge::Edge() // edge default constructor
{
   city1 = nullptr;
   city2 = nullptr;
   distance = 0.0;
}

Edge::~Edge() // edge destructor
{
   city1 = nullptr;
   city2 = nullptr;
   distance = 0.0;
}

// getter and setter functions
City *Edge::getCity1()
{
   return city1;
}

void Edge::setCity1(City *city1)
{
   this->city1 = city1;
}

City *Edge::getCity2()
{
   return city2;
}

void Edge::setCity2(City *city2)
{
   this->city2 = city2;
}

double Edge::getDistance()
{
   return distance;
}

void Edge::setDistance(double distance)
{
   this->distance = distance;
}

void Edge::printEdge() // print edge
{
   cout << left;
   cout << setw(15) << city1->cityName
        << setw(8) << "<--->"
        << setw(15) << city2->cityName
        << setw(3) << " = "
        << setw(8) << right << fixed << setprecision(2) << getDistance()
        << endl;
}
