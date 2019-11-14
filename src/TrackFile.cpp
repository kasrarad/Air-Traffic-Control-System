#include "TrackFile.h"

// Note: still have to store the previous information of all the aircrafts in a vector

using namespace std;

TrackFile::TrackFile(){
}

void TrackFile::StoreAircrafts(vector<Hit*> aircrafts) {
	for (size_t i = 0; i < aircrafts.size(); i++)
		trackedLogFile.push_back(aircrafts[i]);
}

void TrackFile::GetLogByID(int id) {
	// Maybe show the display too here with new positions ?
	cout<<"Here are the logs for aircraft ID #"<<id<<"."<<endl;
	for (size_t i = 0; i < trackedLogFile.size(); i++) {
		if (trackedLogFile[i]->GetID() == id) {
			cout<<"--------------------------------------------------------------------------------"<<endl;
			cout<<"Position: ("<<trackedLogFile[i]->GetPosition()[0]<<", "<<trackedLogFile[i]->GetPosition()[1]<<", "<<trackedLogFile[i]->GetPosition()[2]<<")"<<endl;
			cout<<"Velocity: ("<<trackedLogFile[i]->GetSpeed()[0]<<", "<<trackedLogFile[i]->GetSpeed()[1]<<", "<<trackedLogFile[i]->GetSpeed()[2]<<")"<<endl;
			cout<<"Time: "<<trackedLogFile[i]->GetTime()<<endl;
			cout<<"--------------------------------------------------------------------------------"<<endl;
		}
	}
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

std::vector<Hit*> TrackFile::GetTrackedLogFile() {
	return trackedLogFile;
}

int TrackFile::GetTime() {
	return time;
}

TrackFile::~TrackFile() {
	for (vector<Hit*>::iterator it = trackedLogFile.begin(); it < trackedLogFile.end(); it++) {
		delete *it;
	}
	trackedLogFile.clear();
}
