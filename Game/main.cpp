#pragma once
#include "Console.h"
#include "Car.h"
#include"people.h"
#include "TrafficLight.h"
#include "Game.h"
#include"Map.h"
#include "Boat.h"
#include "truck.h"
#include "Menu.h"

#pragma comment(lib, "Winmm.lib")

template <class T>
void Moving(vector<T>&obj, int& i, int& dis) {
	for (int j = 0; j< obj.size(); j++)
		if (obj[j].isMoving())obj[j].Moving();

	if (i == 0) {
		obj[i].Moving();
		i++;
	}

	if (dis >= obj[i - 1].getWidth() + (rand() % 30)+8)
	{
		if (i == obj.size())i = 0;
		else obj[i].Moving(), i++;

		dis = 0;
	}
	else dis++;
}

vector<Car> Carlist1,Carlist2,Carlist3;
vector<Truck> Trucklist1,Trucklist2,Truclist3;
People p({ 56,42 }, 3, 3, "graphic/people.txt", 0);
TrafficLight tf({ 20,10 }, 3, 3, "graphic/TrafficL.txt", 0);
Map m({ 10,5 }, 102, 41, "graphic/map1.txt");
vector<Boat>Boatlist1;

int main() {
	Console handle;
	
	handle.SetConsole(15, 1150,800 , false);

	//for (int i = 0; i < 2; i++) {
	//	Carlist1.push_back(Car({ 30,10 }, 15, 3, "graphic/car.txt", 1, 0));
	//	Carlist2.push_back(Car({ 30,26 }, 15, 3, "graphic/car.txt", 1, 0));
	//	Trucklist1.push_back(Truck({ 110,15 }, 21, 3, "graphic/truck.txt", 0, 0));
	//	Trucklist2.push_back(Truck({ 110,31 }, 21, 3, "graphic/truck.txt", 0, 0));
	//}
	//for (int i = 0; i < 3; i++)
	//	Boatlist1.push_back(Boat({ 120,31 }, 28, 4, "graphic/boat1.txt", 0, 0));//32

	//m.DRAW();

	//while (!p.IsDead()) {
	//	p.Moving(m);
	//	tf.ControlTraffic();
	//	if (!tf.GetState()) {
	//		Moving(Carlist1, i1, dis1);
	//	}
	//		Moving(Trucklist1, i2, dis2);
	//		Moving(Boatlist1, i3, dis3);
	//	//	Moving(Carlist2, i4, dis4);
	//	//	Moving(Trucklist2, i5, dis5);
	//		//Sleep(45);
	//}
	//PlaySound(L"./sound/ingame.wav", NULL, SND_FILENAME | SND_ASYNC);
	//mciSendString(L"play  ./sound/ingame.wav", NULL, 0, NULL);
	Game g;
	g.RunGame();
	GotoXY({ 65,10 });
	cout << "GAME OVER BITCH!!!";
	//system("cls");
	//mciSendString(L"stop  ./sound/ingame.wav", NULL, 0, NULL);
	//Menu menu;
	//PlaySound(L"./sound/welcome.wav", NULL, SND_FILENAME | SND_ASYNC);
	//menu.Choose_Menu();
	system("pause>null");
}
