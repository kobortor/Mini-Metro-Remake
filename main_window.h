#pragma once
#include<SFML\Graphics.hpp>

class main_window {
public:
	//this should not be created as an object
	main_window() = delete;
	static void initialize();
	static sf::RenderWindow& getInstance();
private:
	static sf::RenderWindow instance;
};