#pragma once
#include"map_generator.h"
#include<SFML\Graphics.hpp>
#include"station.h"
#include<list>

class main_game {
public:
	main_game() = delete; //singleton

	static void initialize(map_generator* _map_gen);
	static sf::Vector2f get_relative_bounds();
	static sf::IntRect get_window_bounds(); //gets the position within the window
	static void resize();

	static void add_station(float _relX, float _relY, station::STATION_TYPE _type);
	static time_t get_game_time();
	static void update();
	static void render(); //always render to main window
	static void cleanup();

	static void handle_mouse_click(sf::Event::MouseButtonEvent eve);
	static void handle_mouse_move(sf::Event::MouseMoveEvent eve);
	static void handle_mouse_release(sf::Event::MouseButtonEvent eve);
	static void handle_key_press(sf::Event::KeyEvent eve);
	static void handle_key_release(sf::Event::KeyEvent eve);

protected:
	static sf::IntRect window_bounds;
	static sf::RectangleShape background;
	static std::list<station> stations;
	static time_t game_start_time;
	static map_generator* map_gen;

	static enum {NONE, LINE_EDIT, LINE_EDIT_STATION } CLICK_MODE;

	static bool mouse_button_pressed[sf::Mouse::ButtonCount];
	static bool key_pressed[sf::Keyboard::KeyCount];
};