#include "CommandProcessor.h"

using namespace std;

void CommandProcessor::Initialize(vector<Hit*> aircrafts) {
	for (size_t i = 0; i < aircrafts.size(); i++)
		trackedAircrafts[i] = aircrafts[i];
}

void CommandProcessor::ChangeAltitude() {
}

void CommandProcessor::ChangeSpeed() {
}

void CommandProcessor::ChangeDirection() {
}

void CommandProcessor::HoldingPattern() {
}

void CommandProcessor::ReportPositionVelocity(int id) {
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		if (id == trackedAircrafts[i]->GetID())
			DisplayPositionAndVelocity(i);
	}
}

void CommandProcessor::ReportAircraft() {
	for (size_t i = 0; i < trackedAircrafts.size(); i++) {
		cout<<"ID: "<<trackedAircrafts[i]->GetID()<<endl;
		DisplayPositionAndVelocity(i);
	}
}

void CommandProcessor::DisplayPositionAndVelocity(int index) {
	cout<<"Position: ("<<trackedAircrafts[index]->GetPosition()[0]<<", "<<trackedAircrafts[index]->GetPosition()[1]<<", "<<trackedAircrafts[index]->GetPosition()[2]<<")"<<endl;
	cout<<"Velocity: ("<<trackedAircrafts[index]->GetSpeed()[0]<<", "<<trackedAircrafts[index]->GetSpeed()[1]<<", "<<trackedAircrafts[index]->GetSpeed()[2]<<")"<<endl;
}

CommandProcessor::~CommandProcessor() {
	for (vector<Hit*>::iterator it = trackedAircrafts.begin(); it < trackedAircrafts.end(); it++) {
			delete *it;
		}
	trackedAircrafts.clear();
}
