#include"map_button.h"
#include"scrollable_menu.h"
#include"../fonts.h"
#include"../main_window.h"
#include"../game/main_game.h"
#include"../game/file_map_generator.h"
#include<iostream>

map_button::map_button(int _x, int _y, int _wid, int _ht, std::string _display_name, std::string _map_file_name)
	: button(_x,_y,_wid,_ht), display_name(_display_name), map_file_name(_map_file_name) {
}

void map_button::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	sf::Text txt;
	txt.setFont(font::consola);
	txt.setString(display_name);
	txt.setPosition(sf::Vector2f(x, y));

	sf::RectangleShape rect(sf::Vector2f(wid, ht));
	rect.setPosition(x, y);
	if (isClicked) {
		rect.setFillColor(sf::Color::White);
	} else {
		rect.setFillColor(sf::Color::Green);
	}

	targ.draw(rect);
	targ.draw(txt);
}

void map_button::onClick(int prevX, int prevY, int curX, int curY, bool isInitial) {
	isClicked = true;
}

void map_button::onRelease(int prevX, int prevY, int curX, int curY) {
	if (contained(curX, curY)) {
		std::cout << "CLICK MAP " << display_name << "\n";
		main_window::RENDER_MODE = main_window::IN_GAME;
		main_game::initialize(new file_map_generator(map_file_name));
	}
	isClicked = false;
}