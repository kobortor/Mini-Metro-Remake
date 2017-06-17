#pragma once
#include<SFML\Graphics.hpp>
#include<list>

class passenger;
class train;

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
	void add_passenger(passenger * pass);
	void load(train *t);
	STATION_TYPE get_type();
	sf::Vector2f get_pos();

	static float screen_size();
protected:
	friend class train;
	void reorg_passengers();

	std::list<passenger*> passengers;

	STATION_TYPE type;
	float relX, relY;
	int posX, posY;
};