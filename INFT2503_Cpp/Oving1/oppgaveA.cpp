#include <iostream>

/**
 * Les inn tempereaturer
 * Finn antallet over 20, under 10 og mellom de.
 * */

//declaration
void inputTemperatures();

int main(){
    inputTemperatures();
    return 0;
}


void inputTemperatures(){
    int under= 0;
    int between = 0;
    int over = 0;
    int input = 0;
    int length = 5;


    std::cout<< "Du skal skrive inn 5 tempereaturer" << std::endl;
    for (size_t i = 0; i < length; i++)
    {
        std::cin >> input;
        std::cout<< "Du skrev in: " << input << std::endl;
        if(input<10){
            under++;
        } else if( input>20){
            over++;
        } else {
            between++;
        }
    }  

    std::cout<<"Temperaturer under 10 grader:        "<<under<<std::endl;
    std::cout<<"Temperaturer mellom 10 og 20 grader: "<<between<<std::endl;
    std::cout<<"Temperaturer over 20 grader:         "<<over<<std::endl;  
    
}