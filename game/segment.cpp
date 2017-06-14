#include"segment.h"
#include"../functions.h"

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

void segment::adjust_dir() {
	if (begin != end) {
		sf::Vector2f diff = end - begin;
		auto& idx = dir;
		//calculate the values

		while (func::dot(diff, segment::unit_direction[(idx + 2) % segment::NUM_DIRECTIONS]) >
			func::dot(diff, segment::unit_direction[idx])) {
			idx = segment::direction((idx + 1) % segment::NUM_DIRECTIONS); //enums make it difficult to increment
		}

		while (func::dot(diff, segment::unit_direction[(idx + segment::NUM_DIRECTIONS - 2) % segment::NUM_DIRECTIONS]) >
			func::dot(diff, segment::unit_direction[idx])) {
			idx = segment::direction((idx + segment::NUM_DIRECTIONS - 1) % segment::NUM_DIRECTIONS); //enums make it difficult to increment
		}
	}
}

void segment::draw(sf::RenderTarget& targ, sf::RenderStates) const {
	using std::min;
	if (begin != end) {
		sf::Vector2f mid = begin;
		float diffX = abs(end.x - begin.x);
		float diffY = abs(end.y - begin.y);

		switch (segment::dir) {
		case NORTH:
			mid.y -= diffY - diffX;
			break;
		case NORTH_EAST:
			mid.x += min(diffX, diffY);
			mid.y -= min(diffX, diffY);
			break;
		case EAST:
			mid.x += diffX - diffY;
			break;
		case SOUTH_EAST:
			mid.x += min(diffX, diffY);
			mid.y += min(diffX, diffY);
			break;
		case SOUTH:
			mid.y += diffY - diffX;
			break;
		case SOUTH_WEST:
			mid.x -= min(diffX, diffY);
			mid.y += min(diffX, diffY);
			break;
		case WEST:
			mid.x -= diffX - diffY;
			break;
		case NORTH_WEST:
			mid.x -= min(diffX, diffY);
			mid.y -= min(diffX, diffY);
			break;
		default:
			break;
		}
		sf::Vertex ln[3] = { begin, mid, end };

		targ.draw(ln, 3, sf::LineStrip);
	}
}