#include"main_game.h"
#include"../main_window.h"
#include"../fonts.h"
#include<iostream>
#include"../system/system_func.h"
#include"../functions.h"
#include"handle.h"
#include"../textures.h"

map_generator* main_game::map_gen = nullptr;
time_t main_game::game_start_time = 0;
std::list<metro_line> main_game::lines;
std::list<station> main_game::stations;
std::list<train> main_game::trains;
sf::RectangleShape main_game::background;
sf::IntRect main_game::window_bounds;
metro_line* main_game::edit_line;
segment main_game::edit_seg;
time_t main_game::last_update;
std::list<sf::Color> main_game::avail_colors;
train_button* main_game::train_btn;

main_game::CLICK_MODE_TYPE main_game::CLICK_MODE;

int main_game::prvX = -1;
int main_game::prvY = -1;

bool main_game::mouse_button_pressed[sf::Mouse::ButtonCount];
bool main_game::key_pressed[sf::Keyboard::KeyCount];

void main_game::initialize(map_generator* _map_gen) {
	avail_colors = {
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Cyan,
		sf::Color::Magenta,
		sf::Color::Yellow
	};

	game_start_time = sys::get_millis();
	last_update = 0;
	background.setFillColor(sf::Color(50, 50, 50));
	map_gen = _map_gen;
	
	auto rel_bound = get_relative_bounds();

	train_btn = new train_button((rel_bound.x - 0.25 * rel_bound.y), 0.05 * rel_bound.y, 
		0.2 * rel_bound.y, 0.1 * rel_bound.y);

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

	for (metro_line &ml : lines) {
		ml.resize();
	}

	for (train &t : trains) {
		t.resize();
	}

	train_btn->resize();
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
	time_t delta = get_game_time() - last_update;
	if (delta == 0) {
		return;
	}
	last_update += delta;
	for (train &t : trains) {
		t.update(delta);
	}
	auto iter = trains.begin();
	while (iter != trains.end()) {
		if (iter->is_dead()) {
			auto tmp = iter;
			iter++;
			trains.erase(tmp);
		} else {
			iter++;
		}
	}
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

	if (CLICK_MODE == LINE_EDIT_FRONT || CLICK_MODE == LINE_EDIT_BACK) {
		main_window::get_instance().draw(edit_seg);
	}

	for (const metro_line &ml : lines) {
		main_window::get_instance().draw(ml);
	}

	for (const station &stn : stations) {
		main_window::get_instance().draw(stn);
	}

	for (const train &t : trains) {
		main_window::get_instance().draw(t);
	}

	main_window::get_instance().draw(*train_btn);

	if (CLICK_MODE == PLACE_TRAIN) {
		sf::RectangleShape rect;
		float ybnd = window_bounds.height;
		float radius = 0.025;
		rect.setPosition(prvX - radius * ybnd, prvY - radius * ybnd);
		//intentionally both height to make square
		rect.setSize(sf::Vector2f(2 * radius * window_bounds.height, 2 * radius * window_bounds.height));
		rect.setTexture(&textures::train_cursor);
		main_window::get_instance().draw(rect);
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
void main_game::set_edit_line(metro_line *line, main_game::CLICK_MODE_TYPE mode) {
	CLICK_MODE = mode;
	edit_line = line;
	edit_seg = segment();

	//act as if it was beginning even if mode is editing from the front.
	//if it is from the front, just reverse it when actually adding the stations
	if (mode == LINE_EDIT_FRONT) {
		edit_seg.begin = edit_line->stations.front()->get_pos();
		edit_seg.end = edit_line->stations.front()->get_pos();
		edit_seg.orig = edit_line->stations.front();
	} else if (mode == LINE_EDIT_BACK) {
		edit_seg.begin = edit_line->stations.back()->get_pos();
		edit_seg.end = edit_line->stations.back()->get_pos();
		edit_seg.orig = edit_line->stations.back();
	}
}

void main_game::handle_mouse_click(sf::Event::MouseButtonEvent eve) {
	if (prvX == -1 && prvY == -1) {
		prvX = eve.x;
		prvY = eve.y;
	}

	if (CLICK_MODE == NONE) {
		if (!avail_colors.empty()) {
			for (station &stn : stations) {
				if (stn.contained(eve.x, eve.y)) {
					CLICK_MODE = LINE_EDIT_BACK;
					lines.push_back(metro_line(&stn, avail_colors.back()));
					avail_colors.pop_back();
					set_edit_line(&lines.back(), LINE_EDIT_BACK);
					break;
				}
			}
		}
	}

	if (CLICK_MODE == NONE) {
		for (metro_line &ml : lines) {
			if (ml.front_handle.contained(eve.x, eve.y)) {
				set_edit_line(&ml, LINE_EDIT_FRONT);
				edit_seg.end = sf::Vector2f(eve.x, eve.y);
				edit_seg.adjust_dir();
				break;
			}
			if (ml.back_handle.contained(eve.x, eve.y)) {
				set_edit_line(&ml, LINE_EDIT_BACK);
				edit_seg.end = sf::Vector2f(eve.x, eve.y);
				edit_seg.adjust_dir();
				break;
			}
		}
	}

	if (CLICK_MODE == NONE || CLICK_MODE == PLACE_TRAIN) {
		train_btn->try_click(eve.x, eve.y, true);
	}

	mouse_button_pressed[eve.button] = true;

	prvX = eve.x;
	prvY = eve.y;
}
void main_game::handle_mouse_move(sf::Event::MouseMoveEvent eve) {
	if (prvX == -1 && prvY == -1) {
		prvX = eve.x;
		prvY = eve.y;
	}

	if (mouse_button_pressed[sf::Mouse::Left]) {
		if (CLICK_MODE == LINE_EDIT_FRONT || CLICK_MODE == LINE_EDIT_BACK) {
			edit_seg.end.x = eve.x;
			edit_seg.end.y = eve.y;

			edit_seg.adjust_dir();

			station *hover = nullptr;
			for (station &stn : stations) {
				if (stn.contained(eve.x, eve.y) && !stn.contained(prvX, prvY)) {
					hover = &stn;
					break;
				}
			}
			//write logic for adding and removing stations
			if (hover != nullptr) {
				//not added before
				if (std::find(edit_line->stations.begin(), edit_line->stations.end(), hover) == edit_line->stations.end()) {
					edit_seg.end = hover->get_pos();
					edit_seg.dest = hover;
					edit_seg.parent = edit_line;

					if (CLICK_MODE == LINE_EDIT_BACK) {
						edit_line->stations.push_back(hover);
						edit_line->segments.push_back(edit_seg);
					} else {
						edit_line->stations.push_front(hover);
						edit_line->segments.push_front(edit_seg.get_reverse());
					}

					edit_seg = segment();
					edit_seg.orig = hover;
					edit_seg.begin = hover->get_pos();
					edit_seg.end = sf::Vector2f(eve.x, eve.y);

					edit_seg.adjust_dir();
				} else if (edit_line->stations.size() >= 2) {
					if (CLICK_MODE == LINE_EDIT_BACK) {
						if (hover == edit_line->stations.back()) {
							edit_line->stations.back()->rearrange_handles();
							edit_line->segments.pop_back();
							edit_line->stations.pop_back();

							edit_seg = segment();
							edit_seg.orig = edit_line->stations.back();
							edit_seg.begin = edit_line->stations.back()->get_pos();
							edit_seg.end = sf::Vector2f(eve.x, eve.y);
							edit_seg.adjust_dir();
						}
					} else if (CLICK_MODE == LINE_EDIT_FRONT) {
						if (hover == edit_line->stations.front()) {
							edit_line->stations.front()->rearrange_handles();
							edit_line->segments.pop_front();
							edit_line->stations.pop_front();

							edit_seg = segment();
							edit_seg.orig = edit_line->stations.front();
							edit_seg.begin = edit_line->stations.front()->get_pos();
							edit_seg.end = sf::Vector2f(eve.x, eve.y);

							edit_seg.adjust_dir();
						}
					}
				}
			}
		} else if (CLICK_MODE == NONE || CLICK_MODE == PLACE_TRAIN) {
			train_btn->try_click(eve.x, eve.y, false);
		}
	}

	prvX = eve.x;
	prvY = eve.y;
}
void main_game::handle_mouse_release(sf::Event::MouseButtonEvent eve) {
	if (prvX == -1 && prvY == -1) {
		prvX = eve.x;
		prvY = eve.y;
	}

	if (CLICK_MODE == LINE_EDIT_FRONT || CLICK_MODE == LINE_EDIT_BACK) {
		if (edit_line->stations.size() == 1) {
			auto iter = func::find_iter(lines.begin(), lines.end(), edit_line);

			if (iter != lines.end()) {
				avail_colors.push_back(iter->color);
				lines.erase(iter);
			}
		} else {
			edit_line->front_handle = handle(&*edit_line, edit_line->stations.front(), 0);
			edit_line->back_handle = handle(&*edit_line, edit_line->stations.back(), 3.14159);

			for (station* stn : edit_line->stations) {
				stn->rearrange_handles();
			}
		}
		CLICK_MODE = NONE;
	} else if(CLICK_MODE == NONE || CLICK_MODE == PLACE_TRAIN) {
		train_btn->try_release(eve.x, eve.y);
	}

	mouse_button_pressed[eve.button] = false;

	prvX = eve.x;
	prvY = eve.y;
}
void main_game::handle_key_press(sf::Event::KeyEvent eve) {
	key_pressed[eve.code] = true;
}
void main_game::handle_key_release(sf::Event::KeyEvent eve) {
	key_pressed[eve.code] = false;
}

