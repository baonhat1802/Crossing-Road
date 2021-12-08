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

void People::Moving(Map&map) {
	
		if (GetAsyncKeyState(int(0x41)) & 1 && GetKeyState(int(0x41)) >> 15) {
			del(pos, { pos.X + width,pos.Y + height });
			if (pos.X >= 13)
				pos.X--;
			map.UpdateMap_people({ pos.X + width,pos.Y }, { pos.X + width - 1,pos.Y });
			//PlaySound(L"./sound/popsound.wav", NULL, SND_FILENAME | SND_ASYNC);
			mciSendString(L"play ./sound/popsound.wav ", NULL, 0, NULL);
		}

		if (GetAsyncKeyState(int(0x53)) & 1 && GetKeyState(int(0x53)) >> 15) {
			del(pos, { pos.X + width,pos.Y + height });
			if (pos.Y <= 42)
				pos.Y++;
			map.UpdateMap_people({ pos.X,pos.Y - 1 }, pos);
			//PlaySound(L"./sound/popsound.wav", NULL, SND_FILENAME | SND_ASYNC);
			mciSendString(L"play ./sound/popsound.wav ", NULL, 0, NULL);
		}

		if (GetAsyncKeyState(int(0x57)) & 1 && GetKeyState(int(0x57)) >> 15) {
			del(pos, { pos.X + width,pos.Y + height });
			if (pos.Y >= 3)
				pos.Y--;
			map.UpdateMap_people({ pos.X,pos.Y + height }, { pos.X,pos.Y + height - 1 });
			//PlaySound(L"./sound/popsound.wav", NULL, SND_FILENAME | SND_ASYNC);
			mciSendString(L"play ./sound/popsound.wav ", NULL, 0, NULL);
		}

		if (GetAsyncKeyState(int(0x44)) & 1 && GetKeyState(int(0x44)) >> 15) {
			del(pos, { pos.X + width,pos.Y + height });
			if(pos.X<=104)
				pos.X++;		
			map.UpdateMap_people({ pos.X-1,pos.Y }, pos);
			//PlaySound(L"./sound/popsound.wav", NULL, SND_FILENAME | SND_ASYNC);
			mciSendString(L"play ./sound/popsound.wav ", NULL, 0, NULL);
		}

		DRAW();
}

bool People::IsDead() {
	Sleep(1);
	string hit = "*.'w()</|\\o[]^~";
	for (int i = 0; i < hit.length(); i++) {
		if (
			GetCOORD({ pos.X, pos.Y }) == hit[i] ||
			GetCOORD({ pos.X + width, pos.Y }) == hit[i] ||
			GetCOORD({ pos.X, pos.Y + height }) == hit[i] ||
			GetCOORD({ pos.X + width,pos.Y + height }) == hit[i]
			||
			GetCOORD({ pos.X - 1, pos.Y + 1 }) == hit[i] ||
			GetCOORD({ pos.X + width + 1, pos.Y + 1 }) == hit[i]
			)
		{
			state = true;
			return state;
		}
	}
	state = false;
	return state;
}

bool People::IsOnTop() {
	if (pos.Y <= 6)
		return true;
	return false;
}

void People::Get_Start() {
	del(pos, { pos.X + width,pos.Y + height });
	pos.Y = 42;
	GotoXY(pos);

	DRAW();
}

COORD People:: GetPos()const {
	return pos;
}

void People::DrawDead() {
	fstream filein;
	filein.open("graphic/ded.txt");
	string tmp;
	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(7));
	while (getline(filein, tmp)) {
		GotoXY({ 50,15+short(i) });
		if (i == 19) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(10));
			cout << tmp<<endl;
		}
		else
			cout << tmp<<endl;
		i++;
		Sleep(50);
	}
	Sleep(2000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(15));
}