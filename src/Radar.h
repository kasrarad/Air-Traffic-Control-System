#pragma once

#include "Hit.h"

#include <vector>
#include <iostream>

/*
 * Radar has a Tracker, Controls and Inputs
 */

class Radar {
private:
	int dimensionXY = 100000; // miles
	int dimensionZ = 25000; // miles
	int paramNum = 8; // Number of parameters in TestCase
	std::vector<Hit> hitList; // We keep track of all the hits
	std::vector<Hit> trackedAircrafts;
public:
	void Initialize();
	void LoadAircrafts(); // Loads all aircrafts from TestCase
	void CheckTrackedArea();
	~Radar();
};
