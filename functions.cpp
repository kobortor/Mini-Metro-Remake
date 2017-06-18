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

	void draw_ring(sf::Vector2f center, float inner_radius, float outer_radius, int num_points, sf::Color col, sf::RenderTarget & targ) {
		std::vector<sf::Vertex> verts;
		verts.reserve(2 * num_points + 2);

		verts.push_back(sf::Vector2f(0, inner_radius));
		verts.push_back(sf::Vector2f(0, outer_radius));

		float delta_angle = 3.141592f * 2 / num_points;

		for (int a = 1; a < num_points; a++) {
			sf::Vector2f vec(sin(delta_angle * a), cos(delta_angle * a));
			verts.push_back(vec * inner_radius);
			verts.push_back(vec * outer_radius);
		}

		verts.push_back(sf::Vector2f(0, inner_radius));
		verts.push_back(sf::Vector2f(0, outer_radius));

		for (sf::Vertex &v : verts) {
			v.color = col;
			v.position += center;
		}

		targ.draw(verts.data(), verts.size(), sf::TrianglesStrip);
	}

	void draw_semi_circle(sf::Vector2f center, float radius, float begin_ang, float end_ang, int num_points, sf::Color col, sf::RenderTarget & targ) {
		if (num_points <= 1) {
			return;
		}

		if (end_ang - begin_ang >= 2 * 3.141592) {
			end_ang = begin_ang + 2 * 3.141592;
		}

		std::vector<sf::Vertex> verts;
		verts.reserve(1 + num_points);

		float delta_ang = (end_ang - begin_ang) / (num_points - 1);
		verts.push_back(center);
		for (int a = 0; a < num_points; a++, begin_ang += delta_ang) {
			verts.push_back(center + sf::Vector2f(radius * sin(begin_ang), radius * -cos(begin_ang)));
		}
		for (sf::Vertex &v : verts) {
			v.color = col;
		}
		targ.draw(verts.data(), 1 + num_points, sf::TriangleFan);
	}

	float dist_to_line(sf::Vector2f begin, sf::Vector2f end, sf::Vector2f point) {
		float ans = hypotf(point - begin);
		ans = std::min(ans, hypotf(point - end));
		
		bool within_range = dot(point - begin, end - begin) >= 0 && dot(point - end, begin - end) >= 0;
		if (within_range) {
			ans = std::min(ans, abs(cross(point - begin, end - begin) / hypotf(end - begin)));
		}
		return ans;
	}
	sf::Color opposite_color(sf::Color col) {
		return sf::Color(255 - col.r, 255 - col.g, 255 - col.b, col.a);
	}
}