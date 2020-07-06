#ifndef CHONO_H_
#define CHONO_H_

#include <iostream>
#include <unordered_map>

namespace Chrono
{
	enum class Month
	{
		january = 1, february, march, april, may, june, july, august, september,
		october, november, december
	};

	class Date
	{
		public:
			class Invalid: public std::runtime_error {public: using std::runtime_error::runtime_error;}; 
			Date(); 
			Date(int year, Month month, int day);

			int get_day() const {return day;}
			Month get_month() const {return month;}
			int get_year() const {return year;}

			void add_year(int n);
			void add_month(int n);
			void add_day(int n);

			static std::string month_to_string(const Month&);
			static Month string_to_month(const std::string&);

		private:
			int year;
			Month month;
			int day;
			static const std::unordered_map<std::string, Month> month_mapping;
	};

	int max_days_in_month(Month m, int year);
	bool is_date(int y, Month m, int d);
	bool leapyear(int y);
	bool operator ==(const Date& d1, const Date& d2);
	bool operator !=(const Date& d1, const Date& d2);
	std::ostream& operator <<(std::ostream& os, const Date& d);
	std::istream& operator >>(std::istream& is, Date& d);
	Date day_of_week(const Date& d);
	Date next_sunday(const Date& d);
	Date next_weekday(const Date& d);
	std::ostream& operator<<(std::ostream&, const Month&);
	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date&);
}

#endif
