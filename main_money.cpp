# include "money.h"

int main()
{
	Money m{10067L};
	Money m2{5.55f, Currency::usd};
	std::cout << "I have " << m << "\n";
	std::cout << "and " << m2 << "\n";
	std::cout << "enter some money \n";
	Money m3;
	std::cin >> m3;
	std::cout << "You have entered " << m3 << "\n";

	return 0;
}
