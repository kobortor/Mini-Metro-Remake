#include"metro_line.h"

metro_line::metro_line(station *begin) {
	stations.push_back(begin);
}

segment metro_line::get_next_path(station* cur, station* prv) {
	if (stations.size() == 1) {
		return segment(); //null
	}

	auto cur_idx = find(stations.begin(), stations.end(), cur);
	auto prv_idx = find(stations.begin(), stations.end(), prv);
	if (cur_idx == stations.end()) {
		return segment();
	}
	int d1 = distance(stations.begin(), cur_idx);
	int d2 = distance(stations.begin(), prv_idx);

	auto seg_iter = segments.begin();

	if (next(cur_idx) == stations.end()) {
		//d1 must not be 0 since size > 1
		std::advance(seg_iter, d1 - 1);
		return seg_iter->get_reverse();
	}

	if (prv_idx == stations.end()) {
		std::advance(seg_iter, d1);
		return *seg_iter;
	}

	if (d1 > d2) {
		std::advance(seg_iter, d1);
		return *seg_iter;
	} else {
		if (d1 == 0) {
			return *seg_iter;
		} else {
			std::advance(seg_iter, d1 - 1);
			return seg_iter->get_reverse();
		}
	}
}

metro_line::HANDLE_CLICK metro_line::click_handle(int posX, int posY) {
	return NONE;
}

void metro_line::draw(sf::RenderTarget &targ, sf::RenderStates) const {
	for (const segment &seg : segments) {
		targ.draw(seg);
	}
}