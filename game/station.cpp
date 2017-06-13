#include"station.h"
#include"main_game.h"
#include"../main_window.h"

station::station(float _relX, float _relY, STATION_TYPE _type):relX(_relX), relY(_relY), type(_type) {
	resize();
}

void station::resize() {
	sf::IntRect bounds = main_game::get_window_bounds();

	posX = bounds.left + bounds.width * relX;
	posY = bounds.top + bounds.height * relX;
}

void station::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	sf::CircleShape circ{ 30 };
	circ.setPosition(posX, posY);
	circ.setFillColor(sf::Color::White);
	targ.draw(circ);
}