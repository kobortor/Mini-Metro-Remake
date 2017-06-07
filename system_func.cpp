#include"system_func.h"

namespace sys {
	time_t get_millis() {
		using namespace std::chrono;
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}
	time_t get_micro() {
		using namespace std::chrono;
		return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	}
}