#pragma once

#include "Hit.h"

#include <iostream>
#include <vector>

/*
 * All commands sent to an individual or all
 */

using namespace std;

class CommandProcessor {
private:
	vector<Hit*> trackedAircrafts;
public:
	void Initialize(vector<Hit*> aircrafts);
	void ChangeAltitude(); // Individual
	void ChangeSpeed(); // Individual
	void ChangeDirection(); // Individual (horizontal plane)
	void HoldingPattern(); // Individual & All
	void ReportPositionVelocity(int id); // Individual
	void ReportAircraft(); // All
	void DisplayPositionAndVelocity(int index);
	~CommandProcessor();
};
