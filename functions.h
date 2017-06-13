#pragma once
#include<string>
#include<SFML\Graphics.hpp>

namespace func {
	void trim(std::string &str);
	float cross(sf::Vector2f A, sf::Vector2f B);
	float dot(sf::Vector2f A, sf::Vector2f B);
}