#pragma once

#include<chrono>

namespace sys {
	//Gets system time in millisecodns
	time_t get_millis();

	//Gets system time in microseconds
	time_t get_micro();
}