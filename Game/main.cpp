#pragma once
#include "Game.h"

int main() {

	Console handle;
	
	handle.SetConsole(15, 1150, 800, false);

	Game g;
	g.Process();

	system("pause>null");
	
}
