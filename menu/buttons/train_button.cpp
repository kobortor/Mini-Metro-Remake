#include "train_button.h"

train_button::train_button(float _rel_wid, float _rel_ht) :
	rel_button(_rel_wid, _rel_ht) {
	texture = new sf::Texture;
	texture->loadFromFile("assets/icons/train.png");
}

train_button::train_button(float _relX, float _relY, float _rel_wid, float _rel_ht) :
	rel_button(_relX, _relY, _rel_wid, _rel_ht) {
	texture = new sf::Texture;
	texture->loadFromFile("assets/icons/train.png");
}

void train_button::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	sf::RectangleShape rect{ sf::Vector2f(wid, ht) };
	rect.setPosition(x, y);
	rect.setTexture(texture);
	targ.draw(rect);
}

void train_button::on_click(int prevX, int prevY, int curX, int curY, bool initClick) {

}

void train_button::on_release(int prevX, int prevY, int curX, int curY) {

}
