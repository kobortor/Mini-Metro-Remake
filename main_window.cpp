#include "main_window.h"
#include "game/main_game.h"
#include "fonts.h"
#include "system/system_func.h"

//static variables
sf::RenderWindow main_window::instance;
scrollable_menu_H main_window::map_menu{ 1, 2 };

//i hate static declarations...
decltype(main_window::RENDER_MODE) main_window::RENDER_MODE;

bool main_window::mouse_button_pressed[sf::Mouse::ButtonCount];
bool main_window::key_pressed[sf::Keyboard::KeyCount];

void main_window::initialize() {
	instance.create(sf::VideoMode(500, 500), "Mini Metro Remake - ICS4U Project");
	map_menu.resize();
	RENDER_MODE = MAIN_MENU;
}

sf::RenderWindow& main_window::get_instance() {
	return instance;
}

void main_window::handle_mouse_click(sf::Event::MouseButtonEvent eve) {
	mouse_button_pressed[eve.button] = true;
	if (RENDER_MODE == MAIN_MENU) {
		if (eve.button == sf::Mouse::Button::Left) {
			map_menu.try_click(eve.x, eve.y, true);
		}
	} else if (RENDER_MODE == IN_GAME) {
		main_game::handle_mouse_click(eve);
	} else if (RENDER_MODE == GAME_OVER) {
		main_game::cleanup();
		RENDER_MODE = MAIN_MENU;
	}
}
void main_window::handle_mouse_move(sf::Event::MouseMoveEvent eve) {
	if (RENDER_MODE == MAIN_MENU) {
		if (mouse_button_pressed[sf::Mouse::Button::Left]) {
			map_menu.try_click(eve.x, eve.y, false);
		}
	} else if (RENDER_MODE == IN_GAME) {
		main_game::handle_mouse_move(eve);
	}
}
void main_window::handle_mouse_release(sf::Event::MouseButtonEvent eve) {
	mouse_button_pressed[eve.button] = false;
	if (RENDER_MODE == MAIN_MENU) {
		if (eve.button == sf::Mouse::Button::Left) {
			map_menu.try_release(eve.x, eve.y);
		}
	} else if (RENDER_MODE == IN_GAME) {
		main_game::handle_mouse_release(eve);
	}
}
void main_window::handle_key_press(sf::Event::KeyEvent eve) {
	if (eve.code == sf::Keyboard::Unknown) {
		return;
	}
	if (RENDER_MODE == IN_GAME) {
		main_game::handle_key_press(eve);
	}
}
void main_window::handle_key_release(sf::Event::KeyEvent eve) {
	if (eve.code == sf::Keyboard::Unknown) {
		return;
	}
	if (RENDER_MODE == IN_GAME) {
		main_game::handle_key_release(eve);
	}
}
void main_window::handle_resize(sf::Event::SizeEvent eve) {
	instance.setView(sf::View(sf::FloatRect(0.f, 0.f, eve.width, eve.height)));
	if (RENDER_MODE == MAIN_MENU) {
		map_menu.resize();
	} else if (RENDER_MODE == IN_GAME) {
		main_game::resize();
	}
}

void main_window::render() {
	sf::Text txt;
	txt.setFont(font::consola);
	txt.setString(std::to_string(sys::get_millis()));
	if (RENDER_MODE == GAME_OVER) {
		return;
	}
	instance.clear();
	if (RENDER_MODE == MAIN_MENU) {
		txt.setString(std::to_string(sys::get_millis()));
		instance.draw(txt);
		instance.draw(map_menu);
	} else if (main_window::RENDER_MODE == main_window::IN_GAME) {
		main_game::update();
		main_game::render();
		if (main_game::is_game_over()) {
			RENDER_MODE = GAME_OVER;
			sf::Text txt;
			txt.setFont(font::consola);
			txt.setCharacterSize(instance.getSize().y / 8);
			txt.setFillColor(sf::Color::Black);
			txt.setString("GAME OVER!\n");
			float wid = txt.getLocalBounds().width;
			txt.setPosition(instance.getSize().x / 2 - wid / 2, main_game::get_window_bounds().top + instance.getSize().y / 16);
			instance.draw(txt);
		}
	}
	instance.display();
}