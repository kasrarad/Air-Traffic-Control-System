/*
 * display.cpp
 *
 *  Created on: Oct 11, 2019
 *      Author: philippeaboukasm
 */

#include "Display.h"

void Display::PrintGrid(vector<TrackFile> trackfile){

	cout << "Air Traffic Controller Display" << endl;

	for (int a = 0; a < 101; a++){

				if (a == 0) {
					cout << "{  }{ 0}";
				}

				else if(a < 10){
					cout << "{ " << a <<"}";
				}

				else {
				cout << "{" << a << "}";
				}
			}

				cout << endl;

			for (int b=0; b < 26; b++){

				if(b < 10) {
					cout<< "{ " << b << "}";
				} else {
					cout << "{" << b << "}" ;
				}


				for (int c=0; c < 26; c++){

					bool found, unknown;

					for (int d = 0; d< trackfile.size(); d++)
					{
						found = false;
						unknown = false;
						if (((trackfile[d].GetPosition()[0])/4000) == c && ((trackfile[d].GetPosition()[1])/4000) == b) {
							found = true;
							if (trackfile[d].GetID() == -1){
								unknown = true;
							}
							break;
						}
					}

					if(found && unknown){
						cout << "{--}";
					}
					else if(found && !unknown) {
						cout << "{++}";
					} else {
						cout << "{  }";
					}
				}

				cout << endl;

			}

			cout << endl;
		}







