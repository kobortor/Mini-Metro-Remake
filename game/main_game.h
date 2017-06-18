#pragma once
#include"map_generator.h"
#include<SFML\Graphics.hpp>
#include"train.h"
#include"../menu/buttons/train_button.h"
#include"../menu/buttons/delete_train_button.h"

class main_game {
public:
	main_game() = delete; //singleton

	//what mode is the user's mouse in
	//aka what action is it doing
	enum CLICK_MODE_TYPE { NONE, LINE_EDIT_FRONT, LINE_EDIT_BACK, PLACE_TRAIN, DELETE_TRAIN };

	//Starts the class
	//_map_gen is the object that generates the map for us
	static void initialize(map_generator* _map_gen);

	//Gets relative ratio of window
	static sf::Vector2f get_relative_bounds();

	//Gets the bounds of the game window within the actual window. Measured in pixels.
	static sf::IntRect get_window_bounds(); //gets the position within the window

	//Draws the game state
	static void render(); //always render to main window

	//Cleans up the game state to get ready for another game
	static void cleanup();

	//Resizes everything in the game to be relative to the new window size
	static void resize();

	//Updates the game state
	static void update();

	//Adds a station at that coordinate
	static void add_station(float _relX, float _relY, station::STATION_TYPE _type);

	//Gets milliseconds since the start of the game
	static time_t get_game_time();

	//Set this line to be the one currently edited
	//mode should be either EDIT_LINE_BACK or EDIT_LINE_FRONT to specify which side is being edited
	static void set_edit_line(metro_line* line, CLICK_MODE_TYPE mode);

	//Returns true of the game is over, false otherwise
	static bool is_game_over();

	//Returns the number of trains that the player is still allowed to place
	static int num_trains_left();

	//Returns the length of a single "unit" in pixels
	//As a general rule of thumb, a station should be 1 unit length in diameter
	//scale approximately according the original game
	//https://i.imgur.com/CbsM78B.png as an example
	static float get_unit_length();

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

	/*
	---------------
	---VARIABLES---
	---------------
	*/
	static std::list<metro_line> lines;
	static std::list<station> stations;
	static std::list<train> trains;

	//the line that is currently being edited
	static metro_line* edit_line;

	//the segment that is currently being edited
	static segment edit_seg;

	//the segment that is currently being selected (to place a train on)
	static segment* selected_seg;

	//what mode is the user's mouse in
	//aka what action is it doing
	static CLICK_MODE_TYPE CLICK_MODE;
private:
	static int trains_left;
	static std::list<sf::Color> avail_colors;
	static float unit_length;
	static time_t game_start_time;
	static time_t last_update;
	static map_generator* map_gen;
	static sf::RectangleShape background;
	static sf::IntRect window_bounds;
	static int prvX, prvY;
	static bool mouse_button_pressed[sf::Mouse::ButtonCount];
	static bool key_pressed[sf::Keyboard::KeyCount];

	static train_button *train_btn;
	static delete_train_button *del_train_btn;
};