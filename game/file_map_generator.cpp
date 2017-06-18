#include"file_map_generator.h"
#include"game_variables.h"
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

	//setting default values
	rel_bounds = { 1, 1 };
	rel_unit = 0.2;
	game_variables::MAX_PASSENGERS = 6;
	game_variables::OVERFLOW_LIMIT = 15000;
	game_variables::OVERFLOW_RECOVERY_RATE = 0.5;
	game_variables::TRAIN_CAPACITY = 6;

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
		std::string value = str.substr(colon + 1);

		func::trim(attrib);
		func::trim(value);

		if (attrib == "WIDTH") {
			rel_bounds.x = stof(value);
		} else if (attrib == "HEIGHT") {
			rel_bounds.y = stof(value);
		} else if (attrib == "RELATIVE UNIT") {
			rel_unit = stof(value);
		} else if (attrib == "MAX PASSENGERS") {
			game_variables::MAX_PASSENGERS = stof(value);
		} else if (attrib == "OVERFLOW LIMIT") {
			game_variables::OVERFLOW_LIMIT = stof(value);
		} else if (attrib == "OVERFLOW RECOVERY RATE") {
			game_variables::OVERFLOW_RECOVERY_RATE = stof(value);
		} else if (attrib == "TRAIN CAPACITY") {
			game_variables::TRAIN_CAPACITY = stof(value);
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

float file_map_generator::get_relative_unit() {
	return rel_unit;
}

void file_map_generator::update_until(long long game_tick) {
	while (!points.empty() && game_tick - last_update > 1000) {
		last_update += 1000;
		sf::Vector2f to_add = points.front();
		points.pop();

		//cheap way to cycle through
		station::STATION_TYPE type[] = { station::TRIANGLE, station::SQUARE, station::CIRCLE };

		main_game::add_station(to_add.x, to_add.y, type[last_update % 3]);
	}
	if (main_game::stations.empty()) {
		last_passenger = game_tick;
	} else {
		while (game_tick - last_passenger > 450) {

			//cheap way to cycle through
			station::STATION_TYPE type[] = { station::TRIANGLE, station::SQUARE, station::CIRCLE };

			auto iter = main_game::stations.begin();
			std::advance(iter, rand() % main_game::stations.size());
			if (iter->get_type() != type[last_passenger / 3 % 3]) {
				iter->add_passenger(new passenger(type[last_passenger / 3 % 3]));
			}
			last_passenger += 450;
		}
	}
}