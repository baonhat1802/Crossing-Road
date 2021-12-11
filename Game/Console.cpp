#include "Console.h"

void Console::FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow(); 
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Console::SetSize(short w, short h) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, w, h, TRUE);
}

void Console::SetCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);


}

void Console::setbuffer() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	COORD newSize;
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;

	int Status = SetConsoleScreenBufferSize(hOut, newSize);
	if (Status == 0)
	{
		cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << endl;
		exit(Status);
	}

	/*GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
	cout << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << endl;*/
}

void Console::setfontsize(int a, int b) {
		PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
		lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
		GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx);
		lpConsoleCurrentFontEx->dwFontSize.X = a;
		lpConsoleCurrentFontEx->dwFontSize.Y = b;
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, lpConsoleCurrentFontEx);
}

short Console::GetColor(short bcolor, short tcolor) {
	return bcolor * 15 + bcolor + tcolor;
}

void Console::SetConsoleColor(short bcolor, short tcolor) {
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;

	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	::GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cbi);

	cbi.wAttributes = WORD(GetColor(bcolor, tcolor));
	::SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cbi);
}

void Console::QuickEdit(bool flag) {
	DWORD prev_mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), (!flag) ? (ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) : prev_mode);
}

void Console::setTitle() {

	SetConsoleTitle(L"Crossing Road");
	
}

void Console::SetConsole(const int& fontsize, const int& width, const int& height, const bool &quickEdit) {

	//setTitle();
	FixConsoleWindow();
	setfontsize(fontsize, fontsize);
	SetSize(width, height);
	setbuffer();
	SetCursor();
	QuickEdit(quickEdit);
	SetConsoleTitleW(L"Crossing Road");
}

void GotoXY(COORD pos) {

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void del(COORD posA, COORD posB) {
	GotoXY(posA);
	COORD tmp = posA;
	for (int i = 0; i < abs(posB.Y - tmp.Y); i++) {
		GotoXY({ posA.X,posA.Y++ });
		for (int j = 0; j < abs(posB.X - tmp.X); j++)
			cout << " ";
	}
}

char GetCOORD(const COORD& COOR) {
	TCHAR a[1];
	DWORD num_read;
	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), LPWSTR(a), DWORD(1), COOR, (LPDWORD)&num_read);
	return *a;
}

void DrawString(const string& str, const COORD& COOR, const int& Color) {
	GotoXY(COOR);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(Color));
	cout << str;
}

void DrawfromFile(const COORD&pos,const char* filename) {
	HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
	fstream filein;
	filein.open(filename);
	string tmp;
	short i = 0;
	while(getline(filein, tmp)) {
		SetConsoleTextAttribute(handle, WORD(rand() % 15 + 1));
		GotoXY({ pos.X, pos.Y + i++ });
		cout << tmp<<"\n";
	}

	filein.close();
}