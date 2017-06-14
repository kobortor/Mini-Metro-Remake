#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

class metro_line;

class handle : public sf::Drawable {
public:
	handle(metro_line *_parent);
	handle(metro_line *_parent, station *_home, float _angle = 0);

	bool contained(int x, int y) const;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	void resize();

	station *home;
	metro_line *parent;
	float angle;
	sf::Vertex tri[3];
};