#include"handle.h"

handle::handle(metro_line* _parent) : parent(_parent), home(nullptr) { }

handle::handle(metro_line* _parent, station* _home, float _angle) : parent(_parent), home(_home), angle(_angle) {
	resize();
}

void handle::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	if (home != nullptr) {
		targ.draw(tri, 3, sf::Triangles);
	}
}

void handle::resize() {
	const float d1 = 35;
	const float d2 = 60;

	sf::Vector2f orig = sf::Vector2f(home->get_pos());
	tri[0].position = sf::Vector2f(d1 * cos(angle), d1 * sin(angle)) + orig;
	tri[1].position = sf::Vector2f(d2 * cos(angle + 0.2), d2 * sin(angle + 0.2)) + orig;
	tri[2].position = sf::Vector2f(d2 * cos(angle - 0.2), d2 * sin(angle - 0.2)) + orig;

	tri[0].color = sf::Color::Red;
	tri[1].color = sf::Color::Red;
	tri[2].color = sf::Color::Red;
}