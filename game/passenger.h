#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

class station;
class train;

class passenger : public sf::Drawable {
public:
	passenger(station::STATION_TYPE _type);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Returns the type of station that the passenger wants to go to
	station::STATION_TYPE get_type();

	//Sets the position of the passenger in pixels
	void set_pos(sf::Vector2f pos);

	//Is the passenger on a train or in station?
	enum { STATION, TRAIN } MODE;

	//Returns the size of a passenger in pixels
	static float screen_size();
protected:
	station::STATION_TYPE type;
	float posX, posY;
};