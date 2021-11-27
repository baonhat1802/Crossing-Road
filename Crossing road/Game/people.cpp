#include "people.h"

People::People(const COORD& pos_, const short& height_, const short& width_, const char*filename, bool IsDead_) {
	pos = pos_;
	height = height_;
	width = width_;
	state= IsDead_;

	fstream infile;
	infile.open(filename);
	string tmp;
	int i = 0;
	while (getline(infile, tmp)) {
		for (int j = 0; j < tmp.length(); j++) {
			graphic[i][j] = tmp[j];
		}
		i++;
	}

	infile.close();

}

void People::DRAW() {
	COORD position = pos;
	for (int i=0; i < height; i++) {
		GotoXY({ position.X, position.Y++ });
		for (int j = 0; j < width; j++)
			cout << graphic[i][j];
	}
}

//bool People::IsDead() {
//	return state;
//}

void People::Moving(Map&map) {
	del(pos, { pos.X + width,pos.Y + height });
	if (_kbhit()) {
		char key = toupper(_getch());
		switch (key)
		{
		case 'A':
			if(pos.X>=20)
				pos.X--;
			map.UpdateMap_people({ pos.X  + width,pos.Y }, { pos.X + width-1,pos.Y });
			break;
		case 'S':
			if(pos.Y<=57)
				pos.Y++;
			map.UpdateMap_people({ pos.X,pos.Y-1 }, pos);
			break;
		case 'W':
			if (pos.Y >= 3)
				pos.Y--;
			map.UpdateMap_people({ pos.X,pos.Y+ height }, { pos.X,pos.Y + height-1 });
			break;
		case 'D':
			if(pos.X<=140)
				pos.X++;
			map.UpdateMap_people({ pos.X-1,pos.Y }, pos);
			break;
		}

	}
		DRAW();	
		
}

bool People::IsDead() {
	if (GetCOORD({ pos.X - 1, pos.Y }) == '|'  ||
		GetCOORD({ pos.X + width + 1,pos.Y }) == '|' ||
		GetCOORD({ pos.X - 1,pos.Y + height }) == '|' ||
		GetCOORD({ pos.X + width + 1,pos.Y + height }) == '|'
		)
	{
		state = true;
		return true;
	}
	state = false;
	return false;;
}

bool People::IsOnTop() {
	if (pos.Y <= 10)
		return true;
	return false;
}

void People::Get_Start() {
	del(pos, { pos.X + width,pos.Y + height });
	pos.Y = 42;
	GotoXY(pos);

	DRAW();
}
