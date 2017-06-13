#include"segment.h"

void segment::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	sf::Vertex ln[2] = { begin, end };
	targ.draw(ln, 2, sf::Lines);
}