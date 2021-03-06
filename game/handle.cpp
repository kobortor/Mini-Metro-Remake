#include"handle.h"
#include"../functions.h"
#include"metro_line.h"
#include"main_game.h"

handle::handle(metro_line * _parent, station * _home, sf::Vector2f rel_bounds, sf::IntRect window_bounds) : parent(_parent), home(_home) {
	if (home != nullptr) {
		home->rearrange_handles(rel_bounds, window_bounds);
		resize(rel_bounds, window_bounds);
	}
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

void handle::resize(sf::Vector2f vec, sf::IntRect window_bounds) {
	//this should only be called from the parent metro_line, 
	if (parent == nullptr) {
		return;
	}

	tri[0].color = parent->get_color();
	tri[1].color = parent->get_color();
	tri[2].color = parent->get_color();

	if (home == nullptr) {
		return;
	}

	const float d2 = main_game::get_unit_length() * 2;

	sf::Vector2f orig = home->get_pos();

	tri[0].position = orig;
	tri[1].position = sf::Vector2f(d2 * sin(angle + 0.2), -d2 * cos(angle + 0.2)) + orig;
	tri[2].position = sf::Vector2f(d2 * sin(angle - 0.2), -d2 * cos(angle - 0.2)) + orig;
}

station * handle::located_at() {
	return home;
}

void handle::set_angle(float ang) {
	angle = ang;
}
