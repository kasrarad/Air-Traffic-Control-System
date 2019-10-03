#pragma once

#include "Hit.h"

#include <vector>
#include <iostream>

/*
 * Radar has a Tracker, Controls and Inputs
 */

class Radar {
private:
	int paramNum = 8; // Number of parameters in TestCase
	std::vector<Hit> hitList; // We keep track of all the hits
public:
	Radar();
	void LoadAircrafts(); // Loads all aircrafts from TestCase
	~Radar();
};
