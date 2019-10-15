#pragma once

#include "Hit.h"

#include <vector>
#include <iostream>

/*
 * Tracker File stores position, time, velocity and ID
 */

class TrackFile: public Hit {
private:
	std::vector<int> position;
	std::vector<int> velocity;
	int id;
	int time;
public:
	TrackFile(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry);
	TrackFile();
	int GetID();
	 std::vector<int> GetSpeed();
	 std::vector<int> GetPosition();
	 int GetTime();
	 ~TrackFile();
};
