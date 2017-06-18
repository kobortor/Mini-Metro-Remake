#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

class metro_line;

class handle : public sf::Drawable {
public:
	handle(metro_line *_parent);
	handle(metro_line *_parent, station *_home, float _angle = 0);

	bool contained(int x, int y) const;

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Resizes this object to the new screen size
	void resize();

	station *home;
	metro_line *parent;
	float angle;
	sf::Vertex tri[3];
};