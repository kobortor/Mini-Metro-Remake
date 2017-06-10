#pragma once

class clickable {
public:
	void tryClick(int x, int y, bool isInitial);
	void tryRelease(int x, int y);
protected:
	//default function is unclickable
	virtual bool contained(int x, int y);

	virtual void onClick(int prevX, int prevY, int curX, int curY, bool initClick) = 0;
	virtual void onRelease(int prevX, int prevY, int curX, int curY) = 0;
	virtual ~clickable();
private:
	int prevX, prevY;
	bool initClick = false;
};