#pragma once
#include"../rel_button.h"

class train_button : public rel_button {
public:
	//Same constructor as rel_button
	train_button(float _rel_wid, float _rel_ht);

	//Same constructor as rel_button
	train_button(float _relX, float _relY, float _rel_wid, float _rel_ht);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Overridden function
	void on_click(int prevX, int prevY, int curX, int curY, bool initClick) override;

	//Overridden function
	void on_release(int prevX, int prevY, int curX, int curY) override;

	//Returns the range in which this button has effect
	static float select_range();
};