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
typedef std::unordered_map<std::string, std::string>::iterator phone_change;
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
		//assert(phone_map[id].find(tel_src_str) != phone_map[id].end());
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

void copy_number(char *dst, std::string& number, size_t max_len)
{
    size_t l = number.length();
    if (l + 1> max_len) //potrzebujemy tez miejsca na nulla
        std::cerr << "not enough memory allocated";
    else {
        number.copy(dst, l);
        dst[l] = '\0';
    }
}
void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
	std::string tel_src_s(tel_src);
	if (debug) {
		std::cerr << "maptel: maptel_transform(" << id << ", " << tel_src_s
		          << ", " << tel_dst << ", " << len << ")\n";

	}
	if (phone_map.find(id) == phone_map.end())
	    std::cerr << "maptel woth id: " <<id <<" does not exist";
    else {
        mapvalue book = phone_map[id];
        if (book.find(tel_src_s) == book.end()) {
            copy_number(tel_dst, tel_src_s, len);
        }
        else {
            phone_change slow = book.find(tel_src_s);
            phone_change fast = slow;
            while(true) {
                //wolnego przeuwamy o jeden i jak natrafimy na koniec no to brak cyklu
                if (book.find(slow->second) != book.end())
                    slow = book.find(slow->second);
                else {
                    //wpisz slow->second
                    copy_number(tel_dst, slow->second, len);
                    return;
                }

                //szybkiego przesuwamy o 2 i jak po drodze byl koniec to brak cyklu
                if (book.find(fast->second) != book.end()) {
                    fast = book.find(fast->second);
                    if (book.find(fast->second) != book.end())
                        fast = book.find(fast->second);
                    else {
                        //wpisz fast->second
                        copy_number(tel_dst, fast->second, len);
                        return;
                    }

                }
                else{
                    //wpisz slow->second
                    copy_number(tel_dst, slow->second, len);
                    return;
                }

                //czyli mamy cykl
                if (slow == fast) {
                    //wpisz tel_src
                    copy_number(tel_dst, tel_src_s, len);
                    return;
                }
            }
        }
    }






	if (debug) {

	}
}


int main() {
	//std::cout << "hello world";
	char *tel1 = "1";
	char *tel2 = "2";
	char *tel3 = "3";
	char *tel4 = "4";
	char *tel5 = "5";
	unsigned long i = maptel_create();
	maptel_insert(i, tel1, tel2);
	maptel_insert(i, tel2, tel3);
	maptel_insert(i, tel3, tel2);
	maptel_insert(i, tel4, tel5);
	char t[4];
	maptel_transform(i,tel3, t, 4);
	printf("%s", t);
    return 0;
}
