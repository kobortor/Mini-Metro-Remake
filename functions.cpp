#include"functions.h"

namespace func {
	void trim(std::string &str) {
		if (str.empty()) {
			return;
		}
		int begin = 0;
		while (begin < str.size() && iswspace(str[begin])) {
			begin++;
		}
		str = str.substr(begin);
		while (!str.empty() && iswspace(str.back())) {
			str.pop_back();
		}
	}
}