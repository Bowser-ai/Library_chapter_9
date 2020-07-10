#include "rational.h"

int main()
{
	Rational r1 {3, 9};
	Rational r2{3, 8};
	Rational r3 = r1 + r2;
	Rational r4 {3, 9};
	Rational r5 {9, 27};
	std::cout << "r3 is: " << r3 << "\n";
	std::cout << "r1 - r2 == " << r1 - r2 << "\n";
	std::cout << "1/2 * -1/2 == " <<Rational{1, 2} * Rational{-1, 2} << "\n";
	std::cout << (r4 == r5) << "\n";
	
	return 0;
}
