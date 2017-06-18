#pragma once
#include<SFML\Graphics.hpp>
#include"../resizable.h"
#include<list>

class passenger;
class train;

class station : public sf::Drawable, public resizable {
public:
	//Which type of station will determine what passengers will want to go here, and how to draw it
	enum STATION_TYPE {
		CIRCLE, TRIANGLE, SQUARE
	};

	//The x position and y position relative to the screen ratios
	//also the type of the station
	station(float _relX, float _relY, STATION_TYPE _type, sf::Vector2f rel_bounds, sf::IntRect window_bounds);

	//Overridden
	void resize(sf::Vector2f rel_bounds, sf::IntRect window_bounds) override;

	//Rearrange the handles around this station
	void rearrange_handles(sf::Vector2f rel_bounds, sf::IntRect window_bounds);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Returns true if the coordinate is contained within the station, false otherwise
	bool contained(int x, int y);

	//Adds the passenger to the station
	void add_passenger(passenger * pass);

	//Add all passengers that wants to get on the train, until either nobody wants to go or the train is full
	void load(train *t);

	//Updates the station
	//[delta] is the number of milliseconds since last update
	void update(long long delta);

	//Gets the type of the station
	STATION_TYPE get_type();

	//Gets the position of the station in pixels
	sf::Vector2f get_pos();

	//Returns true if station has overflowed for too long
	bool is_game_over();
	
	//Returns the size of the station in pixels
	static float screen_size();
protected:
	//Reorganizes the passengers in the train to fit a certain pattern
	void reorg_passengers();

	float overflow_amnt = 0;

	std::list<passenger*> passengers;

	STATION_TYPE type;
	float relX, relY;
	int posX, posY;
};