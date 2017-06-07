#include<SFML\Graphics.hpp>
#include"system_func.h"
#include"interpol\interpol.h"

int main() {
	sf::Font consola;
	consola.loadFromFile("assets/fonts/consola.ttf");
	sf::Text txt;
	txt.setFont(consola);

	sf::RenderWindow wind(sf::VideoMode(500, 500), "WTF");

	sf::CircleShape circ {150, 30};
	circ.setPosition(150, 150);
	circ.setFillColor(sf::Color::White);

	interpol<interpol_func::quadratic> pol{ sys::get_millis(), sys::get_millis() + 500 };

	while (wind.isOpen()) {
		sf::Event eve;
		while (wind.pollEvent(eve)) {
			if (eve.type == sf::Event::Closed) {
				wind.close();
			}
		}
		wind.clear();
		txt.setString(std::to_string(sys::get_millis()));
		wind.draw(txt);

		double scale = pol.get(sys::get_millis());
		circ.setScale(scale, scale);
		circ.setPosition(150 - scale * 150, 150 - scale * 150);
		wind.draw(circ);

		wind.display();
	}
}