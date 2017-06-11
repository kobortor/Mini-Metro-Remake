#include"main_game.h"
#include"../main_window.h"
#include"../fonts.h"

void main_game::initialize() {}
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