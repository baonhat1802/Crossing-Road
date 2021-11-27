#include "Menu.h"

Menu::Menu() {
}


void Menu::iniMenu() {
	NewGame		= new Key({ 73,18 }, "New Game", 15);
	LoadGame	= new Key({ 73,20 }, "Load Game", 15);
	Options		= new Key({ 73,22 }, "Options", 15);
	Tutorial	= new Key({ 73,24 }, "Tutorial", 15);
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
	On_M = new Key({ 30,25 }, " ON ", 11);
	Off_M = new Key({ 36,25 }, " OFF ", 11);
	Return = new Key({ 33,28 }, "RETURN", 11);

	Option_Keys.push_back(On_M);
	Option_Keys.push_back(Off_M);
	Option_Keys.push_back(Return);
}

void Menu::iniCR() {
	fstream filein;
	filein.open("graphic/crname.txt");
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
	for (int i = 0; i < 17; i++) {
	SetConsoleTextAttribute(handle, WORD(i));
		GotoXY({ 12, j++ });
		cout << CR[i];
	}
}

void Menu::ini() {
	iniMenu();

	iniCR();

}

void Menu::Draw_Chosen() {
	for (auto e : Menu_Keys)
		e->DRAW();

	Menu_Keys[state-1]->DRAW_Color(240);
	SetConsoleTextAttribute(handle, WORD(15));
}

void Menu::DrawMenu() {
	
	ini();
	DRAW_CR();
	Draw_Chosen();
}

void Menu::Choose() {
	char c=' ';
	DrawMenu();
	while (true) {
		if (_kbhit()) {
			c = toupper(_getch());
			switch (c) {
			case 'W':
				state--;
				DrawMenu();
				break;
			case 'S':
				state++;
				DrawMenu();
				break;
			}

			if (state == 0)state = 6;
			else if (state == 7) state = 1;
		}
			if (c == char(13))break;
	}
}

void Menu::hitNewGame() {


}

void Menu::hitOption() {


}

void Menu::hitTutorial() {


}

void Menu::hitQuit() {


}

void Menu::Choose_Menu() {
	Choose();
	system("cls");
	switch (state) {
		case 1:
			
		case 2:
			
		case 3:
			
		case 4:
			
		case 5:
			
		case 6:
		
	}
}