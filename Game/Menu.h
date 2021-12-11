#pragma once
#include "Console.h"
#include "Menu_Key.h"

class Menu : public Key{
private:
	//Menu Key
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	int state = 1;

	Key* NewGame, *LoadGame, *Options, *Tutorial, *About, *Quit;
	// Option Key
	Key* On_M, * Off_M,* Return;
	
	vector<Key*>Menu_Keys;
	vector<Key*>Option_Keys;

	string CR[57];
	bool /*p_music*/p_game,load_status=true;
	bool quit, l_game;

	string load_profile;

	void iniCR();
	void DRAW_CR();

	void iniMenu();
	void iniOptions();

	void ini();

	void Choose();

	void Draw_Chosen();

	void Loading();

	void hitAbout();
	void hitOption();
	void hitTutorial();
	void hitQuit();
	void hitLoad(bool&);
	
	void Draw_Option();
	void pMenu_Music(); 

public:
	Menu();
	bool p_music;
	bool IsQuit()const;
	bool IsPlay()const;
	bool IsLoad(string& profile);

	void setbool();

	void Choose_Menu();
	void DrawMenu();
	~Menu();
};
