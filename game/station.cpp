#include"station.h"
#include"main_game.h"
#include"../main_window.h"
#include"passenger.h"
#include<bitset>
#include"graph.h"
#include"../functions.h"
#include"game_variables.h"

station::station(float _relX, float _relY, STATION_TYPE _type) :relX(_relX), relY(_relY), type(_type) {
	resize(sf::Vector2f(1,1), sf::IntRect(0,0,1,1));
}

void station::resize(sf::Vector2f rel_bounds, sf::IntRect window_bounds) {
	posX = window_bounds.left + window_bounds.width * relX / rel_bounds.x;
	posY = window_bounds.top + window_bounds.height * relY / rel_bounds.y;

	reorg_passengers();
}

void station::rearrange_handles(sf::Vector2f rel_bounds, sf::IntRect window_bounds) {
	std::bitset<segment::NUM_DIRECTIONS> dirs;
	std::vector<handle*> tofix;
	for (metro_line &ml : main_game::lines) {
		for (segment &seg : ml.segments) {
			if (seg.get_origin() == this) {
				dirs[seg.dir] = true;
			}
			if (seg.get_destination() == this) {
				dirs[seg.get_reverse().dir] = true;
			}
		}
		if (ml.front_handle.located_at() == this) {
			tofix.push_back(&ml.front_handle);
		}
		if (ml.back_handle.located_at() == this) {
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
			h->set_angle(curAng);
			h->resize(rel_bounds, window_bounds);
		}
	}
}

station::STATION_TYPE station::get_type() {
	return type;
}

void station::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	int point_count;
	switch (type) {
	case TRIANGLE:
		point_count = 3;
		break;
	case CIRCLE:
		point_count = 30;
		break;
	case SQUARE:
		point_count = 4;
		break;
	}

	float inner_radius = screen_size() / 2 * 0.75;
	float outer_radius = screen_size() / 2;

	sf::CircleShape circ(outer_radius, point_count);
	circ.setPosition(posX - outer_radius, posY - outer_radius);
	circ.setFillColor(sf::Color::Black);
	targ.draw(circ);

	circ.setPosition(posX - inner_radius, posY - inner_radius);
	circ.setRadius(inner_radius);

	sf::Color col = sf::Color::White;
	if (overflow_amnt > 0) {
		float warn_radius = screen_size() * 2;

		float amnt = overflow_amnt / game_variables::get_overflow_limit();
		int sub = std::min(255, int(amnt * 255));
		col.g -= sub;
		col.b -= sub;

		sf::Color col = sf::Color::Black;
		col.a = 32 + sub / 4;
		func::draw_semi_circle(sf::Vector2f(posX, posY), warn_radius, 0, 3.141592 * 2 * amnt, 60, col, targ);
	}

	circ.setFillColor(col);
	targ.draw(circ);

	for (const passenger *pass : passengers) {
		targ.draw(*pass);
	}
}

bool station::contained(int x, int y) {
	float lim = screen_size() / 2;
	int diffX = x - posX;
	int diffY = y - posY;
	return diffX * diffX + diffY * diffY <= lim * lim;
}

void station::add_passenger(passenger *pass) {
	pass->MODE = passenger::STATION;
	passengers.push_back(pass);
	reorg_passengers();
}

void station::load(train *t) {
	if (t->is_marked_for_death()) {
		return;
	}

	auto iter = passengers.begin();
	while(iter != passengers.end()) {
		if (t->get_num_passengers() >= game_variables::get_train_capacity()) {
			break;
		}

		std::list<station*> other_stn;
		std::list<station*> destinations;
		for (station &stn : main_game::stations) {
			if (stn.type == (*iter)->get_type()) {
				destinations.push_back(&stn);
			}
		}

		for (station *stn : t->get_home_line()->stations) {
			if (stn != this) {
				other_stn.push_back(stn);
			}
		}

		//inefficient, might optimize later
		int other_dist = graph::shortest_dist(other_stn, destinations);
		int this_dist = graph::shortest_dist(std::list<station*>{this}, destinations);

		if (this_dist != -1 && other_dist < this_dist) {
			auto tmp = iter;
			iter++;
			(*tmp)->MODE = passenger::TRAIN;
			t->add_passenger(*tmp);
			passengers.erase(tmp);
		} else {
			iter++;
		}
	}

	reorg_passengers();
}

void station::update(long long delta) {
	if (passengers.size() >= game_variables::get_max_passengers()) {
		overflow_amnt += delta;
	} else {
		overflow_amnt -= delta * game_variables::get_overflow_recovery_rate();
		if (overflow_amnt < 0) {
			overflow_amnt = 0;
		}
	}
}

sf::Vector2f station::get_pos() {
	return sf::Vector2f(posX, posY);
}

bool station::is_game_over() {
	return overflow_amnt >= game_variables::get_overflow_limit();
}

float station::screen_size() {
	return main_game::get_unit_length() * 1.0;
}

void station::reorg_passengers() {
	const int PASSENGERS_PER_ROW = 6;
	const float padding = 0.25;

	//cheap round up
	int num_rows = (passengers.size() + PASSENGERS_PER_ROW - 1) / PASSENGERS_PER_ROW;
	auto iter = passengers.begin();
	float pXpos = posX + screen_size() / 2 - passenger::screen_size() * (1 + padding);
	float pYpos = posY - num_rows * passenger::screen_size() * (1 + padding);

	int idx = 0;
	while (iter != passengers.end()) {
		if (idx >= PASSENGERS_PER_ROW) {
			pXpos -= (PASSENGERS_PER_ROW - 1) * passenger::screen_size() * (1 + padding);
			pYpos += passenger::screen_size() * (1 + padding);
			idx = 0;
		} else {
			pXpos += passenger::screen_size() * (1 + padding);
		}
		(*iter)->set_pos(sf::Vector2f(pXpos, pYpos));

		idx++;
		iter++;
	}
}
