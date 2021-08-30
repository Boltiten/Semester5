#include <iostream>
#include <math.h>
#include <chrono>
#include <cstdlib>
#include <time.h>

double recursion(double x, int n);

int main(){

    //Kjøretid må tas
    double base = 1.001;
    int potens = 5000;
    double testRecursion;
    int rounds = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    do{        
        testRecursion = recursion(base,potens);
        rounds++;
    } while (rounds < 1000000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()  /pow(10,9)<< "[s]"<< std::endl;
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