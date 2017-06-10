#include "scrollable_menu.h"
#include<SFML\Graphics.hpp>

scrollable_menu_H::scrollable_menu_H(int _y1, int _y2):y1(_y1), y2(_y2), tmpX(0) {}

void scrollable_menu_H::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(0, y1));
	rect.setSize(sf::Vector2f(10000, y2 - y1));
	rect.setFillColor(sf::Color::Red);

	sf::RectangleShape bar;
	bar.setPosition(sf::Vector2f(tmpX, y1));
	bar.setSize(sf::Vector2f(20, 100));
	bar.setFillColor(sf::Color::Blue);

	targ.draw(rect);
	targ.draw(bar);
}

bool scrollable_menu_H::contained(int x, int y) {
	return y1 <= y && y <= y2;
}

void scrollable_menu_H::onClick(int prevX, int prevY, int curX, int curY) {
	//TODO: shift the blocks as the mouse drags
	//be sure to adjust for the block sizes, as that determines how much we can scroll
	tmpX += curX - prevX;
}

void scrollable_menu_H::onRelease(int prevX, int prevY, int curX, int curY) {
	onClick(prevX, prevY, curX, curY);
}
