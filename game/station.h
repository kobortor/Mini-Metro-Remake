#pragma once
#include<SFML\Graphics.hpp>
#include<list>

class passenger;
class train;

class station : public sf::Drawable{
public:
	//Which type of station will determine what passengers will want to go here, and how to draw it
	enum STATION_TYPE {
		CIRCLE, TRIANGLE, SQUARE
	};

	//The x position and y position relative to the screen ratios
	//also the type of the station
	station(float _relX, float _relY, STATION_TYPE _type);

	//Resizes this object to the new screen size
	void resize();

	//Rearrange the handles around this station
	void rearrange_handles();

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	bool contained(int x, int y);
	void add_passenger(passenger * pass);
	void load(train *t);
	void update(long long delta);
	STATION_TYPE get_type();
	sf::Vector2f get_pos();
	bool is_game_over();

	static float screen_size();
protected:
	float overflow_amnt = 0;
	void reorg_passengers();

	std::list<passenger*> passengers;

	STATION_TYPE type;
	float relX, relY;
	int posX, posY;
};