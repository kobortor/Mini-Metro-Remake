#pragma once

class clickable {
public:
	void tryclick(int x, int y, bool isInitial);
protected:
	//default function is unclickable
	virtual bool contained(int x, int y);
	virtual void onClick(int prevX, int prevY, int curX, int curY) = 0;
	virtual ~clickable();
private:
	int prevX, prevY;
};