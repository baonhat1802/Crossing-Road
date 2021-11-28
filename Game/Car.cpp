#include "Car.h"

void Car::DRAW() {
	COORD position = pos;
	for (int i = 0; i < height; i++) {
		GotoXY({ position.X,position.Y++});
		for (int j = 0; j < width; j++)
			if(position.X+j>=40&&position.X+j<=100)
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

//char*Car::backup() {
//	COORD position = pos;
//	char* a = new char[height];
//	for (int i = 0; i < height; i++) 
//		a[i] = GetCOORD({ position.X + width+1, position.Y++});
//	return a;
//	
//}
//
//void Car::DRAWBU(const char *a) {
//	COORD position = pos;
//	for (int i = 0; i < height; i++) {
//		GotoXY({ position.X - 1,position.Y++ });
//		cout << a[i];
//	}
//}

void Car::Moving() {
	if (pos.X + width >= 140 || pos.X + width <= 20) {
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
		del(pos, { pos.X + width+1,pos.Y + height });
		pos.X--;
	}

	DRAW();


}