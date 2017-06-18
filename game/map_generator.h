#pragma once
#include<SFML\Graphics.hpp>

class map_generator {
public:
	//For inherited objects to implement
	//Adds in all stations that should be added up and until game_tick
	virtual void update_until(long long game_tick) = 0;

	//For inherited objects to implement
	//Returns the ratios of the map sides
	virtual sf::Vector2f get_relative_bounds() = 0;

	//For inherited objects to implement
	//Returns the length of a single "unit" relative to the map side ratios
	//As a general rule of thumb, a station should be 1 unit length in diameter
	//scale approximately according the original game
	//https://i.imgur.com/CbsM78B.png as an example
	virtual float get_relative_unit() = 0;
};