#include"metro_line.h"

metro_line::metro_line(station *begin) {
	stations.push_back(begin);
}

void metro_line::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	for (const segment &seg : segments) {
		targ.draw(seg);
	}
}