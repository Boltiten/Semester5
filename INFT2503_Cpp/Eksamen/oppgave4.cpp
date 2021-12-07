#include <iostream>

using namespace std;
class Meter{
public:
    static double convert;

};
double Meter::convert = 1;

class Kilometer{
public:
    static double convert;
};
double Kilometer::convert = 1000;

template <class metric>
class Distance{
public:
    int dist;
    metric type;
    Distance(int dist_) : dist(dist_*metric::convert){};
    friend ostream &operator<<(std::ostream &out, const Distance &distance)
    {
        out<<distance.dist<<"m";
        return out;
    };

    Distance<Kilometer> operator+(const Distance<Meter> &other) const{
        Distance<Kilometer> sum = *this;
        sum.dist += other.dist;
        return sum;
    }
    
    Distance &operator+=(const int &other){
        this->dist = this->dist+other*metric::convert;
        return *this;
    }
};


int main(){
    Distance<Meter> meters(2);
meters += 3;


Distance<Kilometer> kilometers(2);
kilometers += 3;


cout << "5 meters: " << meters << endl;
cout << "5 kilometers: " << kilometers << endl;
cout << "5 kilometers + 5 meters: " << kilometers + meters << endl;
    
    return 0;
}

/*
5 meters: 5m
5 kilometers: 5000m
5 kilometers + 5 meters: 5005m
*/