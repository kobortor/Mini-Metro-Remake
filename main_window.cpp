#include"main_window.h"

//static variables
sf::RenderWindow main_window::instance;

//i hate static declarations...
decltype(main_window::RENDER_MODE) main_window::RENDER_MODE;

void main_window::initialize() {
	instance.create(sf::VideoMode(500, 500), "WTF");
	RENDER_MODE = MAIN_MENU;
}

sf::RenderWindow& main_window::getInstance() {
	return instance;
}