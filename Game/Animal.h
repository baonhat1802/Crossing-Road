#pragma once
#include"Console.h"

class Animal {
protected:
	short width, height;
	char graphic[100][100];
	COORD inpos, pos;
	bool direction;
	bool state;
public:
	Animal();
	Animal(COORD pos_, short width_, short height_, const char* filename, bool direction_, bool state_);

	virtual void DRAW() = 0;
	virtual void Moving() = 0;

	virtual int getWidth() = 0;

	virtual bool isMoving() = 0;

	~Animal();
};