#pragma once
#include<SFML\Graphics\Drawable.hpp>
#include"clickable.h"

class scrollable_menu_H : public sf::Drawable, public clickable {
public:
	scrollable_menu_H(int _y1, int _y2);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	bool contained(int x, int y);
	void onClick(int prevX, int prevY, int curX, int curY) override;
	void onRelease(int prevX, int prevY, int curX, int curY) override;
	int y1, y2;
	int tmpX;
};