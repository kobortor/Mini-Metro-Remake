#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

class handle : public sf::Drawable {
public:
	handle();
	handle(station *_home, float _angle = 0);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	void resize();

	station* home;
	float angle;
	sf::Vertex tri[3];
};