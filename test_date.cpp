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
}

int main(int, const char *[])
{
   return UnitTest::RunAllTests();
}
