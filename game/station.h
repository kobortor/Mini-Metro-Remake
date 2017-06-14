#pragma once
#include<SFML\Graphics.hpp>

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
	sf::Vector2i get_pos();
protected:

	STATION_TYPE type;
	float relX, relY;
	int posX, posY;
};