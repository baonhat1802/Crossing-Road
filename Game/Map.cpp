#include "Map.h"

Map::Map(const COORD& pos_, const int& width_, const int& height_, const char* filename) {
	pos = pos_;
	width = width_;
	height = height_;

	fstream infile;
	infile.open(filename);
	int i = 0;
	string tmp;
	while (getline(infile, tmp)) {
		for (int j = 0; j < tmp.length(); j++)
			graphic[i][j] = tmp[j];
		i++;
	}
	infile.close();
}

void Map::DRAW() {
	COORD position = pos;
	for (int i = 0; i < height; i++) {
		GotoXY({ position.X, position.Y++ });
		for (int j = 0; j < width; j++) {
			/*if (i % 16 < 10)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
			else */
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
				cout << graphic[i][j];
		}
	}
}

//void Map::UpdateMap() {
//	HDWP handle = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD position = pos;
//	for (int i = 10; i < height; i+=1) {
//			GotoXY({ position.X ,position.Y+short(i) });
//		for (int j = 0; j < width; j++) {
//			/*if (i % 12 < 6)
//				SetConsoleTextAttribute(handle, WORD(15));
//			else
//				SetConsoleTextAttribute(handle, WORD(9));*/
//		/*	if (GetCOORD({ position.X + short(j),position.Y - 1 }) == ' ' )
//			{
//				cout << graphic[i][j];
//			}*/
//			
//		}
//	}
//}

void Map::UpdateMap_people(COORD pos_,COORD update_pos) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
	if (abs(pos_.X - update_pos.X) == 1) {
		for (int i = 0; i < 3; i++) {
			GotoXY({ pos_.X,(pos_.Y) + short(i) });
			cout << graphic[pos_.Y + i - pos.Y][pos_.X - pos.X];
		}
	}
	else if (abs(pos_.Y - update_pos.Y) == 1) {
		GotoXY(pos_ );
		for (int i = 0; i < 3; i++) {
			cout << graphic[pos_.Y - pos.Y][pos_.X - pos.X+i];
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
}