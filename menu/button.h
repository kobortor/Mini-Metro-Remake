#pragma once
#include "clickable.h"
#include<SFML\Graphics.hpp>

class button : public clickable, public sf::Drawable {
public:
	button(int _wid, int _ht);
	button(int _x, int _y, int _wid, int _ht);
	void setPos(int _x, int _y);
	int getX();
	int getY();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
	bool contained(int _x, int _y);
protected:
	int x, y;
	int wid, ht;
};