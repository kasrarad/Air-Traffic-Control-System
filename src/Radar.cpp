#include "Radar.h"
#include "TestCase.h"

using namespace std;

void Radar::Initialize() {
	LoadAircrafts();
	CheckTrackedArea(15);
	logFile.open("LogFile.txt");
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

void Radar::CheckTrackedArea(int time) {
	int x = 0;
	int y = 1;
	int z = 2;
	if (time % 15 == 0 ) {
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
}

void Radar::LogToOutput(int time) {
	if (time % 60 == 0 ) {
		logFile.open("LogFile.txt", ios_base::app);
		logFile << "Active List at time: " << time << endl;
		for (size_t i = 0; i < trackedAircrafts.size(); i++){
			logFile << "Plane ID: " << trackedAircrafts[i]->GetID() << endl;
			logFile <<"X: " << trackedAircrafts[i]->GetPosition()[0] << " Y: " << trackedAircrafts[i]->GetPosition()[1] << " Z: " << trackedAircrafts[i]->GetPosition()[2] << endl;
			logFile <<"Vx: " << trackedAircrafts[i]->GetSpeed()[0] << " Vy: " << trackedAircrafts[i]->GetSpeed()[1] << " Vz: " << trackedAircrafts[i]->GetPosition()[2] << endl;
		}
		logFile << "Airspace Input at time: " << time << endl;
		for (size_t i = 0; i < hitList.size(); i++){
			logFile << "Plane ID: " << hitList[i]->GetID() << endl;
			logFile << "X: " << hitList[i]->GetPosition()[0] << " Y: " << hitList[i]->GetPosition()[1] << " Z: " << hitList[i]->GetPosition()[2] << endl;
			logFile << "Vx: " << hitList[i]->GetSpeed()[0] << " Vy: " << hitList[i]->GetSpeed()[1] << " Vz: " << hitList[i]->GetSpeed()[2] << endl;
		}
	}
}

void Radar::CollisionCheck(int time) {
	if (time % 2 == 0) {
		logFile.open("LogFile.txt", ios_base::app);

		// Compare all coordinates
		for (size_t i = 0; i < trackedAircrafts.size(); i++) {
			Hit* h = trackedAircrafts[i];
			int posX1 = h->GetPosition()[0];
			int posY1 = h->GetPosition()[1];
			int posZ1 = h->GetPosition()[2];

			for (size_t j = i + 1; j < trackedAircrafts.size(); j++) {
				Hit* h = trackedAircrafts[j];
				int posX2 = h->GetPosition()[0];
				int posY2 = h->GetPosition()[1];
				int posZ2 = h->GetPosition()[2];

				int xCompare = pow(abs(posX2 - posX1) / 1000, 2);
				int yCompare = pow(abs(posY2 - posY1) / 1000, 2);
				int zCompare = abs(posZ2 - posZ1);
				int distance = sqrt(xCompare + yCompare);

				// We log to the log file
				if (distance <= distanceXY && zCompare <= distanceZ) {
					cout<<"Collision alert for aircraft ID: "<<trackedAircrafts[i]->GetID()<<" and ID: "<<trackedAircrafts[j]->GetID()<<endl;
					logFile<<"Collision alert for aircraft ID: "<<trackedAircrafts[i]->GetID()<<" and ID: "<<trackedAircrafts[j]->GetID()<<endl;
				}
			}
		}
	}
}

void Radar::UpdatePosition(int time) {
	if (time % 5 == 0 ) {
		for (size_t i = 0; i < trackedAircrafts.size(); i++) {
			trackedAircrafts[i]->SetNewHit(trackedAircrafts[i]->GetID(), trackedAircrafts[i]->GetSpeed()[0], trackedAircrafts[i]->GetSpeed()[1], trackedAircrafts[i]->GetSpeed()[2],  trackedAircrafts[i]->GetSpeed()[0] * time,  trackedAircrafts[i]->GetPosition()[1] * time,  trackedAircrafts[i]->GetPosition()[2] * time, time);
		}
	}
}

vector<Hit*> Radar::GetHitList() {
	return hitList;
}

vector<Hit*> Radar::GetTrackFileList() {
	return trackedAircrafts;
}

// All Commands

Hit* Radar::FindAircraft(int id, std::vector<Hit*> aircrafts) {
	for (size_t i = 0; i < aircrafts.size(); i++) {
		if (id == aircrafts[i]->GetID())
			return aircrafts[i];
	}
	return NULL;
}

void Radar::FindAllUnknowns() {
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		if (trackedAircrafts[i]->GetID() == -1) {
			int n1 = -1;
			int n2 = unknownCount;
			stringstream concat;
			concat<<n1<<n2;
			int number = 0;
			concat>>number;
			trackedAircrafts[i]->SetNewHit(number, trackedAircrafts[i]->GetSpeed()[0], trackedAircrafts[i]->GetSpeed()[1], trackedAircrafts[i]->GetSpeed()[2], trackedAircrafts[i]->GetPosition()[0], trackedAircrafts[i]->GetPosition()[1], trackedAircrafts[i]->GetPosition()[2], trackedAircrafts[i]->GetTime());
			unknownCount++;
		}
	}
}

void Radar::ChangeAltitude(int id, int n) {
	Hit* trackedAircraft = FindAircraft(id, trackedAircrafts);
	Hit* hitAircraft = FindAircraft(id, hitList);

	trackedAircraft->SetNewHit(id, trackedAircraft->GetSpeed()[0], trackedAircraft->GetSpeed()[1], trackedAircraft->GetSpeed()[2], trackedAircraft->GetPosition()[0], trackedAircraft->GetPosition()[1], trackedAircraft->GetPosition()[2] + (n * 1000), trackedAircraft->GetTime());
	hitAircraft->SetNewHit(id, hitAircraft->GetSpeed()[0], hitAircraft->GetSpeed()[1], hitAircraft->GetSpeed()[2], hitAircraft->GetPosition()[0], hitAircraft->GetPosition()[1], hitAircraft->GetPosition()[2] + (n * 1000), hitAircraft->GetTime());
}

void Radar::ChangeSpeed(int id, int x, int y, int z) {
	Hit* trackedAircraft = FindAircraft(id, trackedAircrafts);
	Hit* hitAircraft = FindAircraft(id, hitList);

	trackedAircraft->SetNewHit(id, x, y, z, trackedAircraft->GetPosition()[0], trackedAircraft->GetPosition()[1], trackedAircraft->GetPosition()[2], trackedAircraft->GetTime());
	hitAircraft->SetNewHit(id, x, y, z, hitAircraft->GetPosition()[0], hitAircraft->GetPosition()[1], hitAircraft->GetPosition()[2], hitAircraft->GetTime());
}

void Radar::ChangeDirection(int id) {
	// Changing velocity in x (opposite direction) in horizontal plane
	Hit* trackedAircraft = FindAircraft(id, trackedAircrafts);
	Hit* hitAircraft = FindAircraft(id, hitList);

	trackedAircraft->SetNewHit(id, -trackedAircraft->GetSpeed()[0], trackedAircraft->GetSpeed()[1], trackedAircraft->GetSpeed()[2], trackedAircraft->GetPosition()[0], trackedAircraft->GetPosition()[1], trackedAircraft->GetPosition()[2], trackedAircraft->GetTime());
	hitAircraft->SetNewHit(id, -hitAircraft->GetSpeed()[0], hitAircraft->GetSpeed()[1], hitAircraft->GetSpeed()[2], hitAircraft->GetPosition()[0], hitAircraft->GetPosition()[1], hitAircraft->GetPosition()[2], hitAircraft->GetTime());
}

void Radar::HoldingPattern(int id) {
	// Make it so we go around a small square on display ?
	// Every time amount passed, move according to speed<
	// Make it stop
}

void Radar::ReportPositionVelocity(int id) {
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		if (id == trackedAircrafts[i]->GetID())
			DisplayPositionAndVelocity(i);
	}
}

void Radar::DisplayAirspace() {
	cout<<"Overall Airspace:"<<endl;
	for (size_t i = 0; i < hitList.size(); i++) {
		cout<<"ID: "<<hitList[i]->GetID()<<endl;
		cout<<"Position: ("<<hitList[i]->GetPosition()[0]<<", "<<hitList[i]->GetPosition()[1]<<", "<<hitList[i]->GetPosition()[2]<<")"<<endl;
		cout<<"Velocity: ("<<hitList[i]->GetSpeed()[0]<<", "<<hitList[i]->GetSpeed()[1]<<", "<<hitList[i]->GetSpeed()[2]<<")"<<endl;
	}
}

void Radar::DisplayTrackedAircrafts() {
	cout<<"Current Tracked Aircrafts:"<<endl;
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		cout<<"ID: "<<trackedAircrafts[i]->GetID()<<endl;
		cout<<"Position: ("<<trackedAircrafts[i]->GetPosition()[0]<<", "<<trackedAircrafts[i]->GetPosition()[1]<<", "<<trackedAircrafts[i]->GetPosition()[2]<<")"<<endl;
		cout<<"Velocity: ("<<trackedAircrafts[i]->GetSpeed()[0]<<", "<<trackedAircrafts[i]->GetSpeed()[1]<<", "<<trackedAircrafts[i]->GetSpeed()[2]<<")"<<endl;
	}
}

void Radar::DisplayPositionAndVelocity(int index) {
	cout<<"Position: ("<<trackedAircrafts[index]->GetPosition()[0]<<", "<<trackedAircrafts[index]->GetPosition()[1]<<", "<<trackedAircrafts[index]->GetPosition()[2]<<")"<<endl;
	cout<<"Velocity: ("<<trackedAircrafts[index]->GetSpeed()[0]<<", "<<trackedAircrafts[index]->GetSpeed()[1]<<", "<<trackedAircrafts[index]->GetSpeed()[2]<<")"<<endl;
}

void HoldingPatternToAll() {
	// Make it so we go around a small square on display ?
	// Every time amount passed, move according to speed
}

void Radar::ReportAircraft() { // all
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		cout<<"ID: "<<trackedAircrafts[i]->GetID()<<endl;
		DisplayPositionAndVelocity(i);
	}
}

void Radar::AddAircraft(int id, int speedX, int speedY, int speedZ, int x, int y, int z, int time) {
	Hit* newAircraft = new Hit(id, speedX, speedY, speedZ, x, y, z, time);
	trackedAircrafts.push_back(newAircraft);
	hitList.push_back(newAircraft);
}

void Radar::RemoveAircraft(int id) {
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		if (trackedAircrafts[i]->GetID() == id)
			trackedAircrafts.erase(trackedAircrafts.begin() + i); // Deleting with its index
	}
	for (size_t i = 0; i < hitList.size(); i++) {
		if (hitList[i]->GetID() == id)
			hitList.erase(hitList.begin() + i); // Deleting with its index
	}
}

void Radar::ProjectPosition(int unitTime) {
	// Maybe show the display too here with new positions ?
	cout<<"Aircrafts projected with "<<unitTime<<"."<<endl;
	for (size_t i = 0; i < hitList.size(); i++) {
		cout<<"ID: "<<hitList[i]->GetID()<<endl;
		cout<<"Position: ("<<hitList[i]->GetPosition()[0] + hitList[i]->GetSpeed()[0] * unitTime<<", "<<hitList[i]->GetPosition()[1] + hitList[i]->GetSpeed()[1] * unitTime<<", "<<hitList[i]->GetPosition()[2] + hitList[i]->GetSpeed()[2] * unitTime<<")"<<endl;
	}
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
	logFile.close();
}
