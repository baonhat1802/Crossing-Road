#pragma once
#include <thread>
#include"Console.h"
#include"Car.h"
#include "Boat.h"
#include "Shark.h"
#include "Map.h"
#include"TrafficLight.h"
#include "people.h"
#include "truck.h"
#include "Menu.h"
#pragma comment(lib, "Winmm.lib")

class Game {
private:
	int dis1 = 0, i1 = 0;
	int dis2 = 0, i2 = 0;
	int dis3 = 0, i3 = 0;
	int dis4 = 0, i4 = 0;
	int dis5 = 0, i5 = 0;
	int dis6 = 0, i6 = 0;

	vector<Boat*>listBoat;
	vector<Shark*>listShark;
	vector<Car*>Carlist1,Carlist2;
	vector<Truck*>Trucklist1,Trucklist2;
	vector<TrafficLight*> ListLight;

	People *p;
	Map *map;
	Menu* menu;

	string profile_load;

	int speed, score, level, maxlevel;
	thread g_play;
	bool g_running,g_process,p_music=true;

	void ini();
	void iniBoat();
	void iniShark();
	void iniCar();
	void iniTruck();
	void iniMap();
	void iniTL();
	void iniPeople();
	void iniMenu();

	void Clear_Menu();
	void Clear_Car();
	void Clear_Truck();
	void Clear_People();
	void Clear_TL();
	void Clear_Boat();
	void Clear_Shark();
	void Clear_Map();

	template<class T>
	void Moving(vector<T*>& obj, int& i, int& dis);

	void TFcontrol();
	bool GameOver();
	bool WinGame();

	void p_ingame();

	void SaveGame();

	void PauseGame();
	void Reset();
	void ResetGame();

	void PlayMusic();
	void PauseMusic();
	
public:

	void LoadGame();
	void Running(const char&A);
	void RunGame();
	void Process();
	~Game();

};
