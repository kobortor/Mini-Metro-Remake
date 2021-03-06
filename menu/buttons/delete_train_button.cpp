#include"delete_train_button.h"
#include"../../game/main_game.h"
#include"../../textures.h"
#include"../../functions.h"
#include"../../fonts.h"

delete_train_button::delete_train_button(float _rel_wid, float _rel_ht) :
rel_button(_rel_wid, _rel_ht) {}

delete_train_button::delete_train_button(float _relX, float _relY, float _rel_wid, float _rel_ht) :
rel_button(_relX, _relY, _rel_wid, _rel_ht) {}

void delete_train_button::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	sf::RectangleShape rect{ sf::Vector2f(wid, ht) };
	rect.setPosition(x, y);
	rect.setTexture(&textures::delete_train_button);
	targ.draw(rect);
}

void delete_train_button::on_click(int prevX, int prevY, int curX, int curY, bool initClick) {
	if (initClick) {
		main_game::CLICK_MODE = main_game::DELETE_TRAIN;
	} else {
		for (train &t : main_game::trains) {
			float dist = func::hypotf(t.get_pos() - sf::Vector2f(curX, curY));
			t.highlighted = dist < select_range();
		}
	}
}

void delete_train_button::on_release(int prevX, int prevY, int curX, int curY) {
	auto iter = main_game::trains.begin();
	//destroys all trains close enough to it
	while (iter != main_game::trains.end()) {
		iter->highlighted = false;
		float dist = func::hypotf(iter->get_pos() - sf::Vector2f(curX, curY));
		if (dist < select_range()) {
			iter->mark_for_death();
		}
		iter++;
	}
	main_game::CLICK_MODE = main_game::NONE;
}

float delete_train_button::select_range() {
	return main_game::get_unit_length() * 1.25;
}
