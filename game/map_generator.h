#pragma once
#include<SFML\Graphics.hpp>

class map_generator {
public:
	virtual void update_until(long long game_tick) = 0;
	virtual sf::Vector2f getRelativeBounds() = 0;
};