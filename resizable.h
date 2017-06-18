#pragma once
#include<SFML\Graphics.hpp>

class resizable {
public:
	//Resizes this object to the new screen size
	virtual void resize(sf::Vector2f rel_bounds, sf::IntRect window_bounds) = 0;
};