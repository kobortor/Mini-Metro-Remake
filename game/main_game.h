#pragma once
#include"map_generator.h"
#include<SFML\Graphics.hpp>
#include"station.h"
#include"segment.h"
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

	static float get_station_radius();
	static float get_station_mouse_limit();

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
	
	enum direction {
		NORTH = 0,
		NORTH_EAST = 1,
		EAST = 2,
		SOUTH_EAST = 3,
		SOUTH = 4,
		SOUTH_WEST = 5,
		WEST = 6,
		NORTH_WEST = 7,
		NUM_DIRECTIONS = 8
	};

	//unit vectors in each of the 8 directions
	const static sf::Vector2f unit_direction[NUM_DIRECTIONS];

	const static std::string direction_names[NUM_DIRECTIONS];

	static segment selected_segment;
	static station* selected_station;
	static enum {NONE, LINE_EDIT, LINE_EDIT_STATION } CLICK_MODE;

	static bool mouse_button_pressed[sf::Mouse::ButtonCount];
	static bool key_pressed[sf::Keyboard::KeyCount];
};