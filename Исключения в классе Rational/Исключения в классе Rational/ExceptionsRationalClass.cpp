#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <exception>
#include <sstream>
#include <stdexcept>

using namespace std;

int GCD(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return GCD(b, a % b);
	}
}

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}
	Rational(int new_numerator, int new_denominator) {
		if (new_denominator == 0) {
			throw invalid_argument("Invalid argument");
		}
		const int gcd = GCD(new_numerator, new_denominator);
		numerator = new_numerator / gcd;
		denominator = new_denominator / gcd;
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}

	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}
private:
	int numerator;
	int denominator;
};
Rational operator + (const Rational& lhs, const Rational& rhs) {
	return{
		lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator()
	};
}
Rational operator - (const Rational& lhs, const Rational& rhs) {
	return{
		lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator()
	};
}
Rational operator * (const Rational& lhs, const Rational& rhs) {
	return{
		lhs.Numerator() * rhs.Numerator(),
		lhs.Denominator() * rhs.Denominator()
	};
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() == 0) {
		throw domain_error("Domain error");
	};
	if (rhs.Numerator() == 0) {
		throw domain_error("Domain error");
	};
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}
istream& operator >> (istream& is, Rational& r) {
	int n, d;
	char c;
	is >> n >> c >> d;
	if (is && c == '/') {
		r = Rational(n, d);
	}
	return is;
}

ostream& operator << (ostream& os, const Rational& r) {
	return os << r.Numerator() << '/' << r.Denominator();
}

bool operator < (const Rational& lhs, const Rational& rhs) {
	return (lhs - rhs).Numerator() < 0;
}
int main() {
	try {
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error&) {
	}

	cout << "OK" << endl;
	return 0;
}