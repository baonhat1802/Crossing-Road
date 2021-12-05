#pragma once
#include "Console.h"
#include "Map.h"
class People {
private :
	COORD pos;
	short height, width;
	char graphic[100][100];
	bool state;
	static friend class Map;
public	:
	People(const COORD& pos_, const short& height_, const short& width_, const char *filename, bool IsDead_);
	void DRAW();
	void Moving(Map&map);

	bool IsDead();
	bool IsOnTop();

	void Get_Start();

	COORD GetPos()const;

};