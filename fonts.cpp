#include"fonts.h"

namespace font {
	using sf::Font;
	Font consola;
	void load() {
		consola.loadFromFile("assets/fonts/consola.ttf");
	}
}