#pragma once
#include "Animal.h"

class Shark : public Animal {
public:
	Shark(COORD pos_, short width_, short height_, const char* filename, bool direction_, bool state_)
		:Animal(pos_, width_, height_, filename, direction_, state_) {};

	void Moving();
	void DRAW();

	bool isMoving();

	int getWidth();
	void SetInpos(const COORD& inpos_) { inpos = inpos_; };
	COORD GetPos()const;

	bool GetState()const;
};