#pragma once
#include<SFML\Graphics.hpp>
#include"metro_line.h"
#include"passenger.h"

class train : public sf::Drawable {
public:
	train(metro_line *_home_line);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//will return true once it can't find any more track to carry on
	bool is_dead();

	sf::Vector2f get_pos();
	void resize();

	//milliseconds of change
	void update(long long delta);

protected:
	float posX, posY;
	segment cur_track;
	float amnt_done;
	std::list<passenger*> passengers;

	//tries to find next path in metro line
	void seek();

	metro_line *home_line;

	enum {
		TOWARDS_MID, TOWARDS_END, SEEKING, DEAD
	} status;
};