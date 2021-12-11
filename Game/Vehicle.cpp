#include "Vehicle.h"

Vehicle::Vehicle() {
	inpos = pos = { 0,0 };
	width = 0;
	height = 0;
	direction = 0;
	state = 0;
}

Vehicle::Vehicle(COORD pos_, short width_, short height_, const char* filename, bool direction_, bool state_) {
	inpos=pos = pos_;
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
	direction = direction_;
	state = state_;
}

Vehicle::~Vehicle() {
	width = height = NULL;
	pos = { NULL,NULL };
	direction = NULL;
	state=NULL;
}
