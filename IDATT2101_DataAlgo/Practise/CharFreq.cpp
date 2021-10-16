#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

int main(){

    std::string text = "_names.txt";
    std::fstream f(text, std::ios::in);
    char c;
    int alphabet[28];
    double freq[28];
    double totalInputs = 0.0;
    for (size_t i = 0; i < 29; i++)
    {
        alphabet[i] = 0;
        freq[i] = 0.0;
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
        }
        f.close();
        
    }
    for (size_t i = 0; i < 29; i++)
    {
        if((i+97)<123) std::cout<<(char)(i+97)<<" appeared "<<alphabet[i]<<" times"<<std::endl;
        else if((i+97)==123) std::cout<<"space appeared "<<alphabet[i]<<" times"<<std::endl;
        else if((i+97)==124) std::cout<<"new line appeared "<<alphabet[i]<<" times"<<std::endl;
        
        totalInputs += alphabet[i];
    }
    for (size_t i = 0; i < 29; i++)
    {
        freq[i] = alphabet[i]/totalInputs;
    }
    
    std::cout<<totalInputs<<" chars counted"<<std::endl;
    for (size_t i = 0; i < 29; i++)
    {
        if((i+97)<123) std::cout<<(char)(i+97)<<" appeared with "<<freq[i]<<" frequency"<<std::endl;
        else if((i+97)==123) std::cout<<"space appeared "<<freq[i]<<" frequency"<<std::endl;
        else if((i+97)==124) std::cout<<"new line appeared "<<freq[i]<<" frequency"<<std::endl;
        
        totalInputs += alphabet[i];
    }
    return 0;
}