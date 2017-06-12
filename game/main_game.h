#pragma once
#include"map_generator.h"

class main_game {
public:
	static void initialize(map_generator* _map_gen);
	static void resize();
	static void update();
	static void render(); //always render to main window
	static void cleanup();
protected:
	static map_generator* map_gen;
};