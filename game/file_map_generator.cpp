#include"file_map_generator.h"
#include<iostream>

file_map_generator::file_map_generator(std::string file_name) :fin(file_name) {
	if (!fin.is_open()) {
		std::cout << "CANNOT OPEN FILE " << file_name << "\n";
		exit(0);
	}
}

void file_map_generator::update_until(long long game_tick) {

}