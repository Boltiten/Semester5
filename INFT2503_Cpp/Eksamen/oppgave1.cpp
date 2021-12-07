#include <iostream>
#include <string>

using namespace std;

string firstword(string s){
    string first;
    int i;
    for (i = 0; i < s.length(); i++)
    {
        if(s.at(i)==' ') break;
    }
    first = s.substr(0,i);

    return first;
}

bool starts_with(string a, string b)
{
    if(a.empty() && b.empty()) return true;
    a = firstword(a);
    if(a == b)return true;
    return false;
};


int main(){
cout << starts_with("", "") << endl;
cout << starts_with(string(""), "") << endl;

 

cout << starts_with("This is a test", "This") << endl;
cout << starts_with(string("This is a test"), "This") << endl;

 

cout << starts_with("This is a test", "Test") << endl;
cout << starts_with(string("This is a test"), "Test") << endl;

 

cout << starts_with("This", "This is a test") << endl;
cout << starts_with(string("This"), "This is a test") << endl;
    return 0;
}

/*
Gir utskriften:

1
1
1
1
0
0
0
0 */