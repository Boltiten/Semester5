//
// fraction/main.cpp
//
#include "fraction.hpp"
#include "fraction.cpp"
#include <iostream>
#include <string>

using namespace std;

void print(const string &text, const Fraction &broek) {
  cout << text << broek.numerator << " / " << broek.denominator << endl;
}

int main() {
  Fraction a(3, 4);

  Fraction answerA = 5 - a;
  Fraction answerB = a - 5;

  Fraction answerC = 5 - 3 - answerA - 7 - a;

  print("answer A = ", answerA);
  print("answer A = ", answerB);

  print("answer C", answerC);

}
