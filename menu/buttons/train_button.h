#pragma once
#include"../rel_button.h"

class train_button : public rel_button {
public:
	train_button(float _rel_wid, float _rel_ht);
	train_button(float _relX, float _relY, float _rel_wid, float _rel_ht);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	void on_click(int prevX, int prevY, int curX, int curY, bool initClick) override;
	void on_release(int prevX, int prevY, int curX, int curY) override;
private:
	static float select_range();
};