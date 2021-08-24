#include <iostream>

void printMessage(const std::string& message){
    std::cout<<message<<std::endl;
}

int main(){
    printMessage("Hello World!");
    return 0;
}