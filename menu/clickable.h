#pragma once

class clickable {
public:
	void try_click(int x, int y, bool isInitial);
	void try_release(int x, int y);
protected:
	//default function is unclickable
	virtual bool contained(int x, int y);

	virtual void on_click(int prevX, int prevY, int curX, int curY, bool initClick) = 0;
	virtual void on_release(int prevX, int prevY, int curX, int curY) = 0;
	virtual ~clickable();
private:
	int prevX, prevY;
	bool initClick = false;
};