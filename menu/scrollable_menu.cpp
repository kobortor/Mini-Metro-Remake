#include "scrollable_menu.h"
#include<SFML\Graphics.hpp>
#include<fstream>
#include<string>
#include"../main_window.h"

scrollable_menu_H::scrollable_menu_H(int _y1, int _y2) :y1(_y1), y2(_y2) {
	std::ifstream mapFile("assets/maplist.txt");
	std::string mapName;
	std::string mapFileName;
	while (getline(mapFile, mapName)){
		getline(mapFile, mapFileName);
		//allow dummy sizes, will resize later
		buttons.push_back(map_button(0, 0, 1, 1, mapName, mapFileName));
	}
	resize();
}

void scrollable_menu_H::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(0, y1));
	rect.setSize(sf::Vector2f(10000, y2 - y1));
	rect.setFillColor(sf::Color::White);

	targ.draw(rect);

	for (int a = 0; a < buttons.size(); a++) {
		targ.draw(buttons[a]);
	}
}

bool scrollable_menu_H::contained(int x, int y) {
	return y1 <= y && y <= y2;
}

void scrollable_menu_H::on_click(int prevX, int prevY, int curX, int curY, bool isInitial) {
	//TODO: shift the blocks as the mouse drags
	//be sure to adjust for the block sizes, as that determines how much we can scroll
	int diffX = curX - prevX;
	for (int a = 0; a < buttons.size(); a++) {
		buttons[a].setPos(buttons[a].get_pos().x + diffX, buttons[a].get_pos().y);
		buttons[a].try_click(curX, curY, isInitial);
	}
}

void scrollable_menu_H::on_release(int prevX, int prevY, int curX, int curY) {
	int diffX = curX - prevX;
	for (int a = 0; a < buttons.size(); a++) {
		buttons[a].setPos(buttons[a].get_pos().x + diffX, buttons[a].get_pos().y);
		buttons[a].try_release(curX, curY);
	}
}

void scrollable_menu_H::resize() {
	sf::Vector2u windSz = main_window::get_instance().getSize();
	y1 = windSz.y * 0.15;
	y2 = windSz.y * (1 - 0.15);

	int boxSz = y2 - y1 - 2 * margin;
	int left = margin;
	int top = y1 + margin;

	for (int a = 0; a < buttons.size(); a++) {
		buttons[a].setPos(left, top);
		buttons[a].setSize(boxSz, boxSz);
		left += boxSz + padding;
	}
}