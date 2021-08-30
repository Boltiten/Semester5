#include <iostream>
#include <math.h>
#include <chrono>
#include <cstdlib>
#include <time.h>

double recursion(double x, int n);

int main(){
    double base = 1.001;
    int potens = 5000;
    double testRecursion;
    int rounds = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    do{        
        testRecursion = recursion(base,potens);
        rounds++;
        end = std::chrono::steady_clock::now();
    } while (std::chrono::duration_cast<std::chrono::seconds>(end-begin).count() < 1);
    end = std::chrono::steady_clock::now();
    std::cout<<"Time spent: ["<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()<<"ms], should be very close to 1s"<<std::endl;
    std::cout << "Rounds per second: " <<rounds << " rounds in time spent second"<< std::endl;
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