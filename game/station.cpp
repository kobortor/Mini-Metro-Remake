#include"station.h"
#include"main_game.h"
#include"../main_window.h"
#include"passenger.h"
#include<bitset>

station::station(float _relX, float _relY, STATION_TYPE _type):relX(_relX), relY(_relY), type(_type) {
	resize();
}

void station::resize() {
	sf::Vector2f relBounds = main_game::get_relative_bounds();
	sf::IntRect bounds = main_game::get_window_bounds();

	posX = bounds.left + bounds.width * relX / relBounds.x;
	posY = bounds.top + bounds.height * relY / relBounds.y;
}

void station::rearrange_handles() {
	std::bitset<segment::NUM_DIRECTIONS> dirs;
	std::vector<handle*> tofix;
	for (metro_line &ml : main_game::lines) {
		for (segment &seg : ml.segments) {
			if (seg.orig == this) {
				dirs[seg.dir] = true;
			}
			if (seg.dest == this) {
				dirs[seg.get_reverse().dir] = true;
			}
		}
		if (ml.front_handle.home == this) {
			tofix.push_back(&ml.front_handle);
		}
		if (ml.back_handle.home == this) {
			tofix.push_back(&ml.back_handle);
		}
	}

	std::vector<std::pair<int, int>> angles;
	std::vector<std::vector<handle*>> handles;

	if (!dirs.any()) {
		//shouldn't happen
		angles.push_back({ 0, 8 });
		handles.emplace_back();
	} else {
		int prv = -1;
		for (int a = 0;; a++) {
			if (dirs[a % segment::NUM_DIRECTIONS]) {
				if (prv != -1) {
					angles.push_back({ prv, a });
					handles.emplace_back();
				}
				prv = a;
				if (a >= segment::NUM_DIRECTIONS) {
					break;
				}
			}
		}
	}

	for (handle* h : tofix) {
		int bestidx = 0;
		float bestang = float(angles[0].second - angles[0].first) / (handles[0].size() + 1);

		for (int a = 1; a < angles.size(); a++) {
			float newang = float(angles[a].second - angles[a].first) / (handles[a].size() + 1);
			if (newang > bestang) {
				bestang = newang;
				bestidx = a;
			}
		}
		handles[bestidx].push_back(h);
	}

	for (int a = 0; a < angles.size(); a++) {
		float deltaAng = 3.141592 / 4 * (angles[a].second - angles[a].first) / (handles[a].size() + 1);
		float curAng = 3.141592 / 4 * angles[a].first;
		for (handle *h : handles[a]) {
			curAng += deltaAng;
			h->angle = curAng;
			h->resize();
		}
	}
}

void station::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	float radius = main_game::get_station_radius();
	sf::CircleShape circ{ radius };
	circ.setPosition(posX - radius, posY - radius);
	circ.setFillColor(sf::Color::White);
	targ.draw(circ);


}

bool station::contained(int x, int y) {
	float lim = main_game::get_station_mouse_limit();
	int diffX = x - posX;
	int diffY = y - posY;
	return diffX * diffX + diffY * diffY <= lim * lim;
}

void station::add_passenger(passenger *pass) {
	passengers.push_back(pass);
}

sf::Vector2f station::get_pos() {
	return sf::Vector2f(posX, posY);
}