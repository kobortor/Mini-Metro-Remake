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

	prvX = posX;
	prvY = posY;

	color = func::opposite_color(home_line->get_color());
}

train::train(metro_line * _home_line, segment track) :
	home_line(_home_line), cur_track(track), cur_stn(track.dest), prv_stn(track.orig) {
	//by default start at beginning
	status = TOWARDS_MID;
	delay_for = 500;

	posX = prv_stn->posX;
	posY = prv_stn->posY;

	prvX = posX;
	prvY = posY;

	color = func::opposite_color(home_line->get_color());
}

void train::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	if (status != DEAD) {
		float icon_size = screen_size();
		float radius = icon_size / 2;

		sf::CircleShape circ;

		circ.setRadius(radius);
		circ.setPosition(posX - radius, posY - radius);
		circ.setFillColor(color);
		targ.draw(circ);

		if (marked_for_death) {
			float thickness = main_game::get_unit_length() * 0.20;
			func::draw_thick_line(sf::Vector2f(posX - radius, posY - radius), sf::Vector2f(posX + radius, posY + radius), thickness, sf::Color::Red, targ);
			func::draw_thick_line(sf::Vector2f(posX - radius, posY + radius), sf::Vector2f(posX + radius, posY - radius), thickness, sf::Color::Red, targ);
		} else if (highlighted) {
			float thickness = main_game::get_unit_length() * 0.15;
			sf::Color pink = { 255, 128, 255 };
			func::draw_thick_line(sf::Vector2f(posX - radius, posY - radius), sf::Vector2f(posX + radius, posY + radius), thickness, pink, targ);
			func::draw_thick_line(sf::Vector2f(posX - radius, posY + radius), sf::Vector2f(posX + radius, posY - radius), thickness, pink, targ);
		}

		if (posX != prvX || posY != prvY) {
			float arrow_tip = screen_size() * 2;
			float arrow_near = screen_size();
			float base_angle = atan2f(posY - prvY, posX - prvX);
			float arrow_angle = 3.141592 / 6;

			sf::Vector2f dir(posX - prvX, posY - prvY);
			sf::Vertex vert[3];
			vert[0] = sf::Vector2f(posX + arrow_near * sin(base_angle - arrow_angle), posY + arrow_near * cos(base_angle - arrow_angle));
			vert[1] = sf::Vector2f(posX + arrow_tip * sin(base_angle), posY + arrow_tip * cos(base_angle));
			vert[2] = sf::Vector2f(posX + arrow_near * sin(base_angle + arrow_angle), posY + arrow_near * cos(base_angle + arrow_angle));

			for (int a = 0; a < 3; a++) {
				vert[a].color = color;
			}

			targ.draw(vert, 3, sf::Triangles);
		}

		for (passenger *p : passengers) {
			targ.draw(*p);
		}
	}
}

bool train::is_dead() {
	return status == DEAD;
}

sf::Vector2f train::get_pos() {
	return sf::Vector2f(posX, posY);
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
			prvX = posX;
			prvY = posY;

			posX = mid.x;
			posY = mid.y;
			status = TOWARDS_END;
		} else {
			sf::Vector2f diff = func::normalize(mid - begin) * get_speed();
			prvX = posX;
			prvY = posY;

			posX += diff.x * delta;
			posY += diff.y * delta;
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
			prvX = posX;
			prvY = posY;

			posX = end.x;
			posY = end.y;
			status = STOPPING;
			delay_for = 500;
		} else {
			sf::Vector2f diff = func::normalize(end - mid) * get_speed();
			prvX = posX;
			prvY = posY;

			posX += diff.x * delta;
			posY += diff.y * delta;
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
		if (marked_for_death) {
			status = DEAD;
		} else {
			status = STARTING;
			delay_for = 500;
		}
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
	pass->MODE = passenger::TRAIN;
	passengers.push_back(pass);
	reorg_passengers();
}

float train::screen_size() {
	return main_game::get_unit_length() * 0.5;
}

float train::get_speed() {
	//aim for something around 1 relative unit per 0.2 seconds
	//=5 units / second
	//=0.005 units per millisecond
	return 0.005f * main_game::get_unit_length();
}

void train::mark_for_death() {
	marked_for_death = true;
}

void train::reorg_passengers() {
	const int PASSENGERS_PER_ROW = 3;
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
