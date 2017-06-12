#pragma once
#include<SFML\Graphics.hpp>

class station : public sf::Drawable{
public:
	enum STATION_TYPE {
		CIRCLE, TRIANGLE, SQUARE
	};

	station(float _relX, float _relY, STATION_TYPE _type);
	void resize();
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
protected:

	STATION_TYPE type;
	float relX, relY;
	int posX, posY;
};