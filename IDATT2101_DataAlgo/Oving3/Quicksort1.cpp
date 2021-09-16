#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <random>
#include <ctime>

void bytt(int, int);
int splitt(int *t, int v, int h);
int median3sort(int *t, int v, int h);
void quicksort(int *t, int v, int h);
void quickSortMedHjelp(int *t, int v, int h);
void insertionsort(int *t, int v, int h);

int main()
{
    //make arrays
    srand((unsigned) time(NULL));
    int arr1[250000];
    int arr2[250000];
    int arrSize = sizeof(arr1) / sizeof(arr1[0]);
    for (size_t i = 0; i < arrSize; i++)
    {
        arr1[i] = rand() % 1000000;
        arr2[i] = arr1[i];
        //std::cout<<arr2[i]<<" ";
    }
    double checksum = 0;
    double checksum2 = 0;

    //print unsorted
    //print check sum
    for (size_t i = 0; i < arrSize; i++)
    {
        checksum += arr2[i];
    }

    std::cout << "\n";
    std::cout << "checksum: " << checksum << std::endl;

    //Timer Start
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    quicksort(arr1, 0, arrSize - 1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //Timer end
    std::cout << "arr1 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    //Timer Start
    begin = std::chrono::steady_clock::now();
    quickSortMedHjelp(arr2, 0, arrSize - 1);
    end = std::chrono::steady_clock::now();
    //Timer end
    std::cout << "arr2 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    //print sorted
    bool sorted = true;
    for (size_t i = 0; i < arrSize; i++)
    {
        //std::cout<<arr2[i]<<" ";

        if (i != 0 && arr2[i] < arr2[i - 1])
        {
            std::cout << "feil sortering på i: " << i << std::endl;
            std::cout << arr2[i - 1] << ">" << arr2[i] << std::endl;
            sorted = false;
        }
        checksum2 += arr2[i];
    }

    std::cout << "\nchecksum: " << checksum2 << std::endl;
    if(sorted)std::cout<<"Arr2 is sorted"<<std::endl;
    if (checksum2 == checksum)
        std::cout << "Sum1 er lik Sum2" << std::endl;

    std::cout << "" << std::endl;

    std::cout << "got end \n";

    //print time
    return 0;
}
void bytt(int *i, int *j)
{
    int k = *j;
    *j = *i;
    *i = k;
}

int splitt(int *t, int v, int h)
{
    int iv, ih;
    int m = median3sort(t, v, h);
    int dv = t[m];
    bytt(&t[m], &t[h - 1]);
    for (iv = v, ih = h - 1;;)
    {
        while (t[++iv] < dv)
            ;
        while (t[--ih] > dv)
            ;
        if (iv >= ih)
            break;
        bytt(&t[iv], &t[ih]);
    }
    bytt(&t[iv], &t[h - 1]);
    return iv;
}

int median3sort(int *t, int v, int h)
{
    int m = (v + h) / 2;
    if (t[v] > t[m])
        bytt(&t[v], &t[m]);
    if (t[m] > t[h])
    {
        bytt(&t[m], &t[h]);
        if (t[v] > t[m])
            bytt(&t[v], &t[m]);
    }
    return m;
}

void quicksort(int *t, int v, int h)
{

    //Quicksort
    if (v < h)
    {
        int delepos = splitt(t, v, h);
        quicksort(t, v, delepos - 1);
        quicksort(t, delepos + 1, h);
    }
}

void quickSortMedHjelp(int *t, int v, int h)
{
    
    while (v < h)
    {
        if (h - v < 10)
        {
            //median3sort(t,v,h);
            insertionsort(t, v, h);
            break;
        }
        else
        {
            int delepos = splitt(t, v, h);
            if(delepos-v<h-delepos){                
                quickSortMedHjelp(t, v, delepos - 1);
                v = delepos + 1;
            }else {
                quickSortMedHjelp(t, delepos + 1, h);
                h = delepos - 1;
            }
        }
    }
}

void insertionsort(int *t, int v, int h)
{
    for (int i = v + 1; i < h + 1; i++)
    {
        int val = t[i];
        int j = i;

        while (j > v && t[j - 1] > val)
        {
            t[j] = t[j - 1];
            j -= 1;
        }
        t[j] = val;
    }
}