#pragma once
#include"map_generator.h"
#include<SFML\Graphics.hpp>
#include"station.h"
#include<vector>

class main_game {
public:
	main_game() = delete; //singleton

	static void initialize(map_generator* _map_gen);
	static sf::Vector2f getRelativeBounds();
	static void resize();

	static void add_station(float _relX, float _relY, station::STATION_TYPE _type);
	static time_t get_game_time();
	static void update();
	static void render(); //always render to main window
	static void cleanup();
protected:
	static std::vector<station> stations;
	static time_t game_start_time;
	static map_generator* map_gen;
};