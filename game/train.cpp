#include"train.h"
#include"../functions.h"
#include"main_game.h"
#include<iostream>

train::train(metro_line * _home_line):home_line(_home_line) {
	//by default start at beginning
	cur_track = home_line->get_next_path(home_line->stations.front(), nullptr);
	if (cur_track.orig == nullptr) {
		status = DEAD;
	}
	status = TOWARDS_MID;
	posX = cur_track.begin.x;
	posY = cur_track.begin.y;
}

void train::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	if (status != DEAD) {
		sf::CircleShape circ{ 8 };
		circ.setFillColor(sf::Color::Green);
		circ.setPosition(posX - 8, posY - 8);
		targ.draw(circ);
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
	if (status == SEEKING) {
		seek();
		return;
	}
	
	sf::Vector2f &begin = cur_track.begin;
	sf::Vector2f mid = cur_track.calc_mid();
	sf::Vector2f &end = cur_track.end;

	if (status == TOWARDS_MID && begin == mid) {
		status = TOWARDS_END;
	}
	if (status == TOWARDS_END && mid == end) {
		status = SEEKING;
	}

	if (status == TOWARDS_MID) {
		sf::Vector2f diff = func::normalize(mid - begin);
		posX += diff.x * delta / 10;
		posY += diff.y * delta / 10;
		amnt_done = hypot(posX - begin.x, posY - begin.y) / hypot(mid.x - begin.x, mid.y - begin.y);

		if (amnt_done >= 1) {
			posX = mid.x;
			posY = mid.y;
			status = TOWARDS_END;
		}
	} else if (status == TOWARDS_END) {
		sf::Vector2f diff = func::normalize(end - mid);
		posX += diff.x * delta / 10;
		posY += diff.y * delta / 10;
		amnt_done = hypot(posX - mid.x, posY - mid.y) / hypot(end.x - mid.x, end.y - mid.y);
		if (amnt_done >= 1) {
			posX = end.x;
			posY = end.y;
			status = SEEKING;
		}
	}
}

void train::seek() {
	if (func::find_iter(main_game::lines.begin(), main_game::lines.end(), home_line) == main_game::lines.end()) {
		status = DEAD;
	} else {
		cur_track = home_line->get_next_path(cur_track.dest, cur_track.orig);
		if (cur_track.orig == nullptr) {
			status = DEAD;
		} else {
			status = TOWARDS_MID;
		}
	}
}
