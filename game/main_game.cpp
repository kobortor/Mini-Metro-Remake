#include"main_game.h"
#include"../main_window.h"
#include"../fonts.h"
#include<iostream>
#include"../system/system_func.h"

map_generator* main_game::map_gen = nullptr;
time_t main_game::game_start_time = 0;
std::vector<station> main_game::stations;

void main_game::initialize(map_generator* _map_gen) {
	game_start_time = sys::get_millis();
	map_gen = _map_gen;
}
void main_game::resize() {
	sf::Vector2f bounds = getRelativeBounds();
	//find which side is limiting
	sf::Vector2u windowBounds = main_window::getInstance().getSize();
	float calcWid = windowBounds.y * bounds.x / bounds.y;
	float calcHt = windowBounds.x * bounds.y / bounds.x;
	if (calcWid > windowBounds.x) {
		//width is limiting
		std::cout << "Width is limiting\n";
	} else {
		//height is limiting
		std::cout << "Height is limiting\n";
	}
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