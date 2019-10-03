#include "Radar.h"
#include "Test/TestCase.h"

using namespace std;

Radar::Radar() {
	LoadAircrafts();
}

void Radar::LoadAircrafts() {
	TestCase aircrafts;
	for (size_t i = 1; i <= sizeof(aircrafts.airplane_schedule) / sizeof(aircrafts.airplane_schedule[0]) / paramNum; i++) {
		int id = aircrafts.airplane_schedule[i - 1 + 7 * (i - 1)];
	}
}

Radar::~Radar() {
}
