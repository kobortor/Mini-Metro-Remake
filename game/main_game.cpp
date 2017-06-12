#include"main_game.h"
#include"../main_window.h"
#include"../fonts.h"

map_generator* main_game::map_gen = nullptr;

void main_game::initialize(map_generator* _map_gen) {
	map_gen = _map_gen;
}
void main_game::resize() {}
void main_game::update() {}

void main_game::render() {
	sf::Text txt;
	txt.setFont(font::consola);
	txt.setCharacterSize(20);
	txt.setString("YOU ARE PLAYING THE GAME NOW!!!");
	sf::Vector2u windowSize = main_window::getInstance().getSize();
	txt.setPosition(30, 30);
	main_window::getInstance().draw(txt);
}

void main_game::cleanup() {
	delete map_gen;
}