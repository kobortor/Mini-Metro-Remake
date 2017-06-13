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
	sf::Vertex ln[3] = { begin, mid, end };
	targ.draw(ln, 3, sf::LineStrip);
}