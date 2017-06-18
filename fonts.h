#pragma once

#include<SFML\Graphics\Font.hpp>

namespace font {
	using sf::Font;
	extern Font consola;

	//Loads the fonts for the game
	void load();
}