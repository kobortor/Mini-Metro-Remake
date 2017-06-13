#pragma once
#include<SFML\Graphics.hpp>

class map_generator {
public:
	virtual void update_until(long long game_tick) = 0;
	virtual sf::Vector2f get_relative_bounds() = 0;
};