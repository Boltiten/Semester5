#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>


void bytt(int, int);
int splitt(int *t, int v, int h);
int median3sort (int *t,  int v, int h);
void quicksort(int *t,  int v, int h);
void quickSortMedHjelp(int *t, int v, int h);
void helpSort(int *t, int v, int h);

int main(){
    //Make vector, fill with a million numbers (later, don't print it lul)
    int arr1[10];
    int arr2[10];
    int arrSize = sizeof(arr1)/sizeof(arr1[0]);
    for (size_t i = 0; i < arrSize; i++)
    {
        arr1[i] = rand() % 10;
        arr2[i] = arr1[i];
        //std::cout<<arr2[i]<<" ";
    }
    double checksum = 0;

    //print unsorted
    //print check sum
    for (size_t i = 0; i < arrSize; i++)
    {
        checksum += arr2[i];
    }
    
    std::cout<<"\n";
    std::cout<<"checksum: "<< checksum << std::endl;

    //Timer Start
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    quicksort(arr1, 0, arrSize-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //Timer end
    std::cout<<"t1 time: "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()<<"[ns]"<<std::endl;
    

    //Timer Start
    begin = std::chrono::steady_clock::now();
    quickSortMedHjelp(arr2, 0, arrSize-1);
    end = std::chrono::steady_clock::now();
    //Timer end
    std::cout<<"t2 time: "<<std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()<<"[ns]"<<std::endl;

    //print sorted
    checksum = 0;
    std::cout<<"Sorted \n";
    for (size_t i = 0; i < arrSize; i++)
    {
        //std::cout<<arr2[i]<<" ";
        checksum += arr2[i];
    }
    
    std::cout<<"\nchecksum: "<< checksum << std::endl;

    std::cout<<""<<std::endl;


    std::cout<<"got end \n";

    //print time
    return 0;
}
void bytt(int *i, int *j){
    int k = *j;
    *j = *i;
    *i = k;
}

int splitt(int *t, int v, int h){
    int iv, ih;
    int m = median3sort(t, v, h);
    int dv = t[m];
    bytt(&t[m], &t[h-1]);
    for(iv = v, ih = h-1;;){
        while(t[++iv]<dv);
        while(t[--ih]>dv);
        if(iv >= ih) break;
        bytt(&t[iv], &t[ih]);
    }
    bytt(&t[iv],&t[h-1]);
    return iv;
}

int median3sort (int *t, int v, int h) {
    int m = (v+h)/2;
    if(t[v] > t[m]) bytt(&t[v], &t[m]);
    if(t[m] > t[h]){
        bytt(&t[m],&t[h]);
        if(t[v] > t[m]) bytt(&t[v],&t[m]);
    }
    return m;
}

void quicksort(int *t, int v, int h){

    //Quicksort
    if(h-v > 2){
        int delepos = splitt(t,v,h);
        quicksort(t,v,delepos -1);
        quicksort(t,delepos +1, h);
    } else median3sort(t,v,h);
}

void quickSortMedHjelp(int *t, int v, int h){
    //Quicksort, men kanselleres etter en x mengde kjøringer for å bruke en annen metode
    std::cout<<"h-v: "<< h-v<<std::endl;

    if(h-v > 2){
        int delepos = splitt(t,v,h);
        quickSortMedHjelp(t,v, delepos -1);
        quickSortMedHjelp(t, delepos +1, h);
    } else median3sort(t,v,h);
    

    
    //helpSort(t, 0, 0);
}

void helpSort(int *t, int v, int h){
}