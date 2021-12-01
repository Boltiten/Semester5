#include <iostream>

using namespace std;
template<typename type1, typename type2>
class Pair{
public:
    type1 first;
    type2 second;

    Pair(type1 first_, type2 second_) : first(first_), second(second_){};

    Pair operator+(const Pair &other) const{
        type1 sum1 = first + other.first;
        type2 sum2 = second + other.second;
        Pair<type1, type2> sum(sum1, sum2);
        return sum;
    }

    bool operator>(const Pair &other) const{
        type1 sum1 = first + (type1)second;
        type1 sum2 = other.first + (type1)other.second;
        return sum1>sum2;
    }


};




int main() {
  Pair<double, int> p1(3.5, 14);
  Pair<double, int> p2(2.1, 7);
  cout << "p1: " << p1.first << ", " << p1.second << endl;
  cout << "p2: " << p2.first << ", " << p2.second << endl;

  if (p1 > p2)
    cout << "p1 er størst" << endl;
  else
    cout << "p2 er størst" << endl;

  auto sum = p1 + p2;
  cout << "Sum: " << sum.first << ", " << sum.second << endl;
}

/* Utskrift:
p1: 3.5, 14
p2: 2.1, 7
p1 er størst
Sum: 5.6, 21
*/