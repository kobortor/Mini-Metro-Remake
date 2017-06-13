#include"station.h"
#include"main_game.h"
#include"../main_window.h"

station::station(float _relX, float _relY, STATION_TYPE _type):relX(_relX), relY(_relY), type(_type) {
	resize();
}

void station::resize() {
	sf::Vector2f relBounds = main_game::get_relative_bounds();
	sf::IntRect bounds = main_game::get_window_bounds();

	posX = bounds.left + bounds.width * relX / relBounds.x;
	posY = bounds.top + bounds.height * relY / relBounds.y;
}

void station::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	sf::CircleShape circ{ 15 };
	circ.setPosition(posX - 15, posY - 15);
	circ.setFillColor(sf::Color::White);
	targ.draw(circ);
}

bool station::contained(int x, int y) {
	int diffX = x - posX;
	int diffY = y - posY;
	return diffX * diffX + diffY * diffY <= 30 * 30;
}

sf::Vector2i station::get_pos() {
	return{ posX, posY };
}