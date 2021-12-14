#pragma once
#include "Console.h"

class Key {
protected:
	COORD pos;
	string str;
	int Color;
public:
	Key();

	Key(const COORD& pos_, const string& str_, const int& Color_);

	void DRAW();

	void DRAW_Color(const int& Color);

	~Key();
};