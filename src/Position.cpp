/*
 * position.cpp
 *
 *  Created on: Oct 11, 2019
 *      Author: ajalnaseri
 */


#include "Position.h"

using namespace std;

// Position class functions definition

Position::Position(){

}

Position::Position(int x, int y, int z, int xv, int yv, int zv){

	xcoordinate = x;

	ycoordinate = y;

	zcoordinate = z;

	xvelocity = xv;

	yvelocity = yv;

	zvelocity = zv;

}

Position::~Position(){


}

void Position::SetTime(int t){

	time = t;
}

void Position::SetX(int x){

	xcoordinate = x;
}

void Position::SetY(int y){

	ycoordinate = y;

}

void Position::SetZ(int z){

	zcoordinate = z;
}

void Position::SetXV(int xv){

	xvelocity = xv;
}

void Position::SetYV(int yv){

	yvelocity = yv;
}

void Position::SetZV(int zv){

	zvelocity = zv;
}

int Position::GetTime(){

	return time;
}

int Position::GetX(){

	return xcoordinate;
}

int Position::GetY(){

	return ycoordinate;
}

int Position::GetZ(){

	return zcoordinate;
}

int Position::GetXV(){

	return xvelocity;
}

int Position::GetYV(){

	return yvelocity;
}

int Position::GetZV(){

	return zvelocity;
}

