#include "TrackFile.h"
#include "Hit.h"
#include "Display.h"
#include "Radar.h"

#include <iostream>
#include <vector>
#include <fstream>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>

#define PULSE_RADAR 1 	//_PULSE_CODE_MINAVAIL  //look into sys/neutrino.h for reference
#define PULSE_TRACK 2
#define PULSE_DISPLAY 3
#define PULSE_STORE 4
#define PULSE_UPDATE 5

using namespace std;

Display display;
TrackFile trackFile;
Radar radar;

vector<Hit*> trackedAircrafts;
vector<Hit*> logs;

bool scanned = false;
bool run = true;

pthread_t t1;
pthread_t t2;
pthread_t t3;
pthread_t t4;
pthread_t t5;
pthread_t t_server;

typedef union {
	struct _pulse   pulse;  // Basically a mechanism implementing non Blocking "send"
} my_message_t;

 struct sigevent         event;
 struct itimerspec       itime;
 timer_t                 timer_radar;
 timer_t                 timer_track;
 timer_t                 timer_display;
 timer_t                 timer_store;
 timer_t                 timer_update;
 int                     chid;
 int                     rcvid;
 my_message_t            msg;
 struct sched_param      scheduling_params;
 int prio;
 time_t start_time, end_time;
 int time_passed;

void setupCreateStartT(int timer_period_sec,long first_timeoutAt, int pulse_code, timer_t * timer_id){
	if (SchedGet(0, 0, &scheduling_params) != -1) {
		prio = scheduling_params.sched_priority;
	} else {
		prio = 10;
	}
	event.sigev_notify = SIGEV_PULSE;
	event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0,chid,_NTO_SIDE_CHANNEL, 0);
	event.sigev_priority = prio;
	event.sigev_code = pulse_code;
	timer_create(CLOCK_MONOTONIC, &event, timer_id); //CLOCK_MONOTONIC = clock starting at 0, time base never adjusted

	itime.it_value.tv_sec = 0;
	itime.it_value.tv_nsec = first_timeoutAt; ///000000000;
	itime.it_interval.tv_sec = timer_period_sec;
	itime.it_interval.tv_nsec = 000000000;
	timer_settime(*timer_id, 0, &itime, NULL);
}

void* radarThread(void *){
	end_time = time(NULL);
	time_passed = (int) difftime(end_time, start_time);
	cout<< "Time Passed: " << time_passed << endl;
	radar.CheckTrackedArea(time_passed);
	return 0;
}
void* track(void *){
	//radar.CollisionCheck(time_passed); // removed for testing
	return 0;
}
void* displayThread(void *){
	//radar.DisplayTrackedAircrafts(); // removed for testing
	radar.CheckUnknowns(); // Outputs a message if -1 plane found
	trackedAircrafts = radar.GetTrackFileList(); //returns active vector
	logs = trackFile.GetTrackedLogFile();
	display.PrintGrid(trackedAircrafts);
	return 0;
}
void* store(void *){
	end_time = time(NULL);
	time_passed = (int) difftime(end_time, start_time);
	radar.LogToOutput(time_passed); // Log to our output file
	trackFile.StoreAircrafts(trackedAircrafts); // Storing the current aircrafts to the logs
	return 0;
}

void* updatePos(void *){
	end_time = time(NULL);
	time_passed = (int) difftime(end_time, start_time);
	radar.UpdatePosition(time_passed);
	return 0;
}

void* server(void *){
	chid = ChannelCreate(0); //Add error checking here

	for (;;) {
		// Waiting forever for pulses (asynchronous)
		// Consider MsgReceivePulse() as well
		rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
		if (rcvid == 0) { /* we got a pulse */
			if (msg.pulse.code == PULSE_RADAR) {
				pthread_create(&t1, NULL, radarThread, NULL);
			}else if (msg.pulse.code == PULSE_TRACK) {
				pthread_create(&t2, NULL, track, NULL);
			}else if (msg.pulse.code == PULSE_DISPLAY) {
				pthread_create(&t3, NULL, displayThread, NULL);
			}else if (msg.pulse.code == PULSE_STORE) {
				pthread_create(&t4, NULL, store, NULL);
			}else if (msg.pulse.code == PULSE_UPDATE) {
				pthread_create(&t5, NULL, updatePos, NULL);
			}
		}
	}
	return 0;
}

int main() {
	bool running = true;
	int command;
	int idcommand;
	int allcommand;
	int opcommand;
	int aircraftid;
	int altamount;
	int vxamount;
	int vyamount;
	int vzamount;
	int airid;
	int airx;
	int airy;
	int airz;
	int airvx;
	int airvy;
	int airvz;
	int airt;
	int delid;
	int logid;
	int projsec;

	bool displayIsPaused;

	radar.LoadAircrafts(); // Parses the file to hitList
	pthread_create(&t_server, NULL, server, NULL);

	while(running) {
	trackedAircrafts.clear();

	cout << "-----------------------------------------[Air Traffic Controller]-----------------------------------------"<< endl;
	cout << "Input the command number you would like to execute:" << endl;
	cout << "1 - Run airspace" << endl;

	if(displayIsPaused)
		cout << "2 - Resume Display" << endl;
	else
		cout << "2 - Pause Display" << endl;

	cout << "3 - Command Aircraft By ID" << endl;
	cout << "4 - Command All Aircrafts" << endl;
	cout << "5 - Modify Airspace" << endl;
	cout << "6 - Identify Unknown Plane(s)" << endl;
	cout << "7 - Exit" << endl;

	cin >> command;

		switch(command) {
			case 1:
				start_time = time(NULL);
				setupCreateStartT(15,100000000, PULSE_RADAR, &timer_radar);
				setupCreateStartT(2,500000000, PULSE_TRACK, &timer_track);
				setupCreateStartT(5,700000000, PULSE_DISPLAY, &timer_display);
				setupCreateStartT(60,900000000, PULSE_STORE, &timer_store);
				setupCreateStartT(1,100000000, PULSE_UPDATE, &timer_update);
				break;

			case 2:
				if(!displayIsPaused) {
					timer_delete(timer_display);
					displayIsPaused = true;
					cout << "Display Paused" << endl;
				} else {
					setupCreateStartT(5,700000000, PULSE_DISPLAY, &timer_display);
					displayIsPaused = false;
				}
				break;

			case 3:
				cout << "Enter the ID of the aircraft:" << endl;
				cin >> aircraftid;

				cout << "Input the command number you would like to execute:"<< endl;
				cout << "1 - Change Altitude" << endl;
				cout << "2 - Change Speed" << endl;
				cout << "3 - Report Position & Velocity" << endl;
				cout << "4 - Enter Holding Pattern" << endl;  //NOT IMPLEMENTED
				cout << "5 - Exit" << endl;

				cin >> idcommand;

				switch(idcommand) {

					case 1:
						cout << "Enter the amount of change in integers ( x 1000):" << endl;
						cin >> altamount;
						radar.ChangeAltitude(aircraftid, altamount);
						cout << "Altitude successfully changed." << endl;
						break;

					case 2:
						cout << "Enter the desired speed coordinates Vx, Vy, Vz seperated by return:" << endl;
						cin >> vxamount;
						cin >> vyamount;
						cin >> vzamount;

						radar.ChangeSpeed(aircraftid, vxamount, vyamount, vzamount);
						cout << "Speed successfully changed." << endl;
						break;

					case 3:
						radar.ReportPositionVelocity(aircraftid);
						break;
					case 4:
						radar.HoldingPattern(aircraftid);
						break;
					case 5:
						break;
					}
					break;

			case 4:
				cout << "Input the command number you would like to execute:" << endl;
				cout << "1 - Enter Holding Pattern" << endl;
				cout << "2 - Report Aircraft Information" << endl;
				cout << "3 - Exit" << endl;
				cin >> allcommand;

			switch(allcommand) {
				case 1:
					radar.HoldingPatternToAll();
					break;

				case 2:
					radar.DisplayAirspace();
					radar.DisplayTrackedAircrafts();
					break;
				case 3:
					break;
				}
				break;

			case 5:
				cout << "Input the command number you would like to execute:" << endl;
				cout << "1 - Add Aircraft" << endl;
				cout << "2 - Delete Aircraft By ID" << endl;
				cout << "3 - Display Log By ID" << endl;
				cout << "4 - Project Aircraft Positions" << endl;
				cout << "5 - Exit" << endl;

				cin >> opcommand;

				switch (opcommand) {
					case 1:
						cout << "Enter aircraft ID: ";
						cin >> airid;
						cout << endl << "Enter aircraft X coordinate:";
						cin >> airx;
						cout << endl << "Enter aircraft Y coordinate:";
						cin >> airy;
						cout << endl << "Enter aircraft Z coordinate:";
						cin >> airz;
						cout << endl << "Enter aircraft X speed:";
						cin >> airvx;
						cout << endl << "Enter aircraft Y speed:";
						cin >> airvy;
						cout << endl << "Enter aircraft Z speed:";
						cin >> airvz;
						cout << endl << "Enter aircraft entry time:";
						cin >> airt;
						radar.AddAircraft(airid, airx, airy, airz, airvx, airvy, airvz, time_passed); // replace 1 with current time;
						cout << endl << "Aircraft successfully added" << endl;
						break;

					case 2:

						cout << "Enter aircraft ID:";
						cin >> delid;
						radar.RemoveAircraft(delid);
						cout << endl << "Aircraft with ID " << delid << " successfully deleted." << endl;
						break;

					case 3:
						cout << "Enter aircraft ID:";
						cin >> logid;
						trackFile.GetLogByID(logid);
						break;

					case 4:
						cout << "Enter the number of time units for the projection:";
						cin >> projsec;
						radar.ProjectPosition(projsec);
						break;

					case 5:
						break;
					}
					break;
			case 6:
				radar.FindAllUnknownsAndIdentify();
				cout<<"All unknown plane(s) have been identified with a new ID."<<endl;
				break;
			case 7:
				running = false;
				break;
		}
	}
	return 0;
}
