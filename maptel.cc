/*
 *  JNP Zadanie 2: maptel
 *  Maciej Piekarniak - mp347204
 *  Piotr Wiśniewski  - pw361286
 *  UWAGI DLA CZYTELNIKA:
 *   - pozwoliłem sobie nie komentować nazwy funkcji maptel*, ponieważ ich
 *     dokładny opis znajduje się w pliku "maptel.h" - z resztą jak to bywa
 *     we wszelkich interfejsach i implementacjach
 *   - nie komentowałem także rzeczy oczywistych, które naturalnie wynikają
 *     z nazwy funkcji jak np "copy_number" czy "is_valid_number"
 *   - każda funkcja, która implementuje funkcje z interfejsu zawiera na
 *     początku i końcu sekcje do debugowania. Ponownie - nie komentuje tego,
 *     ponieważ to co tam jest widoczne jest oczywiste z kodu.
 */

#include <iostream>
#include <unordered_map>
#include <cassert>
#include "maptel.h"

namespace {
    #ifndef NDEBUG
        const bool debug = true;
    #else
        const bool debug = false;
    #endif

	// Typedefy - czyli przepisanie długiej ilości kodu jako pojedyńcze słowo
	// mapvalue oznacza "wartosc" w mapie ze wszystkimi telefonami.
    typedef std::unordered_map<std::string, std::string> mapvalue;
	// phone_change - wykorzystany do maptel_transform do iteracji.
    typedef std::unordered_map<std::string, std::string>::iterator phone_change;
    // phone_book_map - mapa ze wszystkimi telefonami, utworzona w anonimowym
	//                  namespace.
	typedef std::unordered_map<unsigned long, mapvalue> phone_book_map;

    phone_book_map&  phone_map()
    {
        static phone_book_map ans = phone_book_map();
        return ans;
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
	
	bool is_valid_number(std::string number){
		size_t n = number.size();

		if (n>=TEL_NUM_MAX_LEN)
			return false;

		for (size_t i=0; i!=n; ++i)
			if (!std::isdigit(number[i]))
				return false;
		
		return true;
	}
}


unsigned long maptel_create() {
    static unsigned long counter = 0;
    if (debug) {
        std::cerr << "maptel: maptel_create()\n";
        assert(phone_map().find(counter) == phone_map().end());
    }

    phone_map().insert(std::pair<unsigned long, mapvalue> (counter, mapvalue()));

    if (debug) {
        std::cerr << "maptel: maptel_create: new map id = " << counter << '\n';
        assert(phone_map().find(counter) != phone_map().end());
    }

    return counter++;
}


void maptel_delete(unsigned long id) {
    if (debug) {
        std::cerr << "maptel: maptel_delete(" << id << ")\n";
        assert(phone_map().find(id) != phone_map().end());
    }

    phone_map().erase(id);

    if (debug) {
        std::cerr << "maptel: maptel_delete: map " << id << " deleted\n";
        assert(phone_map().find(id) == phone_map().end());
    }
}


void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
    std::string tel_src_str(tel_src);
    std::string tel_dst_str(tel_dst);
    if (debug) {
        std::cerr << "maptel: maptel_insert(" << id << ", " << tel_src_str
                  << ", " << tel_dst_str << ")\n";
    }

    //mapa nie istnieje
    if (phone_map().find(id) == phone_map().end())
        std::cerr << "maptel with id: " <<id <<" does not exist\n";
    else {
        phone_map()[id].emplace(tel_src_str, tel_dst_str);
        if (debug) {
            std::cerr << "maptel: maptel_insert: inserted\n";
            assert(phone_map()[id].find(tel_src) != phone_map()[id].end());
        }
    }
}


void maptel_erase(unsigned long id, char const *tel_src) {
    std::string tel_src_str(tel_src);
    if (debug) {
        std::cerr << "maptel: maptel_erase(" << id << ", " << tel_src_str << ")\n";
    }

    if (phone_map().find(id) == phone_map().end())
        std::cerr << "maptel with id: " <<id <<" does not exist";
    else {
        if (phone_map()[id].erase(tel_src_str)) {
            if (debug)
                std::cerr << "maptel: maptel_erase: erased\n";
        } else {
            if (debug)
                std::cerr << "maptel: maptel_erase: nothing to erase\n";
        }
    }
}


// Nie jestem pewien, czy sprawdzać poprawność numeru w sekcji debug, czy poza.
void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
	std::string tel_src_s(tel_src);
    if (debug) {
        std::cerr << "maptel: maptel_transform(" << id << ", " << tel_src_s
                  << ", " << static_cast<void*>(tel_dst) << ", " << len << ")\n";
		assert(phone_map().find(id) != phone_map().end());
		assert(is_valid_number(tel_src_s));
    }

    if (phone_map().find(id) == phone_map().end())
        std::cerr << "maptel with id: " << id <<" does not exist";
    else {
        mapvalue book = phone_map()[id];
        if (book.find(tel_src_s) == book.end()) {
            copy_number(tel_dst, tel_src_s, len);
        }
        else {
            phone_change slow = book.find(tel_src_s);
            phone_change fast = slow;
            
			// Wykrywanie cyklu z uzyciem metody "krolika i zolwia"
			while(true) {
                //wolnego przeuwamy o jeden i jak natrafimy na koniec no to brak cyklu
                if (book.find(slow->second) != book.end())
                    slow = book.find(slow->second);
                else {
                    //wpisz slow->second
                    copy_number(tel_dst, slow->second, len);
                    break;
                }
                //szybkiego przesuwamy o 2 i jak po drodze byl koniec to brak cyklu
                if (book.find(fast->second) != book.end()) {
                    fast = book.find(fast->second);
                    if (book.find(fast->second) != book.end())
                        fast = book.find(fast->second);
                    else {
                        //wpisz fast->second
                        copy_number(tel_dst, fast->second, len);
                        break;
                    }
                }
                else{
                    //wpisz slow->second
                    copy_number(tel_dst, slow->second, len);
                    break;
                }

                //czyli mamy cykl
                if (slow == fast) {
                    //wpisz tel_src
                    copy_number(tel_dst, tel_src_s, len);
                    if (debug)
                        std::cerr << "maptel: maptel_transform: cycle detected\n";
                    break;
                }
            } //end while
        } //end else
        if (debug) {
            std::cerr << "maptel: maptel_transform: " << tel_src_s <<" -> "
                      << std::string(tel_dst) <<", \n";
        }
    }
}