#include <iostream>
#include <vector>

using namespace std;

ostream &operator<<(ostream &os, const vector<int> &input){
    os<<'{';
    for (size_t i = 0; i < input.size(); i++)
    {
        os<<input[i];
        if(i+1 != input.size()){
            os<<",";
        }
    }
    os<<'}';
    return os;    
}

int main()
{
    vector<int> vec = {1, 2, 3};
    vector<int> vecMultipliedBy2 = vec | Map([](int e) { return e * 2; });
    cout << vecMultipliedBy2 << endl;
    vector<int> vecFiltered = vec | Filter([](int e) { return e % 2 == 1;
    });
    cout << vecFiltered << endl;

    return 0;
}
