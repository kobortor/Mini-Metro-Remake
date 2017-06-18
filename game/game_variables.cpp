#include "game_variables.h"

int game_variables::MAX_PASSENGERS;
int game_variables::OVERFLOW_LIMIT;
float game_variables::OVERFLOW_RECOVERY_RATE;

int game_variables::get_max_passengers() {
	return MAX_PASSENGERS;
}

int game_variables::get_overflow_limit() {
	return OVERFLOW_LIMIT;
}

float game_variables::get_overflow_recovery_rate() {
	return OVERFLOW_RECOVERY_RATE;
}