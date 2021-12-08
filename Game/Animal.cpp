#include "Animal.h"

Animal::Animal() {
	inpos = pos = { 0,0 };
	width = 0;
	height = 0;
	direction = 0;
}

Animal::Animal(COORD pos_, short width_, short height_, const char* filename, bool direction_, bool state_) {
	inpos = pos = pos_;
	width = width_;
	height = height_;

	fstream filein;
	filein.open(filename);
	string tmp;
	int i = 0;

	while (getline(filein, tmp)) {
		int j = 0;
		for (int j = 0; j < tmp.size(); j++)
			graphic[i][j] = tmp[j];
		i++;
	}

	filein.close();
	state = state_;
	direction = direction_;
}

Animal::~Animal() {
	width = height = 0;
	pos = { 0, 0 };
	direction = 0;
	state = 0;
}