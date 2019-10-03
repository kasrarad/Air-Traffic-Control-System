#include "Hit.h"

using namespace std;

Hit::Hit(int identification, int positionX, int positionY, int positionZ) {
	id = identification;
	x = positionX;
	y = positionY;
	z = positionZ;
}

Hit::~Hit() {
}
