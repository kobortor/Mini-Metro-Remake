#include"file_map_generator.h"
#include"main_game.h"
#include"../functions.h"
#include<iostream>
#include<sstream>

const std::string END_DETAIL = "###END DETAILS###";

file_map_generator::file_map_generator(std::string file_name) {
	std::ifstream fin(file_name);
	std::vector<std::string> input;
	if (!fin.is_open()) {
		std::cout << "CANNOT OPEN FILE " << file_name << "\n";
		exit(0);
	}
	std::string str;
	while (getline(fin, str)) {
		func::trim(str);
		if (!str.empty()) {
			input.push_back(str);
		}
	}
	
	auto iter = input.begin();
	while (iter != input.end()) {
		str = *iter++;
		if (str == END_DETAIL) {
			break;
		}
		int colon = str.find(':');
		if (colon == std::string::npos) {
			std::cout << "EXPECTED COLON '" << str << "'\n";
			exit(0);
		}

		std::string attrib = str.substr(0, colon);
		std::string value = str.substr(colon+1);

		func::trim(attrib);
		func::trim(value);

		if (attrib == "WIDTH") {
			rel_bounds.x = std::stof(value);
		} else if (attrib == "HEIGHT") {
			rel_bounds.y = std::stof(value);
		}
	}

	//now to load the coordinates
	while (iter != input.end()) {
		//TODO: implement coordinate details
		std::stringstream ss(*iter++);
		float x, y;
		ss >> x >> y;
		points.push({ x, y });
	}
}

sf::Vector2f file_map_generator::get_relative_bounds() {
	return rel_bounds;
}

void file_map_generator::update_until(long long game_tick) {
	while (!points.empty() && game_tick - last_update > 1000) {
		last_update += 1000;
		sf::Vector2f to_add = points.front();
		points.pop();
		main_game::add_station(to_add.x, to_add.y, station::TRIANGLE);
	}
}