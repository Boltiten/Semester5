#include <iostream>
#include "Oppgave1.cpp"

using namespace std;

int main() {
  Circle circle(5);

  int area = circle.get_area();
  cout << "Arealet er lik " << endl;

  double circumference = circle.get_circumference();
  cout << "Omkretsen er lik " << circumference << endl;