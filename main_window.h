#pragma once
#include<SFML\Graphics.hpp>
#include"menu\scrollable_menu.h"

class main_window {
public:
	//this should not be created as an object
	main_window() = delete;

	//Initializes the window
	static void initialize();

	//Gets the main Render Window instanec
	static sf::RenderWindow& get_instance();
	enum {
		MAIN_MENU,
		IN_GAME,
		GAME_OVER
	} static RENDER_MODE;

	//Handler for when the user clicks on their mouse
	static void handle_mouse_click(sf::Event::MouseButtonEvent eve);

	//Handler for when the user moves their mouse
	static void handle_mouse_move(sf::Event::MouseMoveEvent eve);

	//Handler for when the user releases a key on their mouse
	static void handle_mouse_release(sf::Event::MouseButtonEvent eve);

	//Handler for when the user presses a key on the keyboard
	static void handle_key_press(sf::Event::KeyEvent eve);

	//Handler for when the user releases a key on the keyboard
	static void handle_key_release(sf::Event::KeyEvent eve);

	//Handler for when the window gets resized
	static void handle_resize(sf::Event::SizeEvent eve);

	//Renders images on the window
	static void render();
private:
	static scrollable_menu_H map_menu;
	static sf::RenderWindow instance;
	static bool mouse_button_pressed[sf::Mouse::ButtonCount];
	static bool key_pressed[sf::Keyboard::KeyCount];
};