#include "train_button.h"
#include"../../game/main_game.h" //how many layers can we go?
#include"../../textures.h"

train_button::train_button(float _rel_wid, float _rel_ht) :
	rel_button(_rel_wid, _rel_ht) {
	texture = &textures::train_button;
}

train_button::train_button(float _relX, float _relY, float _rel_wid, float _rel_ht) :
	rel_button(_relX, _relY, _rel_wid, _rel_ht) {
	texture = &textures::train_button;
}

void train_button::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	sf::RectangleShape rect{ sf::Vector2f(wid, ht) };
	rect.setPosition(x, y);
	rect.setTexture(texture);
	targ.draw(rect);
}

void train_button::on_click(int prevX, int prevY, int curX, int curY, bool initClick) {
	//dont care, maybe make it show a highlight so we know its clicked
}

void train_button::on_release(int prevX, int prevY, int curX, int curY) {
	if (contained(curX, curY)) {
		if (main_game::CLICK_MODE == main_game::NONE) {
			main_game::CLICK_MODE = main_game::PLACE_TRAIN;
		} else if (main_game::CLICK_MODE == main_game::PLACE_TRAIN) {
			main_game::CLICK_MODE = main_game::NONE;
		}
	}
}
