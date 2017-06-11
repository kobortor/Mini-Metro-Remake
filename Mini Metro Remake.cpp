#include<SFML\Graphics.hpp>
#include"system\system_func.h"
#include"interpol\interpol.h"
#include"menu\scrollable_menu.h"
#include"main_window.h"
#include"fonts.h"

int main() {
	font::consola.loadFromFile("assets/fonts/consola.ttf");
	sf::Text txt;
	txt.setFont(font::consola);
	main_window::initialize();

	scrollable_menu_H SMH{ 100, 300 };

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
				main_window::getInstance().setView(sf::View(sf::FloatRect(0.f, 0.f, eve.size.width, eve.size.height)));
				break;
			case sf::Event::Closed:
				main_window::getInstance().close();
				break;
			case sf::Event::MouseButtonPressed:
				if (eve.mouseButton.button == sf::Mouse::Button::Left) {
					leftButtonPressed = true;
					SMH.tryClick(eve.mouseButton.x, eve.mouseButton.y, true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (eve.mouseButton.button == sf::Mouse::Button::Left) {
					leftButtonPressed = false;
					SMH.tryRelease(eve.mouseButton.x, eve.mouseButton.y);
				}
				break;
			case sf::Event::MouseMoved:
				if (leftButtonPressed) {
					SMH.tryClick(eve.mouseMove.x, eve.mouseMove.y, false);
				}
				break;
			default:
				break;
			}
		}
		main_window::getInstance().clear();
		txt.setString(std::to_string(sys::get_millis()));
		main_window::getInstance().draw(txt);
		main_window::getInstance().draw(SMH);

		main_window::getInstance().display();
	}
}