#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"
#include"../resizable.h"

class metro_line;

class handle : public sf::Drawable, public resizable {
public:
	//Constructs the handle based on the line of its parent and that station it's home to
	handle(metro_line *_parent, station *_home, sf::Vector2f rel_bounds, sf::IntRect window_bounds);

	//Returns true if coordinate is contained in the handle, false otherwise
	bool contained(int x, int y) const;

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Overridden
	void resize(sf::Vector2f vec, sf::IntRect window_bounds) override;

	//Returns the station the handle is located at
	station* located_at();

	//Sets the angle that the handle should point towards in radians
	void set_angle(float ang);
protected:
	station *home;
	metro_line *parent;
	float angle;
	sf::Vertex tri[3];
};