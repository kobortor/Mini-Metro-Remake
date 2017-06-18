#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

/*
--------------------------------
---RULES FOR DRAWING SEGMENTS---
--------------------------------

A station is first selected within radius R1.
Only when we go out of this radius do we start drawing.

Divide the map into 8 sections, NSEW, and the in-betweens
When we first go out of the selection radius, find the section it is closest to.
We can use cross product to achieve this.
Switch the direction only when it crosses over another section.
If N is 0 degreees, the line will only switch once it crosses 45 degrees or -45 (315) degrees. 

       X
      /
     /
Y---/

*/

//A short line, many segments joined together will form a full line
//When a train goes through a line, it will create temporary segments, then ask the full line for the next station

class metro_line;

class segment : public sf::Drawable {
public:
	sf::Vector2f begin, end;
	station *orig = nullptr, *dest = nullptr;

	//checked true if the cursor is the train and is hovering over it
	bool highlighted = false;

	segment();
	segment(metro_line *_parent);

	void adjust_dir();

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Resizes this object to the new screen size
	void resize();
	static float screen_size();

	metro_line* parent;
	segment get_reverse() const;
	sf::Vector2f calc_mid() const;

	enum direction {
		NORTH = 0,
		NORTH_EAST = 1,
		EAST = 2,
		SOUTH_EAST = 3,
		SOUTH = 4,
		SOUTH_WEST = 5,
		WEST = 6,
		NORTH_WEST = 7,
		NUM_DIRECTIONS = 8
	} dir = NORTH;

	//unit vectors in each of the 8 directions
	const static sf::Vector2f unit_direction[NUM_DIRECTIONS];

	const static std::string direction_names[NUM_DIRECTIONS];

	const static float hover_ratio;
private:
};