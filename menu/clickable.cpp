#include"clickable.h"

void clickable::try_click(int x, int y, bool isInitial) {
	if (isInitial) {
		prevX = x;
		prevY = y;
		initClick = contained(x, y);
	}
	if(initClick){
		on_click(prevX, prevY, x, y, isInitial);
		prevX = x;
		prevY = y;
	}
}

void clickable::try_release(int x, int y) {
	if (initClick) {
		on_release(prevX, prevY, x, y);
		initClick = false;
	}
}

bool clickable::contained(int x, int y) {
	return false;
}

clickable::~clickable() {
}
