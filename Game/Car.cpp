#include "Car.h"

void Car::DRAW() {
	COORD position = pos;
	for (int i = 0; i < height; i++) {
		GotoXY({ position.X,position.Y++});
		for (int j = 0; j < width; j++)
			if(position.X+j>=17 && position.X+j<=109)
				cout << graphic[i][j];
	}
}

bool Car::isMoving()
{
	return state;
}

int Car::getWidth() {
	return width;
}

void Car::Moving() {
	if (pos.X + width >= 125 || pos.X + width <= 10) {
		//del(pos, { pos.X,pos.Y + height });
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
		del(pos, { pos.X + width,pos.Y + height });
		pos.X--;
	}

	DRAW();

}

COORD Car:: GetPos()const {

	return pos;
}

bool Car::GetState()const {

	return state;

}