#include "train_button.h"
#include"../../game/main_game.h" //how many layers can we go?
#include"../../textures.h"
#include"../../functions.h"
#include"../../fonts.h"

train_button::train_button(float _rel_wid, float _rel_ht) :
rel_button(_rel_wid, _rel_ht) {
	texture = &textures::train_button;
}

train_button::train_button(float _relX, float _relY, float _rel_wid, float _rel_ht) :
rel_button(_relX, _relY, _rel_wid, _rel_ht) {
	texture = &textures::train_button;
}

void train_button::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	const int char_size = ht * 2 / 3;

	sf::Text txt;
	txt.setCharacterSize(char_size);
	txt.setFont(font::consola);

	txt.setString(std::to_string(main_game::MAX_TRAINS - main_game::trains.size()));
	txt.setPosition(x + wid, y - char_size);
	targ.draw(txt);

	sf::RectangleShape rect{ sf::Vector2f(wid, ht) };
	rect.setPosition(x, y);
	rect.setTexture(texture);
	targ.draw(rect);

	if (main_game::MAX_TRAINS == main_game::trains.size()) {
		func::draw_thick_line(sf::Vector2f(x, y), sf::Vector2f(x + wid, y + ht), 5, sf::Color::Red, targ);
		func::draw_thick_line(sf::Vector2f(x + wid, y), sf::Vector2f(x, y + ht), 5, sf::Color::Red, targ);
	}
}

void train_button::on_click(int prevX, int prevY, int curX, int curY, bool initClick) {
	//maybe make it show a highlight so we know its clicked
	if (initClick) {
		main_game::selected_seg = nullptr;
		if (main_game::CLICK_MODE == main_game::NONE && main_game::MAX_TRAINS != main_game::trains.size()) {
			main_game::CLICK_MODE = main_game::PLACE_TRAIN;
		}
	}
}

void train_button::on_release(int prevX, int prevY, int curX, int curY) {
	if (main_game::CLICK_MODE == main_game::PLACE_TRAIN) {
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
}
