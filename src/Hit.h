#pragma once

/*
 * Hit is an airspace object
 */

#include <vector>

class Hit {
private:
	int id, vx, vy, vz, x, y, z, time;
public:
	Hit(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry);
	int GetID();
	std::vector<int> GetSpeed();
	std::vector<int> GetPosition();
	int GetTime();
	~Hit();
};
