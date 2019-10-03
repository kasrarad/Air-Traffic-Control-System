#pragma once

/*
 * Hit is an airspace object
 */

#include <vector>

class Hit {
private:
	int id, x, y, z;
public:
	Hit(int identification, int positionX, int positionY, int positionZ);
	~Hit();
};
