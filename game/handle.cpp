#include"handle.h"
#include"../functions.h"
#include"metro_line.h"

handle::handle(metro_line* _parent) : parent(_parent), home(nullptr) { }

handle::handle(metro_line* _parent, station* _home, float _angle) : parent(_parent), home(_home), angle(_angle) {
	resize();
}

bool handle::contained(int x, int y) const {
	using func::cross;
	sf::Vector2f pt(x, y);
	const sf::Vector2f &p0 = tri[0].position;
	const sf::Vector2f &p1 = tri[1].position;
	const sf::Vector2f &p2 = tri[2].position;
	return	signbit(cross(pt - p0, p1 - p0)) != signbit(cross(pt - p0, p2 - p0)) &&
			signbit(cross(pt - p1, p0 - p1)) != signbit(cross(pt - p1, p2 - p1)) &&
			signbit(cross(pt - p2, p0 - p2)) != signbit(cross(pt - p2, p1 - p2));
}

void handle::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	if (home != nullptr) {
		targ.draw(tri, 3, sf::Triangles);
	}
}

void handle::resize() {
	if (parent == nullptr) {
		return;
	}

	tri[0].color = parent->color;
	tri[1].color = parent->color;
	tri[2].color = parent->color;

	if (home == nullptr) {
		return;
	}

	const float d1 = 35;
	const float d2 = 60;

	sf::Vector2f orig = home->get_pos();

	tri[0].position = orig;
	tri[1].position = sf::Vector2f(d2 * sin(angle + 0.2), -d2 * cos(angle + 0.2)) + orig;
	tri[2].position = sf::Vector2f(d2 * sin(angle - 0.2), -d2 * cos(angle - 0.2)) + orig;
}