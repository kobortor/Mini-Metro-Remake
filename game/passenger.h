#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

class station;
class train;

class passenger : public sf::Drawable {
public:
	passenger(station::STATION_TYPE _type);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//gets the diameter of the icon on the screen
	static float icon_size();
	station::STATION_TYPE get_type();

	float posX, posY;
	enum { STATION, TRAIN } MODE;

protected:
	station::STATION_TYPE type;
};