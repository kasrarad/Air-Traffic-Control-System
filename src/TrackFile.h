#pragma once

#include "Hit.h"

#include <vector>
#include <iostream>

/*
 * Tracker File stores position, time, velocity and ID
 */

class TrackFile {
private:
	std::vector<Hit*> trackedLogFile;
	std::vector<int> position;
	std::vector<int> velocity;
	int id;
	int time;
public:
	TrackFile(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry);
	TrackFile();
	void StoreAircrafts(std::vector<Hit*> aircrafts);
	void GetLogByID(int id);
	int GetID();
	std::vector<int> GetSpeed();
	std::vector<int> GetPosition();
	std::vector<Hit*> GetTrackedLogFile();
	int GetTime();
	~TrackFile();
};
