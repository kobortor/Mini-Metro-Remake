#pragma once
#include"file_map_generator.h"

class game_variables {
public:
	game_variables() = delete;
	static int get_max_passengers();
	static int get_overflow_limit();
	static float get_overflow_recovery_rate();
	static int get_train_capacity();

private:
	friend class file_map_generator;
	friend class map_generator;
	static int MAX_PASSENGERS; //how passengers can we take before we overflow
	static int OVERFLOW_LIMIT; //how many milliseconds we can last before we overflow
	static float OVERFLOW_RECOVERY_RATE; //number of seconds we must recover for each second of overflow
	static int TRAIN_CAPACITY; //how many people can fit in a single train
};