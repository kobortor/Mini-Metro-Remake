#pragma once
#include"map_generator.h"
#include<SFML\Graphics.hpp>
#include"train.h"

class main_game {
public:
	main_game() = delete; //singleton

	enum CLICK_MODE_TYPE { NONE, LINE_EDIT_FRONT, LINE_EDIT_BACK };

	static void initialize(map_generator* _map_gen);
	static sf::Vector2f get_relative_bounds();
	static sf::IntRect get_window_bounds(); //gets the position within the window
	static void resize();

	static void add_station(float _relX, float _relY, station::STATION_TYPE _type);
	static time_t get_game_time();
	static void update();
	static void render(); //always render to main window
	static void cleanup();

	static void set_edit_line(metro_line* line, CLICK_MODE_TYPE mode);

	static float get_station_radius();
	static float get_station_mouse_limit();

	static void handle_mouse_click(sf::Event::MouseButtonEvent eve);
	static void handle_mouse_move(sf::Event::MouseMoveEvent eve);
	static void handle_mouse_release(sf::Event::MouseButtonEvent eve);
	static void handle_key_press(sf::Event::KeyEvent eve);
	static void handle_key_release(sf::Event::KeyEvent eve);

	//make some protected
	static sf::IntRect window_bounds;
	static sf::RectangleShape background;
	static std::list<metro_line> lines;
	static std::list<station> stations;
	static std::list<train> trains;
	static time_t game_start_time;
	static map_generator* map_gen;
	static time_t last_update;

	static metro_line* edit_line;
	static segment edit_seg;
	static CLICK_MODE_TYPE CLICK_MODE;

	static int prvX, prvY;
	static bool mouse_button_pressed[sf::Mouse::ButtonCount];
	static bool key_pressed[sf::Keyboard::KeyCount];
};