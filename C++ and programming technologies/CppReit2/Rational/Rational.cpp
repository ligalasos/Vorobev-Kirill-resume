#include"rational.h"
#include<iostream>
#include <cmath>
#include <numeric>

// Конструктор по умолчанию, который инициализирует число нулем;
// Неявный конструктор преобразования от целых чисел (должен работать следующий код Rational x = 5;). Не забудьте добавить комментарий // NOLINT (см. замечания);
// Конструктор от двух целых чисел (числитель и знаменатель). При этом не гарантируется, что числа взаимно простые и ненулевые (об этом далее);
// Методы GetNumerator() и GetDenominator(), возвращающие числитель и знаменатель соответственно;
// Методы SetNumerator(int) и SetDenominator(int), устанавливающие числитель и знаменатель в требуемые значения;
// Бинарные арифметические операции (+, -, /, *) и их присваивающие версии (+=, -=, /=, *=);
// Унарные операции (+, -), а также префиксные и постфиксные инкременты и декременты (++, --);
// Операции сравнения;
// Операции ввода из потока и вывода в поток (>>, <<);

void Rational::Irreducible() {
  if (this->denominator_ == 0) {
    throw RationalDivisionByZero();
  }
  if (this->denominator_ < 0) {
    this->denominator_ = -this->denominator_;
    this->numerator_ = -this->numerator_;
  }
  int d = std::gcd(std::abs(this->numerator_), std::abs(this->denominator_));
  this->denominator_ = this->denominator_ / d;
  this->numerator_ = this->numerator_ / d;
}

bool operator<(const Rational& a, const Rational& b) {
  return b.GetDenominator() * a.GetNumerator() < b.GetNumerator() * a.GetDenominator();
}

bool operator>=(const Rational& a, const Rational& b) {
  return !(a < b);
}

bool operator==(const Rational& a, const Rational& b) {
  return !(a < b) && !(b < a);
}

bool operator!=(const Rational& a, const Rational& b) {
  return !(a == b);
}

bool operator<=(const Rational& a, const Rational& b) {
  return !(b < a);
}

bool operator>(const Rational& a, const Rational& b) {
  return b < a;
}

Rational Rational::operator+() const{
  return *this;
}

Rational Rational::operator-() const{
  Rational x;
  x.numerator_ = -this->numerator_;
  x.denominator_ = this->denominator_;
  return x;
}

int Rational::GetNumerator() const {
  return this->numerator_;
}

int Rational::GetDenominator() const {
  return this->denominator_;
}

void Rational::SetDenominator(int n) {
  this->denominator_ = n;
  this->Irreducible();
}

void Rational::SetNumerator(int n) {
  this->numerator_ = n;
  this->Irreducible();
}

Rational& Rational::operator+=(const Rational& n) {
  this->numerator_ = (this->numerator_ * n.denominator_) + (this->denominator_ * n.numerator_);
  this->denominator_ = (this->denominator_ * n.denominator_);
  this->Irreducible();
  return *this;
}

Rational& Rational::operator-=(const Rational& n) {
  this->numerator_ = (this->numerator_ * n.denominator_) - (this->denominator_ * n.numerator_);
  this->denominator_ = (this->denominator_ * n.denominator_);
  this->Irreducible();
  return *this;
}

Rational& Rational::operator*=(const Rational& n) {
  this->numerator_ = this->numerator_ * n.numerator_;
  this->denominator_ = this->denominator_ * n.denominator_;
  this->Irreducible();
  return *this;
}

Rational& Rational::operator++() {
  this->SetNumerator(this->GetNumerator() + this->GetDenominator());
  return *this;
}

Rational& Rational::operator--() {
  this->SetNumerator(this->GetNumerator() - this->GetDenominator());
  return *this;
}

Rational Rational::operator--(int) {
  Rational inc = *this;
  --*this;
  return inc;
}

Rational Rational::operator++(int) {
  Rational dec = *this;
  ++*this;
  return dec;
}

Rational& Rational::operator/=(const Rational& n) {
  Rational t{n.GetDenominator(), n.GetNumerator()};
  *this *= t;
  return *this;
}

Rational operator+(const Rational& a, const Rational& b) {
  Rational plus = a;
  plus += b;
  return plus;
}

Rational operator-(const Rational& a, const Rational& b) {
  Rational minus = a;
  minus -= b;
  return minus;
}

Rational operator*(const Rational& a, const Rational& b) {
  Rational umn = a;
  umn *= b;
  return umn;
}

Rational operator/(const Rational& a, const Rational& b) {
  Rational del = a;
  del /= b;
  return del;
}

std::istream& operator>>(std::istream& is, Rational& n) {
  int numerator = 0;
  int denominator = 1;
  is >> numerator;
  if (is) {
    char slash = 0;
    is >> slash;
    if (slash == '/') {
      is >> denominator;
    } else {
      is.unget();
    }
  }
  n = Rational(numerator, denominator);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& n) {
  if (n.GetDenominator() == 1) {
    os << n.GetNumerator();
    return os;
  }
  os << n.GetNumerator() << "/" << n.GetDenominator();
  return os;
}
