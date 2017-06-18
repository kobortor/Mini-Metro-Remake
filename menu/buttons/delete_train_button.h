#pragma once
#include"../rel_button.h"

class delete_train_button : public rel_button {
public:
	delete_train_button(float _rel_wid, float _rel_ht);
	delete_train_button(float _relX, float _relY, float _rel_wid, float _rel_ht);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	void on_click(int prevX, int prevY, int curX, int curY, bool initClick) override;
	void on_release(int prevX, int prevY, int curX, int curY) override;

	static float select_range();
};