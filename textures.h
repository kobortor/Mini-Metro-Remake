#pragma once
#include<SFML\Graphics.hpp>

namespace textures {
	using sf::Texture;
	extern Texture train_button;
	extern Texture train_cursor;
	extern Texture delete_train_button;

	//Loads the textures for the game
	void load();
}