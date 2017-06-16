#include"textures.h"

namespace textures {
	Texture train_button;
	Texture train_cursor;

	void load() {
		train_button.loadFromFile("assets/icons/train button.png");
		train_cursor.loadFromFile("assets/icons/train cursor.png");
	}
}