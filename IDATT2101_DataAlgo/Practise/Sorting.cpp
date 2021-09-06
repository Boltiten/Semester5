#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

std::vector<int> quickSort(std::vector<int>);

int main(){
    //Make vector
    std::vector<int> v{5,3,2,1,4};

    //print unsorted
    std::cout<<"Unsorted \n";
    for (auto x : v){
        std::cout<<x<<"";
    }
    std::cout<<"\n";

    //Timer Start
    v = quickSort(v);
    //Timer end
    
    //print sorted
    std::cout<<"Sorted \n";
    for (auto x : v){
        std::cout<<x<<"";
    }

    //print time
    return 0;
}

std::vector<int> quickSort(std::vector<int> v){
    std::sort(v.begin(), v.end());
    return v;
}