#include <iostream>

#include "Radar.h"

using namespace std;

/* Global Variables */
// Convention: km/h
double elevationDistance = 0.3048; // 1000 feet
double collisionDistance = 4.82803; // 3 miles
double aircraftDimension[3] = {30.48, 7.62, 4.572}; // Converted to km (100 000 feet, 25 000 feet, 15 000 feet)

int main() {
	cout<<"Test";
	Radar();
	return 0;
}
