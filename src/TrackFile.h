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
	virtual int GetID();
	virtual std::vector<int> GetSpeed();
	virtual std::vector<int> GetPosition();
	virtual int GetTime();
	virtual ~TrackFile();
};
