#include"main_game.h"
#include"../main_window.h"
#include"../fonts.h"
#include<iostream>
#include"../system/system_func.h"

map_generator* main_game::map_gen = nullptr;
time_t main_game::game_start_time = 0;
std::vector<station> main_game::stations;
sf::RectangleShape main_game::background;
sf::IntRect main_game::window_bounds;

void main_game::initialize(map_generator* _map_gen) {
	game_start_time = sys::get_millis();
	background.setFillColor(sf::Color(50,50,50));
	map_gen = _map_gen;
	resize();
}
void main_game::resize() {
	sf::Vector2f bounds = getRelativeBounds();
	//find which side is limiting
	sf::Vector2u window = main_window::getInstance().getSize();
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

sf::IntRect main_game::getWindowBounds() {
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
sf::Vector2f main_game::getRelativeBounds() {
	return map_gen->getRelativeBounds();
}
void main_game::render() {
	main_window::getInstance().draw(background);
	sf::Text txt;
	txt.setFont(font::consola);
	txt.setCharacterSize(20);
	txt.setString("YOU ARE PLAYING THE GAME NOW!!!");
	txt.setPosition(30, 30);
	main_window::getInstance().draw(txt);

	for (const station &stn : stations) {
		main_window::getInstance().draw(stn);
	}
}

void main_game::cleanup() {
	delete map_gen;
}