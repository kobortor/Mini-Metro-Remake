#include<SFML\Graphics.hpp>
#include"system\system_func.h"
#include"interpol\interpol.h"
#include"menu\scrollable_menu.h"
#include"game\main_game.h"
#include"main_window.h"
#include"fonts.h"

int main() {
	font::consola.loadFromFile("assets/fonts/consola.ttf");

	main_window::initialize();

	

	interpol<interpol_func::quadratic> pol{ sys::get_millis(), sys::get_millis() + 500 };
	bool leftButtonPressed = false;

	while (main_window::getInstance().isOpen()) {
		sf::Event eve;
		while (main_window::getInstance().pollEvent(eve)) {
			if (eve.type == sf::Event::Closed) {
				main_window::getInstance().close();
			}
			switch (eve.type) {
			case sf::Event::Resized:
				main_window::handle_resize(eve.size);
				break;
			case sf::Event::Closed:
				main_window::getInstance().close();
				break;
			case sf::Event::MouseButtonPressed:
				main_window::handle_mouse_click(eve.mouseButton);
				break;
			case sf::Event::MouseButtonReleased:
				main_window::handle_mouse_release(eve.mouseButton);
				break;
			case sf::Event::MouseMoved:
				main_window::handle_mouse_move(eve.mouseMove);
				break;
			default:
				break;
			}
		}
		main_window::render();
	}
}