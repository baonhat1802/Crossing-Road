#pragma once
#include "Console.h"

class Map {
private:
	COORD pos;
	int width, height;
	char graphic[500][500];
	int time = 0;
public:
	Map(const COORD& pos_, const int& width_, const int& height_, const char* filename);

	void DRAW();
	
	void UpdateMap_people(COORD pos_,COORD update_pos);

};
