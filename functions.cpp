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
	float cross(sf::Vector2f A, sf::Vector2f B) {
		return A.x * B.y - A.y * B.x;
	}
	float dot(sf::Vector2f A, sf::Vector2f B) {
		return A.x * B.x + A.y * B.y;
	}
	sf::Vector2f normalize(sf::Vector2f V) {
		float len = hypot(V.x, V.y);
		return{ V.x / len, V.y / len };
	}
}