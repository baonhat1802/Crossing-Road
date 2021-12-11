#include "Menu.h"

Menu::Menu() {
	load_profile = "";
	state = 1;
	p_music = true;
	p_game = false;
	l_game = false;
	quit = false;
}

void Menu::pMenu_Music() {
	if(p_music)
		PlaySound(L"./sound/welcome.wav", NULL, SND_LOOP |SND_FILENAME| SND_ASYNC);
	else
		PlaySound(NULL, 0, 0);
}

void Menu::iniMenu() {
	NewGame		= new Key({ 72,18 }, "New Game", 15);
	LoadGame	= new Key({ 72,20 }, "Load Game", 15);
	Options		= new Key({ 73,22 }, "Music", 15);
	Tutorial	= new Key({ 72,24 }, "Tutorial", 15);
	About		= new Key({ 73,26 }, "About", 15);
	Quit		= new Key({ 73,28 }, "Quit", 15);

	Menu_Keys.push_back(NewGame);
	Menu_Keys.push_back(LoadGame);
	Menu_Keys.push_back(Options);
	Menu_Keys.push_back(Tutorial);
	Menu_Keys.push_back(About);
	Menu_Keys.push_back(Quit);
}

void Menu::iniOptions() {
	On_M = new Key({ 85,22 }, " ON ", 11);
	Off_M = new Key({ 85,22 }, " OFF ", 11);

	Option_Keys.push_back(On_M);
	Option_Keys.push_back(Off_M);
}

void Menu::iniCR() {
	fstream filein;
	filein.open("graphic/crname.txt"); // cr

	string tmp;
	int i = 0;

	while (getline(filein, tmp)) {
		CR[i] = tmp;
		i++;
	}

	filein.close();
}

void Menu::DRAW_CR() {
	iniCR();
	
	short j = 0;
	srand(time(NULL));

	for (int i = 0; i < 19; i++) {
	SetConsoleTextAttribute(handle, WORD(rand()%15+1));
		GotoXY({ 12, j++ });
		cout << CR[i];
	}
}

void Menu::ini() {
	iniCR();
	iniMenu();
	iniOptions();
}

void Menu::Draw_Chosen() {
	for (auto e : Menu_Keys)
		e->DRAW();

	Menu_Keys[state-1]->DRAW_Color(240);
	SetConsoleTextAttribute(handle, WORD(15));
}

void Menu::Draw_Option() {
	if(p_music)
		Option_Keys[0]->DRAW_Color(11);
	else
		Option_Keys[1]->DRAW_Color(11);
}

void Menu::DrawMenu() {
	ini();
	DRAW_CR();
	Draw_Chosen();
	Draw_Option();
}


void Menu::Choose() {
	char c=' ';
	DrawMenu();
	pMenu_Music();
	while (true) {
		if (_kbhit()) {
			c = toupper(_getch());
			switch (c) {
			case 'W':
				state--;
				break;
			case 'S':
				state++;
				break;
			}
			if (state == 0)	state = 6;
			else if (state == 7) state = 1;
			Draw_Chosen();
		}
			if (c == char(13))break;
			DRAW_CR();
	}
}


void Menu::hitOption() {
	if (p_music)
	{	
		Option_Keys[1]->DRAW_Color(11);
		p_music = false;
	}
	else
	{
		Option_Keys[0]->DRAW_Color(11);
		p_music = true;
	}
}

void Menu::Loading() {
	system("cls");

	DrawfromFile({ 50,10 }, "graphic/Loading.txt");
	GotoXY({ 30,18 });

	SetConsoleTextAttribute(handle, WORD(170));
	for (int i = 0; i < 100; i++) {
			cout << " ";
		Sleep(10);
	}
	
	SetConsoleTextAttribute(handle, WORD(15));
	system("cls");
}

void Menu::hitAbout() {
	system("cls");
	SetConsoleOutputCP(CP_UTF8);
	DrawfromFile({ 55,15 }, "graphic/About.txt");
	GotoXY({67,32 });
	SetConsoleTextAttribute(handle, WORD(240));
	cout << "Press ""ESC"" to back to Menu ";
	char c = ' ';
	while (true) {
		if (_kbhit()) {
			c = _getch();
		}
		if (c == 27)break;
	}
	SetConsoleTextAttribute(handle, WORD(15));
	system("cls");
}

void Menu::hitTutorial() {
	system("cls");
	SetConsoleOutputCP(CP_UTF8);
	DrawfromFile({ 30,0 }, "graphic/Rules.txt");
	GotoXY({ 69,47 });
	SetConsoleTextAttribute(handle, WORD(240));
	cout << "Press ""Enter"" to back to Menu ";
	char c = ' ';
	while (true) {
		if (_kbhit()) {
			c = _getch();
		}
		if (c == 13)break;
	}
	SetConsoleTextAttribute(handle, WORD(15));
	system("cls");
}

//void Menu::hitLoad() {
//	system("cls");
//	SetConsoleOutputCP(CP_UTF8);
//	string user_load;
//	DrawfromFile({ (0,0) }, "graphic/loadgame1.txt");
//
//	GotoXY({ 70,20 });
//	//cout << "> ENTER NAME TO LOAD: ";
//	
//	getline(cin, user_load);
//	load_profile = user_load;
//
//	system("cls");
//}

void Menu::hitLoad(bool& status) {
	system("cls");
	SetConsoleOutputCP(CP_UTF8);
	string user_load;
	DrawfromFile({ (0,0) }, "graphic/loadgame1.txt");

	GotoXY({ 70,20 });

	getline(cin, user_load);
	load_profile = user_load;

	fstream filein;
	filein.open("save/" + user_load + ".txt");

	if (filein.fail()) {
		status = 0;
		GotoXY({ 60,21 });
		SetConsoleTextAttribute(handle, WORD(240));
		cout << "- Cannot load your profile !\n";
		SetConsoleTextAttribute(handle, WORD(15));
		char c = ' ';
		while (true) {
			if (_kbhit()) {
				c = _getch();
			}
			if (c == 27)
				break;
		}
	}
	else {
		status = 1;
	}
	
	filein.close();
	system("cls");
}

void Menu::hitQuit() {
	system("cls");
	DrawfromFile({ 0,0 }, "graphic/thankyou.txt");
}

void Menu::Choose_Menu() {
	Choose();
	switch (state) {
		case 1:
			p_game = true;
			Loading();
			PlaySound(NULL, 0, 0);
			break;
		case 2:
			hitLoad(load_status);
			if (load_status) {
				l_game = true;
				Loading();
			}
			else
				Choose_Menu();
			break;
		case 3:
			hitOption();
			Choose_Menu();
			break;

		case 4:
			hitTutorial();
			Choose_Menu();
			break;

		case 5:
			hitAbout();
			Choose_Menu();
			break;
			
		case 6:
			quit = true;
			hitQuit();

			break;
	}
}

bool Menu::IsQuit()const {
	return quit;
}

bool Menu::IsPlay()const {
	return p_game;
}

bool Menu::IsLoad(string& profile) {
	profile = load_profile;
	return l_game;
}

void Menu::setbool() {
	p_game = l_game = false;
}

Menu::~Menu() {
	handle=NULL;
	state = 0;
	state = NULL;

	delete  NewGame,  LoadGame, Options, Tutorial, About, Quit, On_M, Off_M, Return;

	if (!Menu_Keys.empty()) {
		for (auto& e : Menu_Keys) 
			delete e;
	}
	Menu_Keys.clear();

	vector<Key*>Option_Keys;

	if (!Option_Keys.empty()) {
		for (auto& e : Option_Keys)
			delete e;
	}
	Option_Keys.clear();

}