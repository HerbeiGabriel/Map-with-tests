#include "Map.h"
#include "MapIterator.h"
#include <math.h>
#define NIL -1
int Map::h(TKey e, int i)
{
	int a;
	if (e > 0)
		a = e;
	else a = -e;
	return (a % m + 1 * i + 1 * i * i) % m;
}

Map::Map() {
	e = new TElem[11];
	m = 11;
	for (int i = 0; i < m; i++) {
		e[i].first = -11111;
		e[i].second = -11111;
	}
	cap = 0;
}

Map::Map(int m1)
{
	e = new TElem[m1];
	for (int i = 0; i < m1; i++) {
		e[i].first = -11111;
		e[i].second = -11111;
	}
	m =m1 ;
	cap = 0;
}

Map::~Map() {
	delete[] e;
	m = 0;
	cap = 0;
}

TValue Map::add(TKey c, TValue v) {
	int i = 0;
	bool gasit = false;
	int scr = search1(c);
	if (scr != NULL_TVALUE) {
		TValue v1 = e[scr].second;
		e[scr].second = v;
		return v1;
	}
	else {
		while (gasit == false) {
			if (cap == m-1) {
				int m1 = m;
				int m2 = next_prime(m);
				m = m2;
				TElem* e2 = new TElem[m];
				for (int p = 0; p < m; p++) {
					e2[p].first = -11111;
					e2[p].second = -11111;
				}
					
				int j = 0;
				while (j<m1) {
					gasit = false;
					int i1 = 0;
					int c1 = e[j].first;
					int v1 = e[j].second;
					while (gasit == false) {
						int a = h(c1, i1);
						if (e2[a].first == -11111 && e2[a].second == -11111) {
							e2[a].first = c1;
							e2[a].second = v1;
							gasit = true;
						}
						else i1++;
					}
					j++;

				}
				delete[] e;
				e = e2;
				add(c, v);
				cap--;
				gasit = true;
			}
			else {
			int a = h(c, i);
			if (e[a].first == -11111 && e[a].second == -11111) {
				e[a].first = c;
				e[a].second = v;
				gasit = true;
			}
			else i++;
			}
			
			
		}
		cap++;
	}
	return NULL_TVALUE;
}

TValue Map::search(TKey c){
	int i = 0;
	int a;
	bool gasit = false;
	if (!isEmpty()) {
		while (gasit == false) {
			a = h(c, i);
			if (e[a].first == c) {
				return e[a].second;
			}
			else i++;
			if(i==m-1)
				return NULL_TVALUE;
		}
		if (gasit == true)
			return e[a].second;
	}
	return NULL_TVALUE;
}

int Map::search1(TKey c)
{
	int i = 0;
	int a;
	bool gasit = false;
	while (gasit == false) {
		a = h(c, i);
		if (e[a].first == c) {
			gasit = true;
		}
		else i++;
		if(i==m-1)
			return NULL_TVALUE;
	}
	if (gasit == true)
		return a;
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	if (cap == 0)
		return NULL_TVALUE;
	int scr = search1(c);
	if (scr != NULL_TVALUE) {
		int a = e[scr].second;
		e[scr].first = -11111;
		e[scr].second = -11111;
		cap--;
		return a;
	}
	return NULL_TVALUE;
}


int Map::size() const {
	return cap;
}

bool Map::isEmpty() const{
	if (cap == 0)
		return true;
	return false;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



int Map::next_prime(int a)const {
	for (int i = a * 2; i < a * 4; i++) {
		bool prime = true;
		for (int j = 2; j < i / 2; j++) {
			if (i % j == 0) {
				prime = false;
			}
		}
		if (prime == true)
			return i;
	}
	return 0;
}