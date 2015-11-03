#include <iostream>
#include <queue>
#include <unordered_map>
#include "maptel.h"

typedef const char* dictionary; // ogolnie jakis typ na wartosc do mapy

static std::unordered_map<unsigned long, dictionary> dictionaries;

unsigned long maptel_create() {
    static unsigned long counter = 1;
	// make_pair krzyczalo o bledach, no idea why
	dictionaries.insert( std::pair<unsigned long, dictionary>(counter, "") );
    return counter++;
}

void maptel_delete(unsigned long id) {
	if (dictionaries.find(id) != dictionaries.end())
		dictionaries.erase(id);
}

void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
	dictionaries.insert(std::pair<unsigned long, dictionary>(id, tel_dst));
}

void maptel_erase(unsigned long id, char const *tel_src) {
	if (dictionaries.find(id) != dictionaries.end()) {
		dictionaries.insert(std::pair<unsigned long, dictionary>(id, tel_src));
	}
}

  
void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len);

int main() {
	std::cout << maptel_create();
    return 0;
}
