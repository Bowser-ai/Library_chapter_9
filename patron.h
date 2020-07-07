#ifndef PATRON_H_
#define PATRON_H_

#include <string>
#include <unordered_map>
#include "chrono.h"


class Patron {

	public:
		Patron(std::string username, int card_number)
			: username{username}, card_number{card_number} {}

		std::string get_username() const {return username;}
		int get_card_number() const {return card_number;}
		double get_fee(const Chrono::Date& d) const;

		void set_fee(const Chrono::Date& d, double fee);
		bool owes_fee() const {return fees.size() != 0;}
        bool operator ==(const Patron& other){return card_number == other.card_number;}
        bool operator != (const Patron& other) {return !(*this == other);}

	private:
		std::string username;
		int card_number;
		std::unordered_map<std::string, double> fees;
};

#endif


