#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

class station;
class train;

class passenger : public sf::Drawable {
public:
	passenger(station::STATION_TYPE _type);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	station::STATION_TYPE get_type();

	float posX, posY;
	enum { STATION, TRAIN } MODE;

	static float screen_size();
protected:
	station::STATION_TYPE type;
};