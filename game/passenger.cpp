#include "passenger.h"
#include<cstdlib>
#include<iostream>

passenger::passenger(station * _cur_stn, station::STATION_TYPE _type) :
	cur_stn(_cur_stn), type(_type), MODE(STATION) {
}

void passenger::load_to(train * _cur_train) {
	if (MODE == TRAIN) {
		printf("ERROR! LOADING TO TRAIN WHILE ON TRAIN!\n");
		exit(0);
	}
	MODE = TRAIN;
	cur_train = _cur_train;
}

void passenger::unload_to(station * _cur_stn) {
	if (MODE == STATION) {
		printf("ERROR! LOADING TO STATION WHILE IN STATION!\n");
		exit(0);
	}
	MODE = STATION;
	cur_stn = _cur_stn;
}

void passenger::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	sf::CircleShape circ(icon_size() / 2);
	circ.setPosition(posX, posY);
	circ.setFillColor(sf::Color::Red);

	targ.draw(circ);
}

float passenger::icon_size() {
	return 10;
}

