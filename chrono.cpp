#include "chrono.h"
#include <sstream>

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

	int get_day_from_date(const Date& date)
	{
		std::stringstream ss;
		ss << date.get_year();
		std::string str_year;
		ss >> str_year;
		const std::string sliced_year{str_year.substr(2, 2)};
		const int year_last_digts{std::stoi(sliced_year)};
		const int year_code{(year_last_digts + (year_last_digts / 4)) % 7};
		std::unordered_map<std::string, int> month_mapping {
			{"January", 0}, {"February", 3},
			{"March", 3}, {"April", 6},
			{"May", 1}, {"June", 4}, 
			{"July", 6}, {"August", 2},
			{"September", 5}, {"October", 0},
			{"November", 3}, {"December", 5}
		};
		const int month_code{month_mapping[Date::month_to_string(date.get_month())]}; 
		std::unordered_map<int, int> century_codes {
			{17, 4}, {18, 2}, {19, 0}, {20, 6}, {21, 4}, {22, 2}, {23, 0}
		};
		const int century_code{century_codes[date.get_year() / 100]};
		const bool leap_year_code{leapyear(date.get_year()) 
			&& (date.get_month() == Month::january || date.get_month() == Month::february)};
		const int day_of_the_week{(year_code + month_code + century_code + date.get_day() - static_cast<int>(leap_year_code)) % 7};
		return day_of_the_week;
	}

	Date next_workday(const Date& date)
	{
		constexpr int friday{5};
		constexpr int saturday{6};
		constexpr int days_friday_to_monday{3};
		constexpr int days_saturday_to_monday{2};
		const int current_day{get_day_from_date(date)};
		Chrono::Date new_date{date};
		switch (current_day)
		{
			case friday: 
				new_date.add_day(days_friday_to_monday);
				break;
			case saturday: 
				new_date.add_day(days_saturday_to_monday);
				break;
			default:
				new_date.add_day(1);
				break;
		}
		return new_date;
	}

	Day day_of_the_week(const Date& date)
	{
		const int day_code{get_day_from_date(date)};
		return static_cast<Day>(day_code);
	}

	Day next_weekday(const Date& date)
	{
		const int day_code{get_day_from_date(date)};
		const int next_day_code{(day_code + 1) % 7};
		return static_cast<Day>(next_day_code);
	}
	Date next_sunday(const Date& date)
	{
		const int day_code{get_day_from_date(date)};
		const int advance_day_til_sunday{7 - day_code};
		Chrono::Date next_sunday{date};
		next_sunday.add_day(advance_day_til_sunday);
		return next_sunday;
	}
		
}
