#include<SFML\Graphics.hpp>
#include"system\system_func.h"
#include"interpol\interpol.h"
#include"menu\scrollable_menu.h"
#include"game\main_game.h"
#include"main_window.h"
#include"fonts.h"
#include"textures.h"

//Program starts here
int main() {
	srand(sys::get_millis());
	font::load();
	textures::load();

	main_window::initialize();

	//Main event loop
	while (main_window::get_instance().isOpen()) {
		sf::Event eve;
		while (main_window::get_instance().pollEvent(eve)) {
			if (eve.type == sf::Event::Closed) {
				main_window::get_instance().close();
			}
			switch (eve.type) {
			case sf::Event::Resized:
				main_window::handle_resize(eve.size);
				break;
			case sf::Event::Closed:
				main_window::get_instance().close();
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
			case sf::Event::KeyPressed:
				main_window::handle_key_press(eve.key);
				break;
			case sf::Event::KeyReleased:
				main_window::handle_key_release(eve.key);
				break;
			default:
				break;
			}
		}
		main_window::render();
	}
}