#pragma once
#include "Console.h"

class TrafficLight {
private:
	COORD pos;
	bool State;
	char graphic[100][100];
	short width, height;
	short time;
public:
	TrafficLight(const COORD& pos_, const short&width_,const short&height_,const char* filename, bool State_);
	void DRAW();
	bool GetState();

	void ControlTraffic();

};


