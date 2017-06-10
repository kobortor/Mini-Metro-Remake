#include"clickable.h"

void clickable::tryclick(int x, int y, bool isInitial) {
	bool cont = contained(x, y);
	if(cont){
		if (isInitial) {
			prevX = x;
			prevY = y;
		}
		onClick(prevX, prevY, x, y);
		prevX = x;
		prevY = y;
	}
}

bool clickable::contained(int x, int y) {
	return false;
}

clickable::~clickable() {
}
