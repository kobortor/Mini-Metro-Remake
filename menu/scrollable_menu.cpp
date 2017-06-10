#include "scrollable_menu.h"
#include<SFML\Graphics.hpp>
#include<fstream>
#include<string>
#include<iostream>

scrollable_menu_H::scrollable_menu_H(int _y1, int _y2) :y1(_y1), y2(_y2) {
	std::ifstream mapfile("assets/maplist.txt");
	std::string mapname;
	int boxSz = y2 - y1 - 2 * margin;
	int left = margin;
	while (getline(mapfile, mapname)){
		vec.push_back(map_button(left, y1 + margin, boxSz, boxSz, mapname));
		left += boxSz + padding;
	}
}

void scrollable_menu_H::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(0, y1));
	rect.setSize(sf::Vector2f(10000, y2 - y1));
	rect.setFillColor(sf::Color::Red);

	targ.draw(rect);

	for (int a = 0; a < vec.size(); a++) {
		targ.draw(vec[a]);
	}
}

bool scrollable_menu_H::contained(int x, int y) {
	return y1 <= y && y <= y2;
}

void scrollable_menu_H::onClick(int prevX, int prevY, int curX, int curY) {
	//TODO: shift the blocks as the mouse drags
	//be sure to adjust for the block sizes, as that determines how much we can scroll
	int diffX = curX - prevX;
	for (int a = 0; a < vec.size(); a++) {
		vec[a].setPos(vec[a].getX() + diffX, vec[a].getY());
	}
}

void scrollable_menu_H::onRelease(int prevX, int prevY, int curX, int curY) {
	onClick(prevX, prevY, curX, curY);
}
