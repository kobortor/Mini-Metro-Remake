#include"main_game.h"
#include"../main_window.h"
#include"../fonts.h"
#include<iostream>
#include"../system/system_func.h"
#include"../functions.h"

map_generator* main_game::map_gen = nullptr;
time_t main_game::game_start_time = 0;
std::list<station> main_game::stations;
sf::RectangleShape main_game::background;
sf::IntRect main_game::window_bounds;
segment main_game::selected_segment;
station* main_game::selected_station;
const sf::Vector2f main_game::unit_direction[] = {
	sf::Vector2f(0.f, -1.f),					//N
	sf::Vector2f(1 / sqrtf(2), -1 / sqrtf(2)),	//NE
	sf::Vector2f(1.f, 0.f),						//E
	sf::Vector2f(1 / sqrtf(2), 1 / sqrtf(2)),	//SE
	sf::Vector2f(0.f, 1.f),						//S
	sf::Vector2f(-1 / sqrtf(2), 1 / sqrtf(2)),	//SW
	sf::Vector2f(-1.f, 0.f),					//W
	sf::Vector2f(-1 / sqrtf(2), -1 / sqrtf(2))	//NW
};

const std::string main_game::direction_names[] = {
	"north",
	"north-east",
	"east",
	"south-east",
	"south",
	"south-west",
	"west",
	"north-west"
};

decltype(main_game::CLICK_MODE) main_game::CLICK_MODE;

bool main_game::mouse_button_pressed[sf::Mouse::ButtonCount];
bool main_game::key_pressed[sf::Keyboard::KeyCount];

void main_game::initialize(map_generator* _map_gen) {
	game_start_time = sys::get_millis();
	background.setFillColor(sf::Color(50,50,50));
	map_gen = _map_gen;
	resize();
}
void main_game::resize() {
	sf::Vector2f bounds = get_relative_bounds();
	//find which side is limiting
	sf::Vector2u window = main_window::get_instance().getSize();
	float calcWid = window.y * bounds.x / bounds.y;
	float calcHt = window.x * bounds.y / bounds.x;
	if (calcWid > window.x) {
		window_bounds.width = calcHt * bounds.x / bounds.y;
		window_bounds.height = calcHt;

		window_bounds.top = window.y / 2 - window_bounds.height / 2;
		window_bounds.left = 0;
	} else {
		window_bounds.width = calcWid;
		window_bounds.height = calcWid * bounds.y / bounds.x;

		window_bounds.top = 0;
		window_bounds.left = window.x / 2 - window_bounds.width / 2;
	}
	background.setPosition(window_bounds.left, window_bounds.top);
	background.setSize(sf::Vector2f(window_bounds.width, window_bounds.height));

	for (station &stn : stations) {
		stn.resize();
	}
}

sf::IntRect main_game::get_window_bounds() {
	return window_bounds;
}
void main_game::add_station(float _relX, float _relY, station::STATION_TYPE _type) {
	stations.emplace_back(_relX, _relY, _type);
}
time_t main_game::get_game_time() {
	//edit later to pause
	return sys::get_millis() - game_start_time;
}
void main_game::update() {
	map_gen->update_until(get_game_time());
}
sf::Vector2f main_game::get_relative_bounds() {
	return map_gen->get_relative_bounds();
}
void main_game::render() {
	main_window::get_instance().draw(background);
	sf::Text txt;
	txt.setFont(font::consola);
	txt.setCharacterSize(20);
	txt.setString("YOU ARE PLAYING THE GAME NOW!!!");
	txt.setPosition(30, 30);
	main_window::get_instance().draw(txt);

	if (CLICK_MODE == LINE_EDIT_STATION) {
		main_window::get_instance().draw(selected_segment);
	}

	for (const station &stn : stations) {
		main_window::get_instance().draw(stn);
	}
}
void main_game::cleanup() {
	delete map_gen;
}
float main_game::get_station_radius() {
	return 20;
}
float main_game::get_station_mouse_limit() {
	return 30;
}

void main_game::handle_mouse_click(sf::Event::MouseButtonEvent eve) {
	for (station &stn : stations) {
		if (stn.contained(eve.x, eve.y)) {
			CLICK_MODE = LINE_EDIT_STATION;
			selected_station = &stn;
			selected_segment.begin = sf::Vector2f(stn.get_pos());
			selected_segment.mid = sf::Vector2f(stn.get_pos());
			selected_segment.end = sf::Vector2f(stn.get_pos());
		}
	}

	mouse_button_pressed[eve.button] = true;
}
void main_game::handle_mouse_move(sf::Event::MouseMoveEvent eve) {
	if (CLICK_MODE == LINE_EDIT_STATION) {
		selected_segment.end = sf::Vector2f(eve.x, eve.y);

		if (selected_segment.begin != selected_segment.end) {
			int best_idx = 0;
			float best = func::dot(selected_segment.end - selected_segment.begin, unit_direction[0]);
			for (int a = 1; a < NUM_DIRECTIONS; a++) {
				float nv = func::dot(selected_segment.end - selected_segment.begin, unit_direction[a]);
				if (nv > best) {
					best = nv;
					best_idx = a;
				}
			}
		}
	}
}
void main_game::handle_mouse_release(sf::Event::MouseButtonEvent eve) {
	CLICK_MODE = NONE;
	mouse_button_pressed[eve.button] = true;
}
void main_game::handle_key_press(sf::Event::KeyEvent eve) {}
void main_game::handle_key_release(sf::Event::KeyEvent eve) {}