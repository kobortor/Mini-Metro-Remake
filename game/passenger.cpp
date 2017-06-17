#include "passenger.h"
#include<cstdlib>
#include<iostream>

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

	sf::CircleShape circ(icon_size() / 2, num_sides);
	circ.setPosition(posX, posY);

	if (MODE == STATION) {
		circ.setFillColor(sf::Color::Red);
	} else {
		circ.setFillColor(sf::Color::Green);
	}

	targ.draw(circ);
}

float passenger::icon_size() {
	return 10;
}

station::STATION_TYPE passenger::get_type() {
	//do this to avoid accidentally changing it
	return type;
}

