#include <iostream>

#include "Radar.h"
#include "Position.h"
#include "Display.h"
#include "Hit.h"
#include "TestCase.h"
#include "TrackFile.h"


using namespace std;

/* Global Variables */
int elevationDistance = 1000; // feet
int collisionDistance = 3; // miles
int aboveSeaLevel = 15000; // feet

int main() {

	Display d1;

	Radar radar;

	radar.Initialize();

	cout<<"Generated all aircrafts in a list of hits and tracked aircrafts."<< endl;

	//d1.PrintGrid();



	return 0;
}
