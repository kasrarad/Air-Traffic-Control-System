#include "Radar.h"
#include "Test/TestCase.h"

using namespace std;

void Radar::Initialize() {
	LoadAircrafts();
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

		Hit hit(id, speedX, speedY, speedZ, x, y, z, time);
		hitList.push_back(hit);
	}
}

void Radar::CheckTrackedArea() {
	for (size_t i = 0; i < hitList.size(); i++) {
		if (hitList[i].GetPosition[0] == dimensionXY && hitList[i].GetPosition[1] == dimensionXY && hitList[i].GetPosition[2] == dimensionZ) {
			//trackedAircrafts[i]
		}
	}
}

Radar::~Radar() {
}
