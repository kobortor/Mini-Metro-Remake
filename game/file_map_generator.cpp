#include"file_map_generator.h"
#include"main_game.h"
#include<iostream>

file_map_generator::file_map_generator(std::string file_name) :fin(file_name) {
	if (!fin.is_open()) {
		std::cout << "CANNOT OPEN FILE " << file_name << "\n";
		exit(0);
	}
}

void file_map_generator::update_until(long long game_tick) {
	if (!ticked) {
		std::cout << "Added\n";
		main_game::add_station(0.5, 0.5, station::TRIANGLE);
	}
	ticked = true;
}