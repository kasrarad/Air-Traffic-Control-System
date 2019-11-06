#pragma once

#include "Hit.h"
#include "TrackFile.h"
#include "Radar.h"
#include "TestCase.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cmath>


/*
 * Radar has a Tracker, Controls and Inputs
 */

class Radar {
private:
	std::ofstream logFile;
	int unknownCount = 0;
	int dimensionXY = 100000; // miles
	int dimensionZ = 25000; // miles
	int paramNum = 8; // Number of parameters in TestCase
	int distanceXY = 3;
	int distanceZ = 1000;
	std::vector<Hit*> hitList; // We keep track of all the hits
	std::vector<Hit*> trackedAircrafts; // List of tracked aircraft files
public:
	void Initialize();
	static void* Timer(void *arg);
	void LoadAircrafts(); // Loads all aircrafts from TestCase
	void CheckTrackedArea(int time); // Adds all aircraft inside the area
	void LogToOutput(int time);
	void CollisionCheck(int time); // Detects collision for near aircrafts
	void UpdatePosition(int time);
	std::vector<Hit*> GetHitList();
	std::vector<Hit*> GetTrackFileList(); // Get Active
	void FindAllUnknowns();
	Hit* FindAircraft(int id, std::vector<Hit*> list); // Used to find specific aircrafts in any list
	// Commands
	void ChangeAltitude(int id, int n); // Individual
	void ChangeSpeed(int id, int x, int y, int z); // Individual
	void ChangeDirection(int id); // Individual (horizontal plane)
	void HoldingPattern(int id); // Individual & All
	void ReportPositionVelocity(int id); // Individual
	void DisplayPositionAndVelocity(int index);
	void HoldingPatternToAll(); // All
	void ReportAircraft(); // All
	void DisplayAirspace();
	void DisplayTrackedAircrafts();
	// Airspace Management
	void AddAircraft(int id, int vx, int vy, int vz, int x, int y, int z, int time);
	void RemoveAircraft(int id);
	void ProjectPosition(int unit);
	~Radar();
};
