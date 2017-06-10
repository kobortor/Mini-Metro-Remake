#include<SFML\Graphics.hpp>
#include"system\system_func.h"
#include"interpol\interpol.h"
#include"menu\scrollable_menu.h"

int main() {
	sf::Font consola;
	consola.loadFromFile("assets/fonts/consola.ttf");
	sf::Text txt;
	txt.setFont(consola);

	sf::RenderWindow wind(sf::VideoMode(500, 500), "WTF");

	scrollable_menu_H SMH{ 100, 300 };

	interpol<interpol_func::quadratic> pol{ sys::get_millis(), sys::get_millis() + 500 };
	bool leftButtonPressed = false;

	while (wind.isOpen()) {
		sf::Event eve;
		while (wind.pollEvent(eve)) {
			if (eve.type == sf::Event::Closed) {
				wind.close();
			}
			switch (eve.type) {
			case sf::Event::Resized:
				wind.setView(sf::View(sf::FloatRect(0.f, 0.f, eve.size.width, eve.size.height)));
				break;
			case sf::Event::Closed:
				wind.close();
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
		wind.clear();
		txt.setString(std::to_string(sys::get_millis()));
		wind.draw(txt);
		wind.draw(SMH);

		wind.display();
	}
}