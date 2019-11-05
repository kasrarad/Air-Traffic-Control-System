#pragma once

/*
 * Hit is an airspace object
 */

#include <vector>

class Hit {
protected:
	int id, vx, vy, vz, x, y, z, time;
public:
	Hit(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry);
	Hit();
	virtual int GetID();
	virtual std::vector<int> GetSpeed();
	virtual std::vector<int> GetPosition();
	virtual int GetTime();
	virtual void SetNewHit(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry);
	virtual ~Hit();
};
