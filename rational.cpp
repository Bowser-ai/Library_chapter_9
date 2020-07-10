# include "rational.h"
#include <stdexcept>

Rational::Rational(int numerator, int denominator)
	:numerator{numerator}, denominator{denominator} 
{
	if (denominator == 0)
	{
		throw std::runtime_error{"ration number cant have a 0 denominator"};
	}
}

Rational Rational::operator+(const Rational& rhs)
{
	int new_num{rhs.numerator * denominator + numerator * rhs.denominator};
	int new_denum{rhs.denominator * denominator};
	int gcd{GCD(new_num, new_denum)};

	return {new_num / gcd, new_denum / gcd};
}

Rational Rational::operator-(const Rational& rhs)
{
	int new_num{numerator * rhs.denominator - rhs.numerator * denominator};
	int new_denum{rhs.denominator * denominator};
	int gcd{GCD(new_num, new_denum)};
	return {new_num / gcd, new_denum / gcd};
}

Rational Rational::operator*(const Rational& rhs)
{
	return {numerator * rhs.numerator, denominator * rhs.denominator};
}

Rational Rational::operator/(const Rational& rhs)
{
	return {numerator / rhs.numerator, denominator / rhs.denominator};
}

bool Rational::operator==(const Rational& rhs)
{
	return  to_double() == rhs.to_double();
}

int Rational::GCD(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	return GCD(b, a % b);
}
