#include"train.h"
#include"../functions.h"
#include"main_game.h"
#include<iostream>

train::train(metro_line * _home_line, station *_cur_stn) :
	home_line(_home_line), cur_stn(_cur_stn), prv_stn(nullptr) {
	//by default start at beginning
	status = LOADING;

	cur_track.begin = cur_stn->get_pos();
	cur_track.end = cur_stn->get_pos();

	posX = cur_stn->posX;
	posY = cur_stn->posY;
}

train::train(metro_line * _home_line, segment track) :
	home_line(_home_line), cur_track(track), cur_stn(track.dest), prv_stn(track.orig) {
	//by default start at beginning
	status = TOWARDS_MID;
	delay_for = 500;
	sf::Vector2f &begin = cur_track.begin;
	sf::Vector2f &end = cur_track.end;

	posX = prv_stn->posX;
	posY = prv_stn->posY;
}

void train::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	if (status != DEAD) {
		float radius = icon_size() / 2;
		sf::CircleShape circ{ radius };
		circ.setFillColor(sf::Color::Green);
		circ.setPosition(posX - radius, posY - radius);
		targ.draw(circ);

		for (passenger *p : passengers) {
			targ.draw(*p);
		}
	}
}

bool train::is_dead() {
	return status == DEAD;
}

sf::Vector2f train::get_pos() {
	return sf::Vector2f();
}

void train::resize() {
	//since this is separate from rest of the tracks, we need to do this
	cur_track.resize();

	if (status == TOWARDS_MID) {
		sf::Vector2f &begin = cur_track.begin;
		sf::Vector2f mid = cur_track.calc_mid();
		sf::Vector2f diff = begin + (mid - begin) * amnt_done;
		posX = diff.x;
		posY = diff.y;
	} else if (status == TOWARDS_END) {
		sf::Vector2f mid = cur_track.calc_mid();
		sf::Vector2f &end = cur_track.end;
		sf::Vector2f diff = mid + (end - mid) * amnt_done;
		posX = diff.x;
		posY = diff.y;
	}
}

void train::update(long long delta) {
	if (status == DEAD) {
		return;
	}

	sf::Vector2f &begin = cur_track.begin;
	sf::Vector2f mid = cur_track.calc_mid();
	sf::Vector2f &end = cur_track.end;

	if (status == TOWARDS_MID && begin == mid) {
		status = TOWARDS_END;
	}

	if (status == TOWARDS_MID) {
		if (delay_for <= 0) {
			//carry on
		} else {
			delay_for -= delta;
			return;
		}
		if (hypotf(begin.x - mid.x, begin.y - mid.y) < 3) {
			posX = mid.x;
			posY = mid.y;
			status = TOWARDS_END;
		} else {
			sf::Vector2f diff = func::normalize(mid - begin);
			posX += diff.x * delta / 10;
			posY += diff.y * delta / 10;
			amnt_done = hypot(posX - begin.x, posY - begin.y) / hypot(mid.x - begin.x, mid.y - begin.y);

			if (amnt_done >= 1) {
				posX = mid.x;
				posY = mid.y;
				status = TOWARDS_END;
			}
		}
	} else if (status == TOWARDS_END) {
		if (delay_for <= 0) {
			//carry on
		} else {
			delay_for -= delta;
			return;
		}
		if (hypotf(mid.x - end.x, mid.y - end.y) < 3) {
			posX = end.x;
			posY = end.y;
			status = STOPPING;
			delay_for = 500;
		} else {
			sf::Vector2f diff = func::normalize(end - mid);
			posX += diff.x * delta / 10;
			posY += diff.y * delta / 10;
			amnt_done = hypot(posX - mid.x, posY - mid.y) / hypot(end.x - mid.x, end.y - mid.y);
			if (amnt_done >= 1) {
				posX = end.x;
				posY = end.y;
				status = STOPPING;
				delay_for = 500;
			}
		}
	} else if (status == STOPPING) {
		delay_for -= delta;
		if (delay_for <= 0) {
			status = LOADING;
		}
	} else if (status == LOADING) {
		cur_stn->load(this);
		status = STARTING;
		delay_for = 500;
	} else if (status == STARTING) {
		delay_for -= delta;
		if (delay_for <= 0) {
			status = SEEKING;
		}
	} else if (status == SEEKING) {
		seek();
	}

	reorg_passengers();
}

int train::space_left() {
	return 6 - passengers.size();
}

void train::add_passenger(passenger *pass) {
	passengers.push_back(pass);
	reorg_passengers();
}

float train::icon_size() {
	return 15;
}

void train::reorg_passengers() {
	const int PASSENGERS_PER_ROW = 3;
	const float padding = 0.5;
	float diam = passenger::icon_size();

	//cheap round up
	int num_rows = (passengers.size() + PASSENGERS_PER_ROW - 1) / PASSENGERS_PER_ROW;
	auto iter = passengers.begin();
	float pXpos = posX + icon_size() / 2 + padding * diam;
	float pYpos = posY - icon_size() / 2 - num_rows * diam * (1 + padding);

	int idx = 0;
	while (iter != passengers.end()) {
		if (idx >= PASSENGERS_PER_ROW) {
			pXpos -= (PASSENGERS_PER_ROW - 1) * diam * (1 + padding);
			pYpos += diam * (1 + padding);
			idx = 0;
		} else {
			pXpos += diam * (1 + padding);
		}
		(*iter)->posX = pXpos;
		(*iter)->posY = pYpos;

		idx++;
		iter++;
	}
}

void train::seek() {
	if (func::find_iter(main_game::lines.begin(), main_game::lines.end(), home_line) == main_game::lines.end()) {
		status = DEAD;
	} else {
		cur_track = home_line->get_next_path(cur_stn, prv_stn);
		if (cur_track.orig == nullptr) {
			status = DEAD;
		} else {
			if (cur_track.orig != cur_stn) {
				printf("THIS IS NOT SUPPOSED TO HAPPEN!\n");
			}
			cur_stn = cur_track.dest;
			prv_stn = cur_track.orig;
			status = TOWARDS_MID;
		}
	}
}
