#pragma once
#include<SFML/Graphics.hpp>
#include"station.h"
#include"segment.h"
#include<list>

class metro_line : public sf::Drawable {
public:
	metro_line(station* begin);
	std::list<station*> stations;
	std::list<segment> segments;

	station* get_next_station(station* prev, station* cur);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};