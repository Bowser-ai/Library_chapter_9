# ifndef RATIONAL_H_
#define RATIONAL_H_

#include <iostream>


class Rational
{
	public:
		Rational(int numerator, int denominator);
		double to_double() const {return numerator / denominator;}
		Rational operator + (const Rational& rhs);
		Rational operator - (const Rational& rhs);
		Rational operator * (const Rational& rhs);
		Rational operator / (const Rational& rhs);
		bool operator == (const Rational& rhs);
		bool operator != (const Rational& rhs) { return !(*this == rhs);}
		friend std::ostream& operator<< (std::ostream& os, const Rational& r)
		{
			if (r.numerator < 0 ^ r.denominator < 0) os << "-"; 
			return os << std::abs(r.numerator) <<"/" <<abs(r.denominator);
		}

	private:
		int numerator;
		int denominator;
		int GCD(int, int);
};

#endif

