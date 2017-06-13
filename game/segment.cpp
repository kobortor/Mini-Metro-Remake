#include"segment.h"

void segment::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	sf::Vertex ln[3] = { begin, mid, end };
	targ.draw(ln, 3, sf::LineStrip);
}