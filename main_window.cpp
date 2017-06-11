#include"main_window.h"

//static variables
sf::RenderWindow main_window::instance;

void main_window::initialize() {
	instance.create(sf::VideoMode(500, 500), "WTF");
}

sf::RenderWindow& main_window::getInstance() {
	return instance;
}