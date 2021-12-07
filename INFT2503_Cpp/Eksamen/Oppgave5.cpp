#include <iostream>
#include <vector>
#include <functional>

using namespace std;

ostream &operator<<(std::ostream &out, const vector<int> &vec)
    {
        for (auto &i : vec)
        {
          out<<i;
        }
        return out;
    };

class Find {


public:
    const std::function<int(int)> func;
    Find(const function<bool(int)>& func) : func(func) {}

};

const int* operator|(const vector<int>& vec, const Find& f) {
    for (const int &a : vec)
    {
        if (f.func(a))
        {
            return &a;
        }
    }
    return nullptr;
}
/*
class Reduce{
public:
    std::function<int(int)> func;
    Reduce(const std::function<int(int)> &func) : func(func) {}
};
*/
int main(){
vector<int> vec = {1, 2, 3};

cout << *(vec | Find([](int value) { return value > 1; })) << endl;
cout << (vec | Find([](int value) { return value == 5; })) << endl;


//cout << (vec | Reduce([](int previous_value, int current_value) {return previous_value + current_value;},0 /* initial value */))<< endl;
//cout << (vec | Reduce([](int previous_value, int current_value) {return previous_value + 2 * current_value;},5 /* initial value */))

    return 0;
}

/*
2
0x0
6
17

*/