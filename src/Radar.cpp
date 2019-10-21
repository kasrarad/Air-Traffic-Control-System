#include "Radar.h"
#include "TestCase.h"

using namespace std;

void Radar::Initialize() {
	LoadAircrafts();
	CheckTrackedArea();
}

void Radar::LoadAircrafts() {
	TestCase aircrafts;
	for (size_t i = 1; i <= sizeof(aircrafts.airplane_schedule) / sizeof(aircrafts.airplane_schedule[0]) / paramNum; i++) {
		int id = aircrafts.airplane_schedule[i - 1 + 7 * (i - 1)];
		int speedX = aircrafts.airplane_schedule[i + 0 + 7 * (i - 1)];
		int speedY = aircrafts.airplane_schedule[i + 1 + 7 * (i - 1)];
		int speedZ = aircrafts.airplane_schedule[i + 2 + 7 * (i - 1)];
		int x = aircrafts.airplane_schedule[i + 3 + 7 * (i - 1)];
		int y = aircrafts.airplane_schedule[i + 4 + 7 * (i - 1)];
		int z = aircrafts.airplane_schedule[i + 5 + 7 * (i - 1)];
		int time = aircrafts.airplane_schedule[i + 6 + 7 * (i - 1)];

		Hit* hit = new Hit(id, speedX, speedY, speedZ, x, y, z, time);
		hitList.push_back(hit);
	}
}

void Radar::CheckTrackedArea() {
	int x = 0;
	int y = 1;
	int z = 2;
	for (size_t i = 0; i < hitList.size(); i++) { // array[i][j]
		if (hitList[i]->GetPosition()[x] <= dimensionXY && hitList[i]->GetPosition()[y] <= dimensionXY && hitList[i]->GetPosition()[z] <= dimensionZ) {
			int id = hitList[i]->GetID();
			int speedX = hitList[i]->GetSpeed()[x];
			int speedY = hitList[i]->GetSpeed()[y];
			int speedZ = hitList[i]->GetSpeed()[z];
			int posX = hitList[i]->GetPosition()[x];
			int posY = hitList[i]->GetPosition()[y];
			int posZ = hitList[i]->GetPosition()[z];
			int timeE = hitList[i]->GetTime();

			Hit* trackFile = new Hit(id, speedX, speedY, speedZ, posX, posY, posZ, timeE);
			trackedAircrafts.push_back(trackFile);
		}
	}
}

bool Radar::CollisionCheck() {
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		if (i != trackedAircrafts.size() - 1) {
			if (trackedAircrafts[i]->GetPosition()[0] != (trackedAircrafts[i + 1]->GetPosition()[0] - 1) ||
				trackedAircrafts[i]->GetPosition()[0] != (trackedAircrafts[i + 1]->GetPosition()[0] + 1) ||
				trackedAircrafts[i]->GetPosition()[1] != (trackedAircrafts[i + 1]->GetPosition()[1] - 1) ||
				trackedAircrafts[i]->GetPosition()[1] != (trackedAircrafts[i + 1]->GetPosition()[1] + 1)) {
				// If the position in x is less or greater than 1, same in y: We check for collision (no diagonal check here)
				return false;
			}
		}
	}
	return true;
}

vector<Hit*> Radar::GetHitList() {
	return hitList;
}

vector<Hit*> Radar::GetTrackFileList() {
	return trackedAircrafts;
}

Radar::~Radar() {
	for (vector<Hit*>::iterator it = hitList.begin(); it < hitList.end(); it++) {
		delete *it;
	}
	hitList.clear();

	for (vector<Hit*>::iterator it = trackedAircrafts.begin(); it < trackedAircrafts.end(); it++) {
		delete *it;
	}
	trackedAircrafts.clear();
}
