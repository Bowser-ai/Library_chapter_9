# include "book.h"

int main()
{
	Book book{"Clark", "Space Oddysee", "34-53-45-x", Chrono::Date{1964, Chrono::Month::april, 22}, Genre::fiction};
	Book book2{"Orwell", "1984", "123-454-342-5", Chrono::Date{1940, Chrono::Month::august, 12}, Genre::fiction};
	std:: cout << book << book2;
	return 0;
}
