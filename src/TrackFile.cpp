#include "TrackFile.h"

// Note: still have to store the previous information of all the aircrafts in a vector

using namespace std;

TrackFile::TrackFile(int identification, int speedX, int speedY, int speedZ, int positionX, int positionY, int positionZ, int timeEntry):
Hit(identification, speedX, speedY, speedZ, positionX, positionY, positionZ, timeEntry) {
	this->id = identification;
	this->velocity[0] = speedX;
	this->velocity[1] = speedY;
	this->velocity[2] = speedZ;
	this->position[0] = positionX;
	this->position[1] = positionY;
	this->position[2] = positionZ;
	this->time = timeEntry;
}

TrackFile::TrackFile(){

}

int TrackFile::GetID() {
	return id;
}

std::vector<int> TrackFile::GetSpeed() {
	return velocity;
}

std::vector<int> TrackFile::GetPosition() {
	return position;
}

int TrackFile::GetTime() {
	return time;
}

TrackFile::~TrackFile() {
}
