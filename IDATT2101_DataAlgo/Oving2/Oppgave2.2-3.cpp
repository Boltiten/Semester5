#include <iostream>
#include <math.h>
#include <chrono>
#include <cstdlib>
#include <time.h>

double recursion(double x, int n);

int main(){

    //Kjøretid må tas
    double base = 1.123456789;
    int potens = 1024;
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double testRecursion = recursion(base,potens);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout<<testRecursion<<std::endl;
    return 0;
}

double recursion(double x, int n){
    if(n == 0){
        return 1;
    }else if(n%2 == 1){
        return (x * recursion(x*x, (n-1)/2));
    }else if(n%2 == 0){
        return (recursion(x*x, n/2));
    }
    return 0;
}