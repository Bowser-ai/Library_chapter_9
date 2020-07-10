#ifndef MONEY_H_
#define MONEY_H_

#include <iostream>
#include <unordered_map>

enum class Currency
{
	usd='$', eur='E', yen='Y'
};

class Money
{
	public:

		Money() {}
		Money(long int value, Currency currency = Currency::eur): value{value}, currency{currency} {}
		Money(float value, Currency currency = Currency::eur): value{static_cast<long int>(value * 100)}, currency{currency} {}
		friend std::ostream& operator << (std::ostream& os, const Money& money)
		{
			std::string money_str {std::to_string(money.value)};
			os << static_cast<char>(money.currency) << money_str.substr(0, money_str.size() - 2)
			   << "," << money_str.substr(money_str.size() -2, 2);
			return os;
		}
		friend std::istream& operator >> (std::istream& is, Money& money)
		{
			char ch{0};
			is.get(ch);
			if (std::string("$EY").find(ch) == std::string::npos) throw std::runtime_error{"invalud valuta\n"};
			float amount{0.0};
			Currency cur{static_cast<Currency>(ch)};
			is >> amount;
			money = Money{amount, cur};
			return is;
		}

	private:
		long int value{0};
		Currency currency{Currency::eur};
		static const std::unordered_map<char, double> conversion_table;
};

const std::unordered_map<char, double> Money::conversion_table{
	{'E', 1.0000}, {'$', 0.88}, {'Y', 0.0094}
};

#endif
