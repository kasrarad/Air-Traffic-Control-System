#pragma once

#include "Hit.h"
#include "TrackFile.h"
#include "Radar.h"
#include "TestCase.h"

#include <vector>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>
#include <time.h>

/*
 * Radar has a Tracker, Controls and Inputs
 */

class Radar {
private:
	int unknownCount = 0;
	int dimensionXY = 100000; // miles
	int dimensionZ = 25000; // miles
	int paramNum = 8; // Number of parameters in TestCase
	std::vector<Hit*> hitList; // We keep track of all the hits
	std::vector<Hit*> trackedAircrafts; // List of tracked aircraft files
public:
	void Initialize();
	static void* Timer(void *arg);
	void LoadAircrafts(); // Loads all aircrafts from TestCase
	void CheckTrackedArea(); // Adds all aircraft inside the area
	bool CollisionCheck(); // Detects collision for near aircrafts
	std::vector<Hit*> GetHitList();
	std::vector<Hit*> GetTrackFileList();
	void FindAllUnknowns();
	Hit* FindAircraft(int id, std::vector<Hit*> list); // Used to find specific aircrafts in any list
	void ChangeAltitude(int id, int n); // Individual
	void ChangeSpeed(int id, int x, int y, int z); // Individual
	void ChangeDirection(int id); // Individual (horizontal plane)
	void HoldingPattern(int id); // Individual & All
	void ReportPositionVelocity(int id); // Individual
	void DisplayPositionAndVelocity(int index);
	void HoldingPatternToAll(); // All
	void ReportAircraft(); // All
	~Radar();
};
