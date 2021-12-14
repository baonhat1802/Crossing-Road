#include "Shark.h"

void Shark::DRAW() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
	COORD position = pos;
	for (int i = 0; i < height; i++) {
		GotoXY({ position.X, position.Y++ });
		for (int j = 0; j < width; j++) {
			if (position.X + j >= 15 && position.X + j <= 108)
				cout << graphic[i][j];
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
}

bool Shark::isMoving() {
	return state;
}

int Shark::getWidth() {
	return width;
}

void Shark::Moving() {
	if (pos.X + width >= 136 || pos.X + width <= 10)
	{
		//del(pos, { pos.X + width , pos.Y + height });
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
		del(pos, { pos.X + 1, pos.Y + height });
		pos.X++;
	}

	if (state and !direction)
	{
		//if (pos.X <= 110 - 27 - 1)
		del(pos, { pos.X + width, pos.Y + height });
		pos.X--;
	}

	DRAW();
}

COORD Shark::GetPos()const {

	return pos;
}

bool Shark::GetState()const {

	return state;

}