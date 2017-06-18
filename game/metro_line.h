#pragma once
#include<SFML/Graphics.hpp>
#include"station.h"
#include"segment.h"
#include"handle.h"
#include<list>

class metro_line : public sf::Drawable, public resizable {
public:
	enum HANDLE_CLICK {
		NONE, FRONT, END
	};

	//Constructs a metro_line beginning at [begin] with the color [_color]
	metro_line(station *begin, sf::Color _color, sf::Vector2f rel_bounds, sf::IntRect window_bounds);

	//Resizes this object to the new screen size
	void resize(sf::Vector2f, sf::IntRect) override;

	segment get_next_path(station* cur, station* prv);
	HANDLE_CLICK click_handle(int posX, int posY);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//Returns the color of the metro line
	sf::Color get_color();

	handle front_handle, back_handle;

	std::list<station*> stations;
	std::list<segment> segments;
protected:
	sf::Color color;
};