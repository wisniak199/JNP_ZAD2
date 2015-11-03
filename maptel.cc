/*
  Kompilacja: g++ -o maptel maptel.cc -std=c++11 -Wall -pedantic
  Notki dla ciebie:
  Trzeba jeszcze wpasc na pomysl jak reprezentowac zmiany. imo dobra opcja
  bylby vector z push_backiem i ogolnie map<int, vector<string>>. Czy jakos
  inaczej?

  PW: Nie trzeba robic zadnych vectorow. Wydaje mi sie, ze w zadaniu chodzi o to,
  ze w przypadku mapy ktora ma np:
  numer1 -> numer2; numer2 -> numer3; numer3 -> numer4
  to wtedy mamy wpisac to tel_dst numer4 (jezeli pytamy o numer1)(tak samo
  dla cykli)


  Wykrywanie cyklu da rade zrobic liniowo (z pamiecia stala)
  Trzeba bedzie jeszcze ogarnac "te rzeczy" w zwiazku z C. Sam kod raczej
  nie jest trudny

  uwagi:
  dodac jakies typedefy? przykladowo na unordered_map
*/

#include <iostream>
#include <unordered_map>
#include <cassert>
#include "maptel.h"

#ifndef NDEBUG
    const bool debug = true;
#else
    const bool debug = false;
#endif

typedef std::unordered_map<std::string, std::string> mapvalue;

static std::unordered_map<unsigned long, mapvalue> phone_map;



// TODO: zamienic na obsluge usunietych indeksow
unsigned long maptel_create() {
    static unsigned long counter = 1;
	if (debug) {
		std::cerr << "maptel: maptel_create()\n";
		assert(phone_map.find(counter) == phone_map.end());
	}


	phone_map.insert(std::pair<unsigned long, mapvalue> (counter, mapvalue()));

	if (debug) {
		std::cerr << "maptel: maptel_create: new map id = " << counter << '\n';
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
		std::cerr << "maptel: maptel_delete: map " << id << " deleted\n";
		assert(phone_map.find(id) == phone_map.end());
	}
}


void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
	std::string tel_src_str(tel_src);
	std::string tel_dst_str(tel_dst);
	if (debug) {
		std::cerr << "maptel: maptel_insert(" << id << ", " << tel_src_str
		          << ", " << tel_dst_str << ")\n";
		assert(phone_map.find(id) != phone_map.end());
		assert(phone_map[id].find(tel_src_str) != phone_map[id].end());
	}

	//wydaje mi sie ze nawet w wersji release powinnismy poinformowac uzytkownika jak
	//uzywa niesyniejacej mapy
	if (phone_map.find(id) == phone_map.end())
	    std::cerr << "maptel with id: " <<id <<" does not exist";
    //w elsie mozna by dodac jakies asserty, ale to chyba byloby testowanie stla
    else
        phone_map[id].emplace(tel_src_str, tel_dst_str);

	if (debug) {
		std::cerr << "maptel: maptel_insert: inserted\n";
		// TODO: dodac jakas asercje
	}
}

void maptel_erase(unsigned long id, char const *tel_src) {
	std::string tel_src_str(tel_src);
	if (debug) {
		std::cerr << "maptel: maptel_erase(" << id << ", " << tel_src_str << ")\n";
	}

    if (phone_map.find(id) == phone_map.end())
	    std::cerr << "maptel with id: " <<id <<" does not exist";
    else
        phone_map[id].erase(tel_src_str);


	if (debug) {
		std::cerr << "maptel: maptel_erase: erased\n";
	}
}


void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
	std::string tel_src_s(tel_src);
	std::string tel_dst_s(tel_dst);
	if (debug) {
		std::cerr << "maptel: maptel_transform(" << id << ", " << tel_src_s
		          << ", " << tel_dst << ", " << len << ")\n";

	}






	if (debug) {

	}
}


int main() {
	std::cout << "hello world";
    return 0;
}
