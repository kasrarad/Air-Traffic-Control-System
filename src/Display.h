/*
 * display.h
 *
 *  Created on: Oct 11, 2019
 *      Author: ajalnaseri
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Hit.h"
#include <vector>

using namespace std;


class Display {

//Display class public members
public:

//Air traffic controller grid display function
Display();
void PrintGrid(vector<Hit*> trackfile);


//Display class private members
private:


};


#endif /* DISPLAY_H_ */
