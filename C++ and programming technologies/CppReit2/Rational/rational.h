#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <cmath>
#include <numeric>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
  int numerator_ = 0;
  int denominator_ = 1;
  void Irreducible();
 public:
  Rational(int n, int d) { // NOLINT
    if (d == 0) {
      throw RationalDivisionByZero();
    }
    denominator_ = d;
    numerator_ = n;
    Irreducible();
  }

  explicit Rational() {
    denominator_ = 1;
    numerator_ = 0;
  }

  Rational(int n) : numerator_(n), denominator_(1) {} // NOLINT

  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int n);
  void SetDenominator(int n);
  Rational& operator-=(const Rational& n);
  Rational& operator*=(const Rational& n);
  Rational operator-() const;
  Rational& operator--();
  Rational operator--(int);
  Rational& operator/=(const Rational& n);
  Rational operator+() const;
  Rational& operator+=(const Rational& n);
  Rational& operator++();
  Rational operator++(int);
  friend std::ostream& operator<<(std::ostream& os, const Rational& n);
  friend std::istream& operator>>(std::istream& is, Rational& n);
};

bool operator>=(const Rational& a, const Rational& b);
bool operator==(const Rational& a, const Rational& b);
bool operator<(const Rational& a, const Rational& b);
bool operator>(const Rational& a, const Rational& b);
bool operator!=(const Rational& a, const Rational& b);
bool operator<=(const Rational& a, const Rational& b);
Rational operator-(const Rational& a, const Rational& b);
Rational operator/(const Rational& a, const Rational& b);
Rational operator*(const Rational& a, const Rational& b);
Rational operator+(const Rational& a, const Rational& b);

#endif