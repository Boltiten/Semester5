#include <iostream>
#include <chrono>
#include <math.h>

int main(){
    double base = 1.0001;
    int potens = 10000;
    double result;
    int rounds = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    do{        
        result = pow(base, potens);
        end = std::chrono::steady_clock::now();
        rounds ++;
    } while (std::chrono::duration_cast<std::chrono::seconds>(end-begin).count() < 1);
    end = std::chrono::steady_clock::now();
    std::cout<<"Time spent: ["<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()<<"ms], should be very close to 1s"<<std::endl;
    std::cout << "Rounds per second: " <<rounds << " rounds in time spent second"<< std::endl;
    std::cout<<result<<std::endl;
    return 0;
}