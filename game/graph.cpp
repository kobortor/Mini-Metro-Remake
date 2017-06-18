#include "graph.h"
#include <algorithm>
#include <queue>
#include <functional>

std::unordered_map<station*, std::list<station*>> graph::adj;

void graph::initalize() {

}

void graph::add_station(station *stn) {
	adj[stn];
}

void graph::add_link(station *first, station *second) {
	adj[first].push_back(second);
	adj[second].push_back(first);
}
void graph::erase_link(station *first, station *second) {
	adj[first].erase(std::find(adj[first].begin(), adj[first].end(), second));
	adj[second].erase(std::find(adj[second].begin(), adj[second].end(), first));
}

int graph::shortest_dist(std::list<station*> source, std::list<station*> dest) {
	std::unordered_map<station*, int> distances;

	//may use floats later for distance
	std::priority_queue<std::pair<int, station*>, std::vector<std::pair<int, station*>>, std::greater<std::pair<int, station*>>> pq;
	for (station *stn : source) {
		pq.push({ 0, stn });
		distances[stn] = 0;
	}

	while (!pq.empty()) {
		auto fr = pq.top();
		pq.pop();
		auto links = adj.find(fr.second);

		auto prv_dist = distances.find(fr.second);

		if (prv_dist != distances.end() && fr.first > prv_dist->second) {
			continue;
		}

		if (links != adj.end()) {
			for (station *stn : links->second) {
				auto dest = distances.find(stn);
				if (dest == distances.end() || distances[stn] > fr.first + 1) {
					distances[stn] = fr.first + 1;
					pq.push({ fr.first + 1, stn });
				}
			}
		}
	}

	int ans = -1;
	for (station *stn : dest) {
		auto iter = distances.find(stn);
		if (iter != distances.end()) {
			if (ans == -1 || iter->second < ans) {
				ans = iter->second;
			}
		}
	}
	return ans;
}

void graph::cleanup() {
	adj.clear();
}
