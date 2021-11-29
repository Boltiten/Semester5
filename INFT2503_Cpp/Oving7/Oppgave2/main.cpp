#include <iostream>
#include <vector>
#include <ostream>

class Set{
public:
    //TODO
    //konstruktor
    Set();
    //union, {1,4,7} og {4, 3} blir {1,4,7,3}
    Set operator+(const Set &other) const;
    //add() til en mengde, hvis tallet finnes fra før, så gjør ingenting, kanskje si ifra at det finnes fra før
    Set &operator+=( int other);
    //kopiere en mengde til en ny mengde
    Set &operator=(Set &other);
    //print mengde
    size_t size() const{return mengde.size();}
    int operator[](size_t index) const;
private:
    std::vector<int> mengde;
    bool valueExist(int value);
};
Set::Set(){}

bool Set::valueExist(int value)
{
    for (auto &&i : mengde)
    {
        if(i==value)return true;
    }   
    return false;
}

Set Set::operator+(const Set &other) const
{
    //union av 2 vectorer
    Set set = *this;
    for (size_t i = 0; i < other.mengde.size(); i++)
    {
        set += other.mengde[i];
    }
    return set;
}

Set &Set::operator+=(int other) 
{
    if(!valueExist(other))mengde.push_back(other);    
    return *this;
}

int Set::operator[](size_t index) const
{
    return mengde[index];
}

std::ostream &operator<<(std::ostream &out, const Set &set) {
  for (size_t i = 0; i < set.size(); i++)
    out << set[i] << " ";
  return out;
}


int main()
{
    Set a;
    a += 2;
    a += 3;
    a += 2;

    Set b;
    b += 5;
    b += 4;
    b += 3;
    
    Set c = a + b;

    std::cout<<c<<std::endl;
    return 0;
}