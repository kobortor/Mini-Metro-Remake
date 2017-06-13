#pragma once
#include<SFML\Graphics.hpp>
#include"menu\scrollable_menu.h"

class main_window {
public:
	//this should not be created as an object
	main_window() = delete;
	static void initialize();
	static sf::RenderWindow& get_instance();
	enum {
		MAIN_MENU,
		IN_GAME,
		PAUSE_MENU,
		OPTION_MENU
	} static RENDER_MODE;

	static void handle_mouse_click(sf::Event::MouseButtonEvent eve);
	static void handle_mouse_move(sf::Event::MouseMoveEvent eve);
	static void handle_mouse_release(sf::Event::MouseButtonEvent eve);
	static void handle_key_press(sf::Event::KeyEvent eve);
	static void handle_key_release(sf::Event::KeyEvent eve);
	static void handle_resize(sf::Event::SizeEvent eve);
	static void render();
private:
	static scrollable_menu_H map_menu;
	static sf::RenderWindow instance;
	static bool mouse_button_pressed[sf::Mouse::ButtonCount];
	static bool key_pressed[sf::Keyboard::KeyCount];
};