#include <iostream>
#include <unordered_map>
#include <cassert>
#include "maptel.h"

#ifndef NDEBUG
    const bool debug = true;
#else
    const bool debug = false;
#endif

static std::unordered_map<unsigned long, std::string> phone_map;



// TODO: zamienic na obsluge usunietych indeksow
unsigned long maptel_create() {
    static unsigned long counter = 1;
	if (debug) {
		std::cerr << "maptel: maptel_create()\n";
		//assert(phone_map.find(counter) == phone_map.end());
	}

	phone_map.insert( std::pair<unsigned long, std::string>(counter, "") );
    
	if (debug) {
		std::cerr << "maptel: maptel_create will return: " << counter << '\n';
		assert(phone_map.find(counter) != phone_map.end());
	}
	
	return counter++;
}

// doned
void maptel_delete(unsigned long id) {
	if (debug) {
		std::cerr << "maptel: maptel_delete(" << id << ")\n";
		assert(phone_map.find(id) != phone_map.end());
	}
	
	phone_map.erase(id);
	
	if (debug) {
		std::cerr << "maptel: maptel_delete deleted id " << id << '\n';
		assert(phone_map.find(id) == phone_map.end());
	}
}


void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
	std::string tel_src_str(tel_src);
	std::string tel_dst_str(tel_dst);
	if (debug) {
		std::cerr << "maptel: maptel_insert(" << id << ", \"" << tel_src_str
		          << "\", \"" << tel_dst_str << "\")\n";
		assert(phone_map.find(id) != phone_map.end());
	}
	phone_map.insert(std::pair<unsigned long, std::string>(id, tel_dst));
	
	if (debug) {
		std::cerr << "maptel: maptel_insert succeeded\n";
		// TODO: dodac jakas asercje
	}
}

void maptel_erase(unsigned long id, char const *tel_src) {
	std::string tel_src_str(tel_src);
	
}

  
void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
	std::string tel_src_s(tel_src);
	std::string tel_dst_s(tel_dst);
}


int main() {
	std::cout << "hello world";
    return 0;
}
