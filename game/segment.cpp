#include"segment.h"

const sf::Vector2f segment::unit_direction[] = {
	sf::Vector2f(0.f, -1.f),					//N
	sf::Vector2f(1 / sqrtf(2), -1 / sqrtf(2)),	//NE
	sf::Vector2f(1.f, 0.f),						//E
	sf::Vector2f(1 / sqrtf(2), 1 / sqrtf(2)),	//SE
	sf::Vector2f(0.f, 1.f),						//S
	sf::Vector2f(-1 / sqrtf(2), 1 / sqrtf(2)),	//SW
	sf::Vector2f(-1.f, 0.f),					//W
	sf::Vector2f(-1 / sqrtf(2), -1 / sqrtf(2))	//NW
};

const std::string segment::direction_names[] = {
	"north",
	"north-east",
	"east",
	"south-east",
	"south",
	"south-west",
	"west",
	"north-west"
};

void segment::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	if (begin != end) {
		sf::Vector2f mid = begin;
		float diffX = abs(end.x - begin.x);
		float diffY = abs(end.y - begin.y);

		switch (segment::dir) {
		case NORTH:
			mid.y -= diffY - diffX;
			break;
		case NORTH_EAST:
			mid.x -= std::min(diffX, diffY);
			mid.y += std::min(diffX, diffY);
			break;
		case EAST:
			mid.x += diffX - diffY;
			break;
		case SOUTH_EAST:
			break;
		case SOUTH:
			break;
		case SOUTH_WEST:
			break;
		case WEST:
			break;
		case NORTH_WEST:
			break;
		default:
			break;
		}
		sf::Vertex ln[3] = { begin, mid, end };

		targ.draw(ln, 3, sf::LineStrip);
	}
}