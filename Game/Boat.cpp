#include "Boat.h"

Boat::Boat(COORD pos_, short width_, short height_, const char* filename, bool direction_, bool state_) {
	pos = inpos = pos_;
	width = width_;
	height = height_;
	direction = direction_;
	state = state_;
	time = 0;
	fstream infile;
	infile.open(filename);

	for (int i = 0; i < 3; i++) {
			string tmp;
		for (int j = 0; j < 4; j++) {
			getline(infile, tmp);
			for (int z = 0; z < 28; z++) {
				graphic[i][j][z] = tmp[z];
			}
		}
		getline(infile, tmp);
	}

	infile.close();
}

bool Boat::isMoving()
{
	return state;
}

int Boat::getWidth() {
	return width;
}

void Boat::DRAW() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
	int red = time % 3;
	COORD position = pos;
	for (int i = 0; i < height; i++) {
		GotoXY({ position.X,position.Y++ });
		for (int j = 0; j < width; j++)
			if (position.X + j >= 35 && position.X + j <= 109)
				cout << graphic[red][i][j];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
	(time == 2) ? time = 0 : time++;
}

void Boat::Moving() {
	if (pos.X + width >= 150 || pos.X + width <= 40) {
		del(pos, { pos.X + width,pos.Y + height });
		state = false;
		pos = inpos;
		return;
	}

	if (!state)
	{
		state = true;
		return;
	}


	if (state and direction)
	{
		del(pos, { pos.X + 1,pos.Y + height });
		pos.X++;
	}

	if (state and !direction)
	{
		if (pos.X <= 82)
		del(pos, { pos.X + width,pos.Y + height });
		pos.X--;
	}

	DRAW();
}

COORD Boat::GetPos()const {

	return pos;
}

bool Boat::GetState()const {

	return state;

}