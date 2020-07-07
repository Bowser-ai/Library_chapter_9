#include "chrono.h"

namespace Chrono
{
	Date::Date() {}

	Date::Date(int year, Month month, int day): year{year}, month{month}, day{day}
	{
		if (!is_date(year, month, day)) throw Invalid{"Invalid date"};
	}

	void Date::add_day(int n)
	{

		day = (day + n) % max_days_in_month(month, year);
		month = Month(static_cast<int>(month) + (day + n) / max_days_in_month(month, year));
		year += static_cast<int>(month) / 12;
	}

	void Date::add_month(int n)
	{
		month = Month((static_cast<int>(month) + n) % 12);
		year += (static_cast<int>(month) + n) / 12;
	}

	void Date::add_year(int n)
	{
		if (leapyear(year) && month == Month::february && day == 29)
		{
			day = 1;
			month = Month::march;
		}
		year += n;
	}

	std::string Date::month_to_string(const Month& m)
	{
		for (const auto& k_v_pair : month_mapping)
		{
			if (k_v_pair.second == m) return k_v_pair.first;
		}
		throw std::runtime_error{"Invalid cast to string from month"};
	}

	Month Date::string_to_month(const std::string& s)
	{
        try{
		    return month_mapping.at(s);
        }
        catch (std::out_of_range& e)
        {
            throw std::runtime_error{"Invalid month supplied"};
        }
	}

	int max_days_in_month(Month month, int year)
	{
		int max_days_in_month{0};
		switch(month)
		{
			case Month::april: case Month::june: case Month::september: case Month::november:
				max_days_in_month = 30;
				break;
			case Month::february:
				max_days_in_month = (leapyear(year) ? 29: 28);
				break;
			default:
				max_days_in_month = 31;
		}
		return max_days_in_month;
	}

	bool is_date(int year, Month month, int day)
	{
		return 1800 <= year && year <= 3000
			&& 1 <= static_cast<int>(month) && static_cast<int>(month) <= 12
			&& 1 <= day && day <= max_days_in_month(month, year);
	}

	bool leapyear(int year)
	{
		return  (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}

	bool operator==(const Date& d, const Date& other)
	{
		return d.get_day() == other.get_day()
			&& d.get_month() == other.get_month()
			&& d.get_year() == other.get_year();
	}

	bool operator!=(const Date& d, const Date& other)
	{
		return !(d==other);
	}

	std::ostream& operator<<(std::ostream& os, const Month& month)
	{
		return os << Date::month_to_string(month);
	}

	std::ostream& operator <<(std::ostream& os, const Date& d)
	{
		return os << "(" << d.get_year() << ", "
				  << d.get_month() <<", " << d.get_day() << ")";
	}

	std::istream& operator >>(std::istream& is, Date& d)
	{
		auto error = std::runtime_error{"Date format should be '(y m d)'"};
		char ch{};
		is.get(ch);
		if (ch != '(') throw error;
		int y{0};
		is >> y;
		std::string month;
		is >> month;
		Month m = Date::string_to_month(month);
		int day{0};
		is >> day;
		is.get(ch);
		if (ch != ')') throw error;
		d = Date{y, m, day};
		return is;
	}

	const std::unordered_map<std::string, Month> Date::month_mapping {
		{"January", Month::january}, {"February", Month::february},
		{"March", Month::march}, {"April", Month::april},
		{"May", Month::may}, {"June", Month::june}, 
		{"July", Month::july}, {"August", Month::august},
		{"September", Month::september}, {"October", Month::october},
		{"November", Month::november}, {"December", Month::december}
	};
}
