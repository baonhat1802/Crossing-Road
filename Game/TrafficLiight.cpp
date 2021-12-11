#include "TrafficLight.h"

TrafficLight::TrafficLight(const COORD& pos_, const short& width_, const short& height_, const char* filename, bool State_){
	pos = pos_;
	State = State_;
	width = width_;
	height = height_;
	time = 0;

	fstream infile;
	infile.open(filename);
	string tmp;
	int i = 0;
	while (getline(infile, tmp)) {
		for (int j = 0; j < tmp.size(); j++)
			graphic[i][j] = tmp[j];
		i++;
	}

	infile.close();

}

void TrafficLight::DRAW() {
	COORD position = pos;
	for (int i = 0; i < height; i++) {
		GotoXY({ position.X, position.Y++ });
		for (int j = 0; j < width; j++) {
			if (i == 0 && j == 1 && State == true)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(12));
			else if (i == 1 && j == 1 && State == false)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(10));
			else 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
			cout << graphic[i][j];
		}
	}
}

void TrafficLight::ControlTraffic() {
	int t = 15 + rand() % 100;
	if (time >= t)State = !State, time = 0;
	else time++;

	DRAW();
}

bool TrafficLight::GetState() {
	return State;
}