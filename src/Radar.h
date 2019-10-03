#pragma once

#include "Hit.h"

#include <vector>
#include <iostream>

/*
 * Radar has a Tracker, Controls and Inputs
 */

class Radar {
private:
	int paramNum = 8; // Number of parameters below
	int id, x, y, z, vx, vy, vz, time; // Parameters
	std::vector<Hit> hitList; // We keep track of all the hits
public:
	Radar();
	void LoadAircrafts(); // Loads all aircrafts from TestCase
	~Radar();
};
