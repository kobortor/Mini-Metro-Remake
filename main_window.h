#pragma once
#include<SFML\Graphics.hpp>

class main_window {
public:
	//this should not be created as an object
	main_window() = delete;
	static void initialize();
	static sf::RenderWindow& getInstance();
	enum {
		MAIN_MENU,
		IN_GAME //maybe add OPTIONS_MENU and PAUSE_MENU somewhere
	} static RENDER_MODE;

private:
	static sf::RenderWindow instance;
};