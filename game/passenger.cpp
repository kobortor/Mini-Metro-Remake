#include "passenger.h"
#include<cstdlib>
#include<iostream>
#include"main_game.h"

passenger::passenger(station::STATION_TYPE _type) :
	type(_type), MODE(STATION) {
}

void passenger::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	int num_sides;
	switch (type) {
	case station::TRIANGLE:
		num_sides = 3;
		break;
	case station::SQUARE:
		num_sides = 4;
		break;
	case station::CIRCLE:
		num_sides = 30;
		break;
	default:
		printf("This should not happen!\n");
		break;
	}

	float radius = screen_size() / 2;
	sf::CircleShape circ(radius, num_sides);
	circ.setPosition(posX - radius, posY - radius);

	if (MODE == STATION) {
		circ.setFillColor(sf::Color::Red);
	} else {
		circ.setFillColor(sf::Color::Green);
	}

	targ.draw(circ);
}

station::STATION_TYPE passenger::get_type() {
	//do this to avoid accidentally changing it
	return type;
}

void passenger::set_pos(sf::Vector2f pos) {
	posX = pos.x;
	posY = pos.y;
}

float passenger::screen_size() {
	return main_game::get_unit_length() * 0.5;
}

