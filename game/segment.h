#pragma once
#include<SFML\Graphics.hpp>

//A short line, many segments joined together will form a full line
//When a train goes through a line, it will create temporary segments, then ask the full line for the next station
class segment : public sf::Drawable {
public:
	sf::Vector2f begin, end;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};