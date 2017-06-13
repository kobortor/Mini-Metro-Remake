#include"file_map_generator.h"
#include"main_game.h"
#include"../functions.h"
#include<iostream>

const std::string END_DETAIL = "###END DETAILS###";

file_map_generator::file_map_generator(std::string file_name) :fin(file_name) {
	if (!fin.is_open()) {
		std::cout << "CANNOT OPEN FILE " << file_name << "\n";
		exit(0);
	}
	std::string input;
	while (std::getline(fin, input)) {
		if (input == END_DETAIL) {
			break;
		}
		int colon = input.find(':');
		if (colon == std::string::npos) {
			std::cout << "EXPECTED COLON '" << input << "'\n";
			exit(0);
		}

		std::string attrib = input.substr(0, colon);
		std::string value = input.substr(colon+1);

		func::trim(attrib);
		func::trim(value);

		if (attrib == "WIDTH") {
			rel_bounds.x = std::stof(value);
		} else if (attrib == "HEIGHT") {
			rel_bounds.y = std::stof(value);
		}
	}
}

sf::Vector2f file_map_generator::getRelativeBounds() {
	return rel_bounds;
}

void file_map_generator::update_until(long long game_tick) {
	if (!ticked) {
		std::cout << "Added\n";
		main_game::add_station(0.5, 0.5, station::TRIANGLE);
	}
	ticked = true;
}