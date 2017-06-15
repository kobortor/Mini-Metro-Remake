#pragma once
#include<SFML/Graphics.hpp>
#include"station.h"
#include"segment.h"
#include"handle.h"
#include<list>

class metro_line : public sf::Drawable {
public:
	enum HANDLE_CLICK {
		NONE, FRONT, END
	};

	metro_line(station* begin, sf::Color _color);
	std::list<station*> stations;
	std::list<segment> segments;

	void resize();

	segment get_next_path(station* cur, station* prv);
	HANDLE_CLICK click_handle(int posX, int posY);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	sf::Color color;
	handle front, back;
};