#include <iostream>
#include <fstream>

/**
 * Les inn tempereaturer
 * Finn antallet over 20, under 10 og mellom de.
 * */

//declaration
void read_temperatures(double temperatures[], int length);

int main(){
    int length = 5;
    double* temperature = new double [length];
    read_temperatures(temperature, length);    
    delete[] temperature;
    return 0;
}

void read_temperatures(double temperatures[], int length){
    int under= 0;
    int between = 0;
    int over = 0;
    std::fstream temperatureFile;
    temperatureFile.open("temperatures.txt");    
    for (size_t i = 0; i < length; i++)
    {
        temperatureFile>>temperatures[i];
        if(temperatures[i]<10){
            under++;
        } else if( temperatures[i]>20){
            over++;
        } else {
            between++;
        }
    }
    temperatureFile.close();
    std::cout<<"Temperaturer under 10 grader:        "<<under<<std::endl;
    std::cout<<"Temperaturer mellom 10 og 20 grader: "<<between<<std::endl;
    std::cout<<"Temperaturer over 20 grader:         "<<over<<std::endl;  
    
}