#include"metro_line.h"

metro_line::metro_line(station *begin) {
	stations.push_back(begin);
}

station* metro_line::get_next_station(station* prev, station* cur) {
	auto cur_idx = find(stations.begin(), stations.end(), cur);
	if (cur_idx == stations.end()) {
		return nullptr;
	}
}

void metro_line::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	for (const segment &seg : segments) {
		targ.draw(seg);
	}
}