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

	float hypotf(sf::Vector2f V) {
		return ::hypotf(V.x, V.y);
	}

	void draw_thick_line(sf::Vector2f begin, sf::Vector2f end, float wid, sf::Color col, sf::RenderTarget &targ) {
		float radius = wid / 2;

		sf::CircleShape circ{ radius };
		circ.setFillColor(col);

		circ.setPosition(begin.x - radius, begin.y - radius);
		targ.draw(circ);
		
		circ.setPosition(end.x - radius, end.y - radius);
		targ.draw(circ);

		sf::Vector2f diff = end - begin;
		if (diff.x == 0 && diff.y == 0) {
			return;
		}

		diff = normalize(diff);
		diff *= radius;
		std::swap(diff.x, diff.y);
		diff.y *= -1;

		sf::Vertex vert[] = { begin + diff, end + diff, end - diff, begin - diff };
		for (int a = 0; a < 4; a++) {
			vert[a].color = col;
		}

		targ.draw(vert, 4, sf::TriangleFan);
	}

	float dist_to_line(sf::Vector2f begin, sf::Vector2f end, sf::Vector2f point) {
		float ans = hypotf(point - begin);
		ans = std::min(ans, hypotf(point - end));
		
		bool within_range = dot(point - begin, end - begin) >= 0 && dot(point - end, begin - end) >= 0;
		if (within_range) {
			ans = std::min(ans, abs(cross(point - begin, end - begin) / hypotf(begin)));
		}
		return ans;
	}
}