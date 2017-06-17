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
		//TODO
	}
}

void delete_train_button::on_release(int prevX, int prevY, int curX, int curY) {
	if (main_game::CLICK_MODE == main_game::PLACE_TRAIN) {

	}
}
