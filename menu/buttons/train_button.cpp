#include "train_button.h"
#include"../../game/main_game.h" //how many layers can we go?
#include"../../textures.h"
#include"../../functions.h"
#include"../../fonts.h"

train_button::train_button(float _rel_wid, float _rel_ht) :
rel_button(_rel_wid, _rel_ht) {}

train_button::train_button(float _relX, float _relY, float _rel_wid, float _rel_ht) :
rel_button(_relX, _relY, _rel_wid, _rel_ht) {}

void train_button::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	const int char_size = ht * 2 / 3;

	sf::Text txt;
	txt.setCharacterSize(char_size);
	txt.setFont(font::consola);

	txt.setString(std::to_string(main_game::num_trains_left()));
	txt.setPosition(x + wid, y - char_size);
	targ.draw(txt);

	sf::RectangleShape rect{ sf::Vector2f(wid, ht) };
	rect.setPosition(x, y);
	rect.setTexture(&textures::train_button);
	targ.draw(rect);

	if (main_game::num_trains_left() == 0) {
		float thickness = main_game::get_unit_length() * 0.15;
		func::draw_thick_line(sf::Vector2f(x, y), sf::Vector2f(x + wid, y + ht), thickness, sf::Color::Red, targ);
		func::draw_thick_line(sf::Vector2f(x + wid, y), sf::Vector2f(x, y + ht), thickness, sf::Color::Red, targ);
	}
}

void train_button::on_click(int prevX, int prevY, int curX, int curY, bool initClick) {
	//maybe make it show a highlight so we know its clicked
	if (initClick) {
		main_game::selected_seg = nullptr;
		if (main_game::num_trains_left() != 0) {
			main_game::CLICK_MODE = main_game::PLACE_TRAIN;
		}
	} else {
		main_game::selected_seg = nullptr;
		for (metro_line &ml : main_game::lines) {
			for (segment &segs : ml.segments) {
				segs.highlighted = false;
				if (main_game::selected_seg != nullptr) {
					continue;
				}
				sf::Vector2f mid = segs.calc_mid();
				float dist_to = std::min(func::dist_to_line(segs.begin, mid, sf::Vector2f(curX, curY)),
					func::dist_to_line(mid, segs.end, sf::Vector2f(curX, curY)));
				if (dist_to < select_range()) {
					//essentially a break and reset statement
					main_game::selected_seg = &segs;
					segs.highlighted = true;
				}
			}
		}
	}
}

void train_button::on_release(int prevX, int prevY, int curX, int curY) {
	if (main_game::selected_seg != nullptr) {
		float d1 = func::hypotf(main_game::selected_seg->begin - sf::Vector2f(curX, curY));
		float d2 = func::hypotf(main_game::selected_seg->end - sf::Vector2f(curX, curY));
		if (d1 < d2) {
			main_game::trains.emplace_back(main_game::selected_seg->parent, *main_game::selected_seg);
		} else {
			main_game::trains.emplace_back(main_game::selected_seg->parent, main_game::selected_seg->get_reverse());
		}
		main_game::selected_seg->highlighted = false;
	}
	main_game::selected_seg = nullptr;
	main_game::CLICK_MODE = main_game::NONE;
}

float train_button::select_range() {
	return main_game::get_unit_length() * 0.75;
}
