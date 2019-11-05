#include "Hit.h"

using namespace std;

Hit::Hit(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry):
id(identification), vx(speedX), vy(speedY), vz(speedZ), x(positionX), y(positionY), z(positionZ), time(timeEntry) {
}

Hit::Hit(){

}

int Hit::GetID() {
	return id;
}

std::vector<int> Hit::GetSpeed() {
	vector<int> speed;
	speed.push_back(vx);
	speed.push_back(vy);
	speed.push_back(vz);
	return speed;
}

std::vector<int> Hit::GetPosition() {
	vector<int> position;
	position.push_back(x);
	position.push_back(y);
	position.push_back(z);
	return position;
}

int Hit::GetTime() {
	return time;
}

void Hit::SetNewHit(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry) {
	id = identification;
	vx = speedX;
	vy = speedY;
	vz = speedZ;
	x = positionX;
	y = positionY;
	z = positionZ;
	time = timeEntry;
}

Hit::~Hit() {
}
