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
	segment();
	segment(metro_line *_parent);

	//Adjusts the direction the the segment based on changes to the end coordinate
	void adjust_dir();

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Resizes this object to the new screen size
	void resize();

	//Returns the width the segment in pixels
	static float screen_size();

	//Gets the reversed direction segment
	//It should have the opposite beginning & ends
	//and opposite origins and destinations
	segment get_reverse() const;

	//Returns the middle point of the segment based on the direction
	//Note that mid may be at begin or end
	sf::Vector2f calc_mid() const;

	//Getters
	sf::Vector2f get_begin_point();
	sf::Vector2f get_end_point();
	station* get_origin();
	station* get_destination();
	metro_line* get_parent_line();

	//Setters
	void set_begin_point(sf::Vector2f v);
	void set_end_point(sf::Vector2f v);
	void set_origin(station *stn);
	void set_destination(station *stn);
	void set_parent_line(metro_line *ml);

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

	//The strings for each of the direction enums
	const static std::string direction_names[NUM_DIRECTIONS];

	//The ratio that the line's width expands by if hovered over
	const static float hover_ratio;

	//checked true if the cursor is the train and is hovering over it
	bool highlighted = false;
private:
	metro_line* parent_line;
	sf::Vector2f begin, end;
	station *orig = nullptr, *dest = nullptr;
};