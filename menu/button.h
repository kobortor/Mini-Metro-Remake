#pragma once
#include "clickable.h"
#include<SFML\Graphics.hpp>

class button : public clickable, public sf::Drawable {
public:
	//Size of the button in pixels
	button(int _wid, int _ht);

	//Position and size of the button in pixels
	button(int _x, int _y, int _wid, int _ht);

	//Sets the position of the button in pixels
	void setPos(int _x, int _y);

	//Sets the size of the button in pixels
	void setSize(int _wid, int _ht);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

	//Returns the position of the button in pixels
	sf::Vector2f get_pos();

	//Returns the size of the button in pixels
	sf::Vector2f get_size();

	//Returns true of the coordinate is contained within the button, false otherwise
	bool contained(int _x, int _y);
protected:
	int x, y;
	int wid, ht;
};