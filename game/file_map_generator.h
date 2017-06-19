#pragma once
#include"map_generator.h"
#include<fstream>
#include<string>
#include<queue>

class file_map_generator : public map_generator {
public:
	//Constructs the generator based on the name of the file
	file_map_generator(std::string file_name);

	//Overridden
	void update_until(long long game_tick) override;

	//Overridden
	sf::Vector2f get_relative_bounds() override;

	//Overridden
	float get_relative_unit() override;
protected:
	float rel_unit;
	sf::Vector2f rel_bounds;
	std::vector<sf::Vector2f> points;

	int passenger_spawned = 0;
	int station_spawned = 0;
	int next_passenger_delay = 7500;
	int next_station_delay = 2000;
	long long last_passenger = 0;
	long long last_update = 0;
};