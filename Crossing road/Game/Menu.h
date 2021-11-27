#pragma once
#include "Console.h"
#include "Menu_Key.h"

class Menu : public Key {
private:
	//Menu Key
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int state = 1;
	Key* NewGame, * LoadGame, * Options, *Tutorial,*About,*Quit;
	// Option Key
	Key* On_M, * Off_M,* Return;
	
	vector<Key*>Menu_Keys;
	vector<Key*>Option_Keys;

	string CR[20];

	void iniCR();
	void DRAW_CR();

	void iniMenu();
	void iniOptions();


	void ini();

	void Choose();

	void Draw_Chosen();

	void hitNewGame();
	void hitOption();
	void hitTutorial();
	void hitQuit();

public:
	Menu();
	void Choose_Menu();
	void DrawMenu();


};
