#pragma once

class clickable {
public:
	//Tries to click the object. If successful initially, it will continue to "click" it when isInitial is false
	void try_click(int x, int y, bool isInitial);

	//Releases the mouse on the object
	void try_release(int x, int y);
protected:
	//Returns true if the coordinate is contained within the object, false otherwise
	virtual bool contained(int x, int y);

	//To be implemented by the inherited object
	//prevX and prevY are the last known coordinates of the mouse
	//curX and curY are the current coordinates of the mouse
	//initClick will be true of it is the first click of the mouse, 
	//if it is false then it means the mouse has been "dragged"
	virtual void on_click(int prevX, int prevY, int curX, int curY, bool initClick) = 0;

	//To be implemented by the inherited object
	//prevX and prevY are the last known coordinates of the mouse
	//curX and curY are the current coordinates of the mouse
	virtual void on_release(int prevX, int prevY, int curX, int curY) = 0;

	//destructor
	virtual ~clickable();
private:
	int prevX, prevY;
	bool initClick = false;
};