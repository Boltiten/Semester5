#include <iostream>
#include <fstream>
#include <string>

/**
 * Les inn tempereaturer
 * Finn antallet over 20, under 10 og mellom de.
 * */

//declaration
void read_temperatures(double temperatures[], int length);
int getLines();

int main(){
    int length = getLines();
    std::cout<<"file length: "<< length <<std::endl;
    double temperature[length];
    read_temperatures(temperature, length);
    return 0;
}

int getLines(){
    std::string line;
    std::fstream temperatureFile;
    int length = 0;
    temperatureFile.open("temperatures.txt");
    while(std::getline(temperatureFile, line)){
        ++length;
    }
    temperatureFile.close();
    return length;
}

void read_temperatures(double temperatures[], int length){
    int under= 0;
    int between = 0;
    int over = 0;
    std::string line;
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
    std::cout<<"Temperaturer under 10 grader:        "<<under<<std::endl;
    std::cout<<"Temperaturer mellom 10 og 20 grader: "<<between<<std::endl;
    std::cout<<"Temperaturer over 20 grader:         "<<over<<std::endl;  
    
}