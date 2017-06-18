#pragma once
#include"button.h"

class rel_button : public button {
public:
	//Widths and heights relative to the ratios of the window
	rel_button(float _rel_wid, float _rel_ht);

	//x position, y position, widths and heights relative to the ratios of the window
	rel_button(float _relX, float _relY, float _rel_wid, float _rel_ht);

	//Resizes this object to the new screen size
	void resize();
protected:
	float relX, relY, relWid, relHt;
};