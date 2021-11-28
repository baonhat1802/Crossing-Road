#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
#include <conio.h>
#include <thread>
#include<queue>
#include <stdlib.h>
#include<winapifamily.h>
using namespace std;
//#pragma execution_character_set("utf-8")

class Console {
public:
	void FixConsoleWindow();

	void SetSize(short w, short h);

	void SetCursor();

	void setbuffer();

	void setTitle();

	void setfontsize(int a, int b);

	short GetColor(short bcolor, short tcolor);

	void SetConsoleColor(short bcolor, short tcolor);

	void QuickEdit(bool flag);

	void SetConsole(const int& fontszie, const int& width, const int& height, bool quickEdit);

};

void GotoXY(COORD pos);
void del(COORD posA, COORD posB);
char GetCOORD(const COORD &COOR);
void DrawString(const string& str, const COORD& COOR, const int& Color);
void DrawfromFile(const COORD&pos,const char* filename);