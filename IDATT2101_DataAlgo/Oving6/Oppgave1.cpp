#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>

void printVector(std::vector<std::vector<int>> e);

//Forsøk 1
class Graph {
public:
    Graph(std::vector<int> &v, std::vector<std::vector<int>> &e):v_(v), e_(e){}
    bool IsEulerWalkable();
    std::vector<int> v_;
    std::vector<std::pair<int,int>> e_;
};


int main(){

    std::string filename = "tall.txt";
    std::fstream f(filename, std::ios::in);
    int inputNumbers;
    std::vector<int> v;
    std::vector<std::vector<int>> e;
    int i = 0;

    if(f.is_open())
    {
        while(f >> inputNumbers)
        {
            i++;
            v.push_back(inputNumbers);
            if(i%2==0)
            {
                e.push_back(v);
                v.clear();
            }
        }
    }
    Graph g(v,e);

    printVector(e);

    f.close();
    return 0;
}

void printVector(std::vector<std::vector<int>> e){
    for (auto v : e)
    {
        for (auto i : v)
        {
            std::cout<<i<<" ";
        }
        std::cout<<std::endl;
        
    }
    
}