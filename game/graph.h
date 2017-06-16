#pragma once
#include<unordered_map>
#include<list>
#include"station.h"

//bidirectional graph
//static class meant to work with main_game
class graph {
public:
	graph() = delete;
	static void initalize();
	static void add_station(station *stn);
	static void add_link(station *first, station *second);
	static void erase_link(station *first, station *second);

	//returns the shortest distance from source to dest
	//returns -1 if cannot reach
	static int shortest_dist(std::list<station*> source, std::list<station*> dest);
	static void cleanup();
protected:
	static std::unordered_map<station*, std::list<station*>> adj;
};