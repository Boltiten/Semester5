#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    std::vector<double> v = {0,1,2,3,4};
    v.emplace(v.begin(), 5);
    auto it = find(v.begin(), v.end(),2);
    if(it==v.end()){
        std::cout<<"couldnt find number"<<std::endl;
    } else {
        std::cout<<*it<<std::endl;
    }
    return 1;
}

