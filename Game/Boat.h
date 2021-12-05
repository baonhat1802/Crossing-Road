#pragma once
#include "Vehicle.h"
class Boat{
private:
	short width, height;
	COORD inpos, pos;
	bool direction;
	bool state;
	char graphic [3][30][30];
	int time;
public:
	Boat(COORD pos_, short width_, short height_, const char* filename, bool direction_, bool state_);
	void SetInpos(const COORD& inpos_) { inpos = inpos_; };

	void Moving();
	void DRAW();

	int getWidth();

	bool isMoving();

	COORD GetPos()const;

	bool GetState()const;
	/*char* backup();

	void DRAWBU(const char*a);*/
};
