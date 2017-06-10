#include"clickable.h"

void clickable::tryClick(int x, int y, bool isInitial) {
	bool cont = contained(x, y);
	if(cont || (!isInitial && initClick)){
		if (isInitial) {
			prevX = x;
			prevY = y;
			initClick = true;
		}
		onClick(prevX, prevY, x, y, isInitial);
		prevX = x;
		prevY = y;
	}
}

void clickable::tryRelease(int x, int y) {
	if (initClick) {
		onRelease(prevX, prevY, x, y);
		initClick = false;
	}
}

bool clickable::contained(int x, int y) {
	return false;
}

clickable::~clickable() {
}
