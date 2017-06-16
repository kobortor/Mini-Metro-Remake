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
	static void add_link(station *first, station *second);
	static void erase_link(station *first, station *second);
	static void cleanup();
protected:
	static std::unordered_map<station*, std::list<station*>> adj;
};