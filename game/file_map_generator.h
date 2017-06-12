#pragma once
#include"map_generator.h"
#include<fstream>
#include<string>

class file_map_generator : public map_generator {
public:
	file_map_generator(std::string file_name);
	void update_until(long long game_tick);
protected:
	bool ticked = false;
	std::ifstream fin;
};