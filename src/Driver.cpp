#include <iostream>

#include "Radar.h"

using namespace std;

/* Global Variables */
int elevationDistance = 1000; // feet
int collisionDistance = 3; // miles
int aircraftDimension[4] = {100, 100, 25000, 15000}; // {miles, miles, feet, feet}
int aboveSeaLevel = 15000; // feet


int main() {
	Radar radar;

	radar.Initialize();
	cout<<"Generated all aircrafts in a list of hits.";
	return 0;
}
