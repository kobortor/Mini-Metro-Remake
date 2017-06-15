#pragma once
#include<SFML\Graphics.hpp>
#include<list>
#include"passenger.h"

class station : public sf::Drawable{
public:
	enum STATION_TYPE {
		CIRCLE, TRIANGLE, SQUARE
	};

	station(float _relX, float _relY, STATION_TYPE _type);
	void resize();
	void rearrange_handles();
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	bool contained(int x, int y);
	sf::Vector2f get_pos();
protected:
	std::list<passenger*> passengers;

	STATION_TYPE type;
	float relX, relY;
	int posX, posY;
};