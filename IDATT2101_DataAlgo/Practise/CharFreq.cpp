#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

int main(){

    std::string text = "_names.txt";
    std::fstream f(text, std::ios::in);
    char c;
    int alphabet[28];
    int totalInputs = 0;
    for (size_t i = 0; i < 29; i++)
    {
        alphabet[i] = 0;
    }    

    if (f.is_open())
    {

        while (f.get(c))
        {
            c = tolower(c);
            alphabet[(int)c - 97]++;
            //space
            if((int)c == 32)alphabet[26]++;
            //new line
            if((int)c == 10)alphabet[27]++;
            totalInputs++;
        }
        f.close();
        
    }
    std::cout<<totalInputs<<std::endl;
    totalInputs = 0;
    for (size_t i = 0; i < 29; i++)
    {
        //std::cout<<(char)(i+97)<<" appeared "<<alphabet[i]<<" times"<<std::endl;
        totalInputs += alphabet[i];
    }
    std::cout<<totalInputs<<std::endl;
    
    return 0;
}