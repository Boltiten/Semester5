#include <iostream>
#include <random>
#include <vector>

template<typename Type>
void sort(Type &data)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        int smallest = i;
        for (size_t j = i+1; j < data.size(); ++j)
        {
            if(data[j] < data[smallest])
            smallest = j;
        }
        auto tmp = data[i];
        data[i] = data[smallest];
        data[smallest] = tmp;        
    }    
}

int main() 
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 10.0);

    std::vector<double> table;
    for (size_t i = 0; i < 10; i++)
    {
        table.emplace_back(distribution(generator));
    }

    sort(table);

    for (auto &e : table)
    {
        std::cout<<e<<std::endl;
    }
    
     
}