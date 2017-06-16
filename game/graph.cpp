#include "graph.h"
#include <algorithm>

std::unordered_map<station*, std::list<station*>> graph::adj;

void graph::initalize() {

}

void graph::add_link(station *first, station *second) {
	adj[first].push_back(second);
	adj[second].push_back(first);
}
void graph::erase_link(station *first, station *second) {
	adj[first].erase(std::find(adj[first].begin(), adj[first].end(), second));
	adj[second].erase(std::find(adj[second].begin(), adj[second].end(), first));
}

void graph::cleanup() {
	adj.clear();
}
