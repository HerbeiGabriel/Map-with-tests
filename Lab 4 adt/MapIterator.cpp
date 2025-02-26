#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	index = 0;
	visited = 0;
	while (index < map.m && map.e[index].first == -11111) {
		index++;
	}
}


void MapIterator::first() {
	index = 0;
	while (index < map.m && map.e[index].first == -11111) {
		index++;
	}
}


void MapIterator::next() {
	if (!valid()) {
		throw std::exception("Iterator is not valid");
	}
	index++;
	while (index < map.m && map.e[index].first == -11111) {
		index++;
	}
}


TElem MapIterator::getCurrent(){
	if (!valid()) {
		throw std::exception("Iterator is not valid");
	}
	return map.e[index];
}


bool MapIterator::valid() const {
	return index < map.m;
}



