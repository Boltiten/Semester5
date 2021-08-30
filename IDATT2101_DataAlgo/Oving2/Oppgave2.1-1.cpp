#include <iostream>
#include <math.h>

double recursion(double x, int n);

int main(){
    double test = recursion(2,4);
    std::cout<<test<<std::endl;
    return 0;
}

double recursion(double x, int n){
    if(n=0){
        return 1;
    } else {
        return recursion(x*x, n-1);
    }
}