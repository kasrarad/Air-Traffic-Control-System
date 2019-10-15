/*
 * position.h
 *
 *  Created on: Oct 11, 2019
 *      Author: ajalnaseri
 */

#ifndef POSITION_H_
#define POSITION_H_


//Position class definition

class Position{


//Position class public members
public:

//Position class constructors
	Position();

	Position(int x, int y, int z, int xv, int yv, int zv);


//Position class destructor
	~Position();


//Position class setter functions
	void SetTime(int t);

	void SetX(int x);

	void SetY(int y);

	void SetZ(int z);

	void SetXV(int xv);

	void SetYV(int yv);

	void SetZV(int zv);


//Position class getter functions
	int GetTime();

	int GetX();

	int GetY();

	int GetZ();

	int GetXV();

	int GetYV();

	int GetZV();


//Position class private members
private:

	int time;

	int xcoordinate;

	int ycoordinate;

	int zcoordinate;

	int xvelocity;

	int yvelocity;

	int zvelocity;


};





#endif /* POSITION_H_ */
