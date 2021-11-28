#include "Menu_Key.h"

Key::Key() {
	pos = { 0,0 };
	str=" ";
	Color=0;
}

Key::Key(const COORD& pos_, const string& str_, const int&Color_){
	pos = pos_;
	str = str_;
	Color = Color_;
}

void Key::DRAW() {
	DrawString(str, pos, Color);
}

void Key::DRAW_Color(const int& Color_) {

	DrawString(str, pos, Color_);

}
