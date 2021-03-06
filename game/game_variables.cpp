#include "game_variables.h"

int game_variables::MAX_PASSENGERS;
int game_variables::OVERFLOW_LIMIT;
float game_variables::OVERFLOW_RECOVERY_RATE;
int game_variables::TRAIN_CAPACITY;
int game_variables::MAX_TRAIN_COUNT;

int game_variables::get_max_passengers() {
	return MAX_PASSENGERS;
}

int game_variables::get_overflow_limit() {
	return OVERFLOW_LIMIT;
}

float game_variables::get_overflow_recovery_rate() {
	return OVERFLOW_RECOVERY_RATE;
}

int game_variables::get_train_capacity() {
	return TRAIN_CAPACITY;
}

int game_variables::get_max_train_count() {
	return MAX_TRAIN_COUNT;
}
