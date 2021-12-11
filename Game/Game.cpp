#include "Game.h"
void Game:: ini() {
	g_process = g_running =  true;
	speed = 50;
	level = 0;
	maxlevel=10;
}

void Game::iniBoat() {
	Clear_Boat();

	for (int i = 0; i < 3; i++)
		listBoat.push_back(new Boat({ 110,20 }, 28, 4, "graphic/boat1.txt", 0, 0));//32
}

void Game::iniShark() {
	Clear_Shark();

	for (int i = 0; i < 3; i++)
		listShark.push_back(new Shark({ 11,36 }, 27, 4, "graphic/shark.txt", 1, 0));

}

void Game:: iniCar() {
	Clear_Car();
	
	for (int i = 0; i < 4; i++) {
		Carlist1.push_back(new Car({ 15,10 }, 15, 3, "graphic/car.txt", 1, 0));
		Carlist2.push_back(new Car({ 15,26 }, 15, 3, "graphic/car.txt", 1, 0));
	}
}
void Game::iniTruck() {
	Clear_Truck();

	for (int i = 0; i < 4; i++) {
		Trucklist1.push_back(new Truck({ 110,15 }, 21, 3, "graphic/truck.txt", 0, 0));
		Trucklist2.push_back(new Truck({ 110,31 }, 21, 3, "graphic/truck.txt", 0, 0));
	}
}

void Game::iniMap() {
	map=new Map({ 10,5 }, 128, 41, "graphic/map1.txt"); // 101
}

void Game::iniPeople() {
	Clear_People();

	p=new People({ 56,42 }, 3, 3, "graphic/people.txt", 0);
}

void Game:: iniTL() {
	Clear_TL();

	ListLight.push_back(new TrafficLight ({ 13,12 }, 3, 3, "graphic/TrafficL.txt", 0));

	ListLight.push_back(new TrafficLight({ 13,28 }, 3, 3, "graphic/TrafficL.txt", 0));
}

void Game::iniMenu() {
	Clear_Menu();
	menu = new Menu();
}

void Game::Clear_Car() {
	if (!Carlist1.empty())
		for (auto &e : Carlist1) {
			delete e;
		}

	if (!Carlist2.empty())
		for (auto &e : Carlist2) {
			delete e;
		}

	Carlist1.clear();
	Carlist2.clear();
}

void Game::Clear_Truck() {
	if (!Trucklist1.empty())
		for (auto &e : Trucklist1) {
			delete e;
		}

	if (!Trucklist2.empty())
		for (auto &e : Trucklist2) {
			delete e;
		}

	Trucklist1.clear();
	Trucklist2.clear();
}

void Game::Clear_People() {
	if (p != nullptr)delete p;
}

void Game::Clear_TL() {
	if (!ListLight.empty())
		for (auto &e : ListLight)
			delete e;
	ListLight.clear();
}

void Game::Clear_Boat() {
	if (!listBoat.empty())
		for (auto &e : listBoat) {
			delete e;
		}
	listBoat.clear();
}

void Game::Clear_Shark() {
	if (!listShark.empty())
		for (auto& e : listShark) {
			delete e;
		}
	listShark.clear();
}

void Game::Clear_Map() {
	if (map)
		delete map;
}

void Game::Clear_Menu() {
	if (menu)
		delete menu;
}

template<class T>
void Game::Moving(vector<T*> & obj, int& i, int& dis) {
	srand(time(0));
		for (int j = 0; j < obj.size(); j++)
			if (obj[j]->isMoving())obj[j]->Moving();

		if (i == 0) {
			obj[i]->Moving();
			i++;
		}

		if (dis >= obj[i - 1]->getWidth() +5+ (rand() % 15) )
		{
			if (i == obj.size()) i = 0;
			else obj[i]->Moving(), i++;

			dis = 0;
		}
		else dis++;
}


void Game::TFcontrol() {
	for (int i = 0; i < 2; i++)
	{
		ListLight[i]->ControlTraffic();
	}
}

bool Game::GameOver() {
	if (p->IsDead()) {
		g_running = false;
		return true;
	}
	return false;
}

void Game::p_ingame() {
	p->Moving(*map);
	if (p->IsOnTop())
	{
		speed-=5;
		level++;
		score = level * 100;
		p->Get_Start();
	}
}

void Game::RunGame() {
	while (!GameOver() and g_running) {
		TFcontrol();
		p_ingame();

		if (!ListLight[0]->GetState()) {
			Moving(Carlist1, i1, dis1);
			Moving(Trucklist1, i2, dis2);
		}

		Moving(listBoat, i3, dis3);

		if (!ListLight[1]->GetState()) {
			Moving(Carlist2, i4, dis4);
			Moving(Trucklist2, i5, dis5);
		}

		Moving(listShark, i6, dis6);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
		GotoXY({ 116,21 });
		cout << "> LEVEL: " << level << "/" << maxlevel;
		GotoXY({ 116,22 });
		cout << "> SCORE: " << score;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));

		//GotoXY({ (p->GetPos().X , p->GetPos().Y )});
		Sleep(speed);
	}
}

void Game::ResetGame() {
	dis1 = 0, i1 = 0;
	dis2 = 0, i2 = 0;
	dis3 = 0, i3 = 0;
	dis4 = 0, i4 = 0;
	dis5 = 0, i5 = 0;
	dis6 = 0, i6 = 0;

	level = score = 0;

	ini();

	iniBoat();
	iniShark();
	iniCar();
	iniTruck();

	iniMap();
	iniPeople();
	iniTL();
	map->DRAW();
	PlayMusic();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
	GotoXY({ 116,21 });
	cout << "> LEVEL: " << level << "/" << maxlevel;
	GotoXY({ 116,22 });
	cout << "> SCORE: " << score;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
}

bool Game::WinGame() {
	if (speed <= 0)
		return true;
	return false;
}

void Game::PlayMusic() {
	if(p_music)
		PlaySound(L"./sound/ingame.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
	else
		PlaySound(0, NULL, NULL);
}

void Game::PauseMusic() {
	if (p_music) {
		p_music = false;
		PlaySound(0, NULL, NULL);
	}
	else {
		p_music = true;
		PlaySound(L"./sound/ingame.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
	}
}

void Game::Running(const char & A) {
	ResetGame();
	g_play = thread(&Game::RunGame, this);
	bool IsLose = false, IsWin = false;

	char c = A;

	if (c == 'L') {
		LoadGame();
	}
	
	while (g_process) {

		if (GameOver() and !IsLose) {
			Sleep(100);
			PlaySound(0, NULL, NULL);
			if (g_running)
			{
				g_running = false;
				g_play.join();
			}
			PlaySound(L"./sound/lose.wav", NULL, SND_FILENAME | SND_ASYNC);
			p->DrawDead();

			IsLose = true;
			//End();
			
			system("cls");
			DrawfromFile({ 30,0 }, "graphic/BLNT.txt");
			GotoXY({ 73,20 });
			cout << "SCORE : " << score;
			PlaySound(L"./sound/dead.wav", NULL, SND_FILENAME | SND_ASYNC);
			GotoXY({ 66,42 });
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(240));
			cout << "Press Esc to back to Menu";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
			if (_kbhit()) {
				c = toupper(_getch());
				if (c == 27) {
					system("cls");
					break;
				}
			}
		}

		if (WinGame() and !IsWin) {
			Sleep(100);
			PlaySound(0, NULL, NULL);
			if (g_running)
			{
				g_running = false;
				g_play.join();
			}

			PlaySound(L"./sound/win.wav", NULL, SND_FILENAME | SND_ASYNC);
			IsWin = true;
			system("cls");
			DrawfromFile({ 0,0 }, "graphic/win.txt");
			GotoXY({ 66,42 });
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
			if (_kbhit()) {
				c = toupper(_getch());
				if (c == 27) {
					system("cls");
					break;
				}
			}
		}

		if (_kbhit()) {
			c = toupper(_getch());
			switch (c)
			{
			case 'P':
				PauseGame();
				break;
			case 'R':
				Reset();
				break;
			case 'T':
				SaveGame();
				break;
			case 'L':
				LoadGame();
				break;
			case 'O':
				PauseMusic();
				break;
			case 27://Esc
				if (g_running)
				{
					g_running = false;
					g_play.join();
				}

				g_process = false;
				if (IsWin || IsLose) {
					mciSendString(L"play ./sound/CJ.wav ", NULL, 0, NULL);
					Sleep(3000);
				}
				system("cls");

				break;
			}
		}
	}
	if (g_play.joinable()) g_play.join();
}

void Game::PauseGame() {
	if (g_running )
	{
		g_running = false;
		g_play.join();

	}
	else
	{
		g_running = true;
		g_play = thread(&Game::RunGame, this);
	}
}

void Game::Reset() {
	if (g_running)
	{
		g_running = false;
		g_play.join();
	}
	ResetGame();
	g_running = true;
	g_play = thread(&Game::RunGame, this);
}

void Game::SaveGame(){
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	if(g_running==true)
	PauseGame();

	string name;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
	GotoXY({ 113, 32 });

	cout << "> Input name: ";
	getline(cin, name);

	for (int i = 0; i <8; i++) {
		GotoXY({ 113, 33 });
		if(i%2==0)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(0));
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(240));
		cout << "Save game successfully !";
		Sleep(400);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
	del({ 113,32 }, { 162 ,34 });
	
	fstream fileout;

	fileout.open("save/" + name + ".txt", ios::out);

	fileout << level << "\n";
	fileout << score << "\n";

	fileout << speed << "\n";
	fileout << "People\n";
	fileout << p->GetPos().X << " " << p->GetPos().Y<<"\n";

	fileout << "Car1\n";
	for (int i = 0; i < 4; i++) {
		fileout << Carlist1[i]->GetState()<<"\n";
		fileout << Carlist1[i]->GetPos().X << " " << Carlist1[i]->GetPos().Y<<"\n";
		Carlist1[i]->DRAW();
	}

	fileout << "Car2\n";
	for (int i = 0; i < 4; i++) {
		fileout << Carlist2[i]->GetState()<<"\n";
		fileout << Carlist2[i]->GetPos().X << " " << Carlist2[i]->GetPos().Y<<"\n";
		Carlist2[i]->DRAW();
	}

	fileout << "Truck1\n";
	for (int i = 0; i < 4; i++) {
		fileout << Trucklist1[i]->GetState() << "\n";
		fileout << Trucklist1[i]->GetPos().X << " " << Trucklist1[i]->GetPos().Y << "\n";
		Trucklist1[i]->DRAW();
	}

	fileout << "Truck2" << "\n";
	for (int i = 0; i < 4; i++) {
		fileout << Trucklist2[i]->GetState() << "\n";
		fileout << Trucklist2[i]->GetPos().X << " " << Trucklist2[i]->GetPos().Y << "\n";
		Trucklist2[i]->DRAW();
	}

	fileout << "Boat" << "\n";
	for (int i = 0; i < 3; i++) {
		fileout << listBoat[i]->GetState() << "\n";
		fileout << listBoat[i]->GetPos().X << " " << listBoat[i]->GetPos().Y << "\n";
	}

	fileout << "Shark" << "\n";
	for (int i = 0; i < 3; i++) {
		fileout << listShark[i]->GetState() << "\n";
		fileout << listShark[i]->GetPos().X << " " << listShark[i]->GetPos().Y << "\n";
	}

	fileout << "TL" << "\n";
	for (int i = 0; i < 2; i++) {
		fileout << ListLight[i]->GetState() << "\n";
	}

	fileout << dis1 << " " << i1 <<	"\n";
	fileout << dis2 << " " << i2 << "\n";
	fileout << dis3 << " " << i3 << "\n";
	fileout << dis4 << " " << i4 << "\n";
	fileout << dis5 << " " << i5 << "\n";
	fileout << dis6 << " " << i6 << "\n";

	//Continue
	fileout.close();
	PauseGame();

}

void Game::LoadGame() {
	if (g_running == true)
	PauseGame();

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	string user_load_game;

	if (profile_load != "") {
		user_load_game = profile_load;
	} 

	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
		GotoXY({ 113, 32 });
		cout << "> Input name: ";
		getline(cin, user_load_game);
	}

	//cin.clear();
	fstream filein;
	filein.open("save/" + user_load_game + ".txt");

	profile_load.clear();
	if (filein.fail()) {

		filein.close();

		GotoXY({ 113,33 });
		cout << "Cannot load your save !";
		Sleep(2000);
		del({ 113,32 }, { 162,34 });

		PauseGame();
		return;
	}


	Clear_Car();
	Clear_Truck();
	Clear_People();
	Clear_TL();
	Clear_Boat();
	Clear_Shark();
	Clear_Map();

	del({ 0,0 }, { 115,48 });
	iniMap();
	map->DRAW();

	string tmp;
	short X, Y;
	bool State;

	filein >> level;
	filein >> score;

	filein >> speed;
	filein >> tmp;

	filein >> X >> Y;

	p = new People({ X,Y }, 3, 3, "graphic/people.txt", 0);

	filein >> tmp;
	for (int i = 0; i < 4; i++) {
		filein >> State;
		filein >> X >> Y;

		Carlist1.push_back(new Car({ X,Y }, 15, 3, "graphic/car.txt", 1, State));
		Carlist1[i]->SetInpos({ 15,10 });
		Carlist1[i]->DRAW();
	}

	filein >> tmp;
	for (int i = 0; i < 4; i++) {
		filein >> State;
		filein >> X >> Y;

		Carlist2.push_back(new Car({ X,Y }, 15, 3, "graphic/car.txt", 1, State));
		Carlist2[i]->SetInpos({ 15,26 });
		Carlist2[i]->DRAW();
	}

	filein >> tmp;
	for (int i = 0; i < 4; i++) {
		filein >> State;
		filein >> X >> Y;

		Trucklist1.push_back(new Truck({ X,Y }, 21, 3, "graphic/truck.txt", 0, State));
		Trucklist1[i]->SetInpos({ 110,15 });
		Trucklist1[i]->DRAW();
	}

	filein >> tmp;
	for (int i = 0; i < 4; i++) {
		filein >> State;
		filein >> X >> Y;

		Trucklist2.push_back(new Truck({ X,Y }, 21, 3, "graphic/truck.txt", 0, State));
		Trucklist2[i]->SetInpos({ 110,31 });
		Trucklist2[i]->DRAW();
	}

	filein >> tmp;
	for (int i = 0; i < 3; i++) {
		filein >> State;
		filein >> X >> Y;

		listBoat.push_back(new Boat({ X,Y }, 28, 4, "graphic/boat1.txt", 0, State));
		listBoat[i]->SetInpos({ 110,20 } );
		listBoat[i]->DRAW();
	}

	filein >> tmp;
	for (int i = 0; i < 3; i++) {
		filein >> State;
		filein >> X >> Y;

		listShark.push_back(new Shark({ X, Y }, 27, 4, "graphic/shark.txt", 1, State));
		listShark[i]->SetInpos({11, 36});
		listShark[i]->DRAW();
	}

	filein >>tmp;
	filein >> State;
	ListLight.push_back(new TrafficLight({ 13,12 }, 3, 3, "graphic/TrafficL.txt", State));
	filein >> State;
	ListLight.push_back(new TrafficLight({ 105,28 }, 3, 3, "graphic/TrafficL.txt", State));

	filein >> dis1 >> i1;
	filein >> dis2 >> i2;
	filein >> dis3 >> i3;
	filein >> dis4 >> i4;
	filein >> dis5 >> i5;
	filein >> dis6 >> i6;

	filein.close();
	PauseGame();
}

void Game::Process() {
	iniMenu();
	while (!menu->IsQuit())
	{
		//string profile;

		menu->Choose_Menu();

		if (menu->IsPlay()) {
			Running(' ');
		}

		if (menu->IsLoad(profile_load)) {
			Running('L');
		}

		menu->setbool();
	}
}

Game::~Game() {

	dis1 = 0, i1 = 0;
	dis2 = 0, i2 = 0;
	dis3 = 0, i3 = 0;
	dis4 = 0, i4 = 0;
	dis5 = 0, i5 = 0;
	dis6 = 0, i6 = 0;

	dis1 = i1 = NULL;
	dis2 = i2 = NULL;
	dis3 = i3 = NULL;
	dis4 = i4 = NULL;
	dis5 = i5 = NULL;
	dis6 = i6 = NULL;

	Clear_Menu();
	Clear_Car();
	Clear_Truck();
	Clear_People();
	Clear_TL();
	Clear_Boat();
	Clear_Shark();
	Clear_Map();

	profile_load.clear();

	speed= score= level= maxlevel=NULL;
	g_play.~thread();
	g_running=g_process=p_music =NULL;
}