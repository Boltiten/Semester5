#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>


void bytt(int, int);
int splitt(std::vector<int> t, int v, int h);
int median3sort (std::vector<int>, int, int);
std::vector<int> quicksort(std::vector<int>, int, int);
std::vector<int> quickSortMedHjelp(std::vector<int>, int , int);
std::vector<int> helpSort(std::vector<int>, int, int);

int main(){
    //Make vector, fill with a million numbers (later, don't print it lul)
    std::vector<int> t1{};
    for (size_t i = 0; i < 1000000; i++)
    {
        t1.push_back(rand() % 1000000);
    }
    

    std::vector<int> t2 = t1;
    double checksum = 0;

    //print unsorted
    //print check sum
    for (auto x : t2){
        checksum += x;
    }
    std::cout<<"\n";
    std::cout<<"checksum: "<< checksum << std::endl;

    //Timer Start
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    t1 = quicksort(t1, t1.front(), t1.back());
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //Timer end
    std::cout<<"t1 time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()<<"[ns]"<<std::endl;

    //Timer Start
    begin = std::chrono::steady_clock::now();
    t2 = quickSortMedHjelp(t2, t2.back(), t2.front());
    end = std::chrono::steady_clock::now();
    //Timer end
    std::cout<<"t2 time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()<<"[ns]"<<std::endl;

    //print sorted
    checksum = 0;
    std::cout<<"Sorted \n";
    for (auto x : t2){
        checksum += x;
    }
    std::cout<<"checksum: "<< checksum << std::endl;

    std::cout<<""<<std::endl;



    //print time
    return 0;
}
void bytt(int i, int j){
    int k = j;
    j = i;
    i = k;
}

int splitt(std::vector<int> t, int v, int h){
    int iv, ih;
    int m = median3sort(t, v, h);
    int dv = t[m];
    bytt(t[m], t[h-1]);
    for(iv = v, ih = h-1;;){
        while(t[++iv]<dv);
        while(t[--ih]>dv);
        if(iv >= ih) break;
        bytt(t[iv], t[ih]);
    }
    bytt(t[iv],t[h-1]);
    return iv;
}

int median3sort (std::vector<int> t, int v, int h) {
    int m = (v+h)/2;
    if(t[v] > t[m]) bytt(t[v], t[m]);
    if(t[m] > t[h]){
        bytt(t[m],t[h]);
        if(t[v] > t[m]) bytt(t[v],t[m]);
    }
    return m;
}


std::vector<int> quicksort(std::vector<int> t, int v, int h){
    //Quicksort
    if(h-v > 2){
        int delepos = splitt(t,v,h);
        quicksort(t,v,delepos -1);
        quicksort(t,delepos +1, h);
    } else median3sort(t,v,h);
    return t;
}
std::vector<int> quickSortMedHjelp(std::vector<int> t, int v, int h){
    //Quicksort, men kanselleres etter en x mengde kjøringer for å bruke en annen metode
    if(h-v > 2){
        int delepos = splitt(t,v,h);
        quicksort(t,v,delepos -1);
        quicksort(t,delepos +1, h);
    } else median3sort(t,v,h);

    helpSort(t, 0, 0);
    return t;
}

std::vector<int> helpSort(std::vector<int> t, int v, int h){
    return t;
}