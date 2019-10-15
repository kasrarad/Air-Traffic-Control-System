#include <iostream>

#include "Radar.h"
#include "Display.h"


using namespace std;

int main() {

	Display d1;

	Radar radar;

	radar.Initialize();

	cout<<"Generated all aircrafts in a list of hits and tracked aircrafts."<< endl;

	d1.PrintGrid(radar.GetTrackFileList());

	return 0;
}
