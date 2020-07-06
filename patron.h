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
		double get_fee(const Chrono::Date& d) const {return fees[d];}

		void set_fee(const Chrono::Date& d, double fee) {fees[d] = fee;}
		bool owes_fee() const {return fees.size() != 0;}

	private:
		std::string username;
		int card_number;
		std::unordered_map<Chrono::Date, double> fees;
};

#endif


