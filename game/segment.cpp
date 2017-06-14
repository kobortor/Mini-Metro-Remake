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
	if (begin != end) {
		sf::Vertex ln[3] = { begin, calc_mid(), end };
		targ.draw(ln, 3, sf::LineStrip);
	}
}

segment segment::get_reverse() {
	segment retv = *this;
	std::swap(retv.begin, retv.end);
	std::swap(retv.orig, retv.dest);

	//finally, calculate the reverse direction
	sf::Vector2f mid = calc_mid();
	if (mid == end) {
		retv.dir = direction((dir + 4) % NUM_DIRECTIONS);
		//a straight line, just reverse it
	}

	float diffX = end.x - mid.x;
	float diffY = end.y - mid.y;

	//maybe this has floating point precision errors?
	if (diffX == 0) {
		if (diffY > 0) {
			retv.dir = NORTH;
		} else {
			retv.dir = SOUTH;
		}
	} else if (diffY == 0) {
		if (diffX > 0) {
			retv.dir = WEST;
		} else {
			retv.dir = EAST;
		}
	} else {
		if (diffX > 0) {
			if (diffY > 0) {
				retv.dir = NORTH_WEST;
			} else {
				retv.dir = SOUTH_WEST;
			}
		} else {
			if (diffY > 0) {
				retv.dir = NORTH_EAST;
			} else {
				retv.dir = SOUTH_EAST;
			}
		}
	}

	return retv;
}

sf::Vector2f segment::calc_mid() const {
	using std::min;

	sf::Vector2f mid = begin;
	float diffX = abs(end.x - begin.x);
	float diffY = abs(end.y - begin.y);

	switch (dir) {
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
	return mid;
}