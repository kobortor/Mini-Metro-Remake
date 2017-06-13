#pragma once
#include<SFML\Graphics.hpp>

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
class segment : public sf::Drawable {
public:
	sf::Vector2f begin, mid, end;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};