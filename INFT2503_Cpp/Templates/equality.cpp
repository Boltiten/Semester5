#include <iostream>
#include <math.h>


bool equal(double a, double b)
{
    if(abs(a-b)<0.00001)return true;
    return false;
}

template<typename Type> 
bool equal(Type a, Type b)
{
    

    if(a == b) return true;
    return false;
}

int main()
{
    int a = 1;
    int b = 2;
    int c = 1;

    double d = 1.0;
    double e = 2.001;
    double f = 2.0;

    std::cout<<equal(f,e)<<std::endl;
    return 0;
}
