#include "chrono.h"
#include "UnitTest++/UnitTest++.h"

SUITE(DateTests)
{
	TEST(validDate)
	{
		CHECK_THROW(Chrono::Date(1990, Chrono::Month::june, -15), Chrono::Date::Invalid);
		CHECK_THROW(Chrono::Date(1690, Chrono::Month::june, 15), Chrono::Date::Invalid);
		CHECK_THROW(Chrono::Date(1691, Chrono::Month::february, 29), Chrono::Date::Invalid);
		CHECK_THROW(Chrono::Date(2000, Chrono::Month::february, 30), Chrono::Date::Invalid);
	}
	TEST(leapYear)
	{
		CHECK(!Chrono::leapyear(1691));
		CHECK(!Chrono::leapyear(2001));
		CHECK(Chrono::leapyear(2000));
	}
	TEST(day_of_date)
	{
		Chrono::Date date{2020, Chrono::Month::july, 8};
		int day{get_day_from_date(date)};
		CHECK_EQUAL(day, 3);
	}
	TEST(next_workday)
	{
		Chrono::Date date{2020, Chrono::Month::july, 8};
		Chrono::Date tomorrow{2020, Chrono::Month::july, 9};
		Chrono::Date friday{2020, Chrono::Month::july, 10};
		Chrono::Date saturday{2020, Chrono::Month::july, 11};
		Chrono::Date sunday{2020, Chrono::Month::july, 12};
		Chrono::Date monday{2020, Chrono::Month::july, 13};
		CHECK_EQUAL(tomorrow, next_workday(date));
		CHECK_EQUAL(monday, next_workday(friday));
		CHECK_EQUAL(monday, next_workday(saturday));
		CHECK_EQUAL(monday, next_workday(sunday));
	}
	TEST(next_week_day)
	{
		Chrono::Date saturday{2020, Chrono::Month::july, 11};
		Chrono::Date sunday{2020, Chrono::Month::july, 12};
		Chrono::Date monday{2020, Chrono::Month::july, 13};
		Chrono::Date thuesday{2020, Chrono::Month::july, 13};
		CHECK_EQUAL(int(Chrono::Day::sunday), int(next_weekday(saturday)));
		CHECK_EQUAL(int(Chrono::Day::monday), int(next_weekday(sunday)));
		CHECK_EQUAL(int(Chrono::Day::thuesday), int(next_weekday(monday)));
	}

}

int main(int, const char *[])
{
   return UnitTest::RunAllTests();
}
