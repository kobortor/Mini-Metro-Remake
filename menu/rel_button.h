#pragma once
#include"button.h"

class rel_button : public button {
public:
	rel_button(float _rel_wid, float _rel_ht);
	rel_button(float _relX, float _relY, float _rel_wid, float _rel_ht);

	void resize();
protected:
	float relX, relY, relWid, relHt;
};