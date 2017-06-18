#include"button.h"

button::button(int _wid, int _ht) :wid(_wid), ht(_ht) {}
button::button(int _x, int _y, int _wid, int _ht)
	: x(_x), y(_y), wid(_wid), ht(_ht) {}

void button::setPos(int _x, int _y) {
	x = _x;
	y = _y;
}
void button::setSize(int _wid, int _ht) {
	wid = _wid;
	ht = _ht;
}

sf::Vector2f button::get_pos() {
	return sf::Vector2f(x, y);
}

sf::Vector2f button::get_size() {
	return sf::Vector2f(wid, ht);
}

bool button::contained(int _x, int _y) {
	return x <= _x && _x <= x + wid && y <= _y && _y <= y + ht;
}