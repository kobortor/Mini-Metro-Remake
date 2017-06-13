#pragma once
#include"map_generator.h"
#include<fstream>
#include<string>
#include<queue>

class file_map_generator : public map_generator {
public:
	file_map_generator(std::string file_name);
	void update_until(long long game_tick);
	sf::Vector2f get_relative_bounds() override;
protected:
	sf::Vector2f rel_bounds;
	std::queue<sf::Vector2f> points;
	long long last_update = 0;
};