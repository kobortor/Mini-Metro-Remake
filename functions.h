#pragma once
#include<string>
#include<SFML\Graphics.hpp>

namespace func {
	void trim(std::string &str);

	//if X is the angle between the 2 vectors, cross(A,B) gets |A| * |B| * sin(X)
	float cross(sf::Vector2f A, sf::Vector2f B);

	//if X is the angle between the 2 vectors, dot(A,B) gets |A| * |B| * cos(X)
	float dot(sf::Vector2f A, sf::Vector2f B);
}