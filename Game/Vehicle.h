#pragma once
#include "Console.h"
class Vehicle { 
protected:
	short width, height;
	char graphic[30][30];
	COORD inpos,pos;
	bool direction;
	bool state;
private:
public:
	Vehicle();
	Vehicle(COORD pos_, short width_, short height_, const char* filename, bool direction_, bool state_);

	virtual void SetInpos(const COORD&)=0;

	virtual void DRAW()=0; 
	virtual void Moving()=0;

	virtual int getWidth()=0;
	
	virtual COORD GetPos() const = 0;
	virtual bool GetState() const = 0;

	virtual bool isMoving()=0;

	~Vehicle();

};
