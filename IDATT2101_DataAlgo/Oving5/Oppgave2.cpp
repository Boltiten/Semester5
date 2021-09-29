/**
 * Last = n inputs / m størrelse på tabell.
 * n = 10_000_000
 * 10_000_000/0.75 = 12_500_000 = m. Finn et primtall eller toerpotens som er større og nære
 * 
 * 
 * Lag en array med tilfeldige tall
 * 
 * */

#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <array>
#include <random>
#include <algorithm>

//stuff
const int arrSize = 10;
const int hashTableSize = 11;
int collisions[3] = {0,0,0};
void PrintLine();
void swap(int *a, int *b);
void printArray(int arr[], int n);
void randomize(int arr[], int n);

template <typename K, typename V>

class HashNode
{
public:
    V value;
    K key;
    
    HashNode(K key, V value)
    {
        this->value=value;
        this->key=key;
    }
};

template <typename K, typename V>
class HashMap
{
    HashNode<K,V>** arr;
    int capacity;
    int size;
    HashNode<K,V>* dummy;

public:
    explicit HashMap()
    {
        capacity = 20;
        size = 0;
        arr = new HashNode<K,V>*[capacity];

        for (size_t i = 0; i < capacity; i++)
        {
            arr[i] = NULL;
        }
        
        dummy = new HashNode<K, V>(-1,-1);
    }

    int hashCode(K key)
    {
        return key % capacity;
    }
    bool isEmpty(){
        return size == 0;
    }
    int sizeofMap(){
        return size;
    }

};

template <typename K, typename V>
class HashLinear : public HashMap 
{
    
public:
    using HashMap::HashMap;
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = hashCode(key);
        
        //collision
        while(arr[hashIndex] != NULL)
        {
            //linear
            collisions[0]++;
            hashIndex++;
            hashIndex%=capacity;

            //her kan jeg finne forskjellige metoder å legge inn på, kanskje en id om hvilken hash vi skal bruke.
        }
        if(arr[hashIndex] == NULL)
        {
            size++;
            arr[hashIndex] = temp;
        }
    }

    V delete(int key)
    {
        int hashIndex = hashCode(key);

        while (arr[hashIndex] != NULL)
        {
            if(arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = arr[hashIndex];

                arr[hashIndex] = dummy;

                size--;
                return temp->value;
            }
            hashIndex++;
            hashindex%=capacity;
        }
        return NULL;
    }
    V get(int key)
    {
        int hashIndex = hashCode(key);
        int counter = 0;

        while(arr[hashIndex] != NULL){
            if(counter++ > capacity) return NULL;
            if(arr[hashIndex->key==key])return arr[hashIndex]->value;
            hashindex++;
            hashIndex %= capacity;
        }
        return NULL;
    }
};

template <typename K, typename V>
class HashQuadratic : public HashMap
{
public:
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = hashCode(key);
        
        //collision
        while(arr[hashIndex] != NULL)
        {
            //linear
            collisions[1]++;
            hashIndex++;
            hashIndex%=capacity;

            //her kan jeg finne forskjellige metoder å legge inn på, kanskje en id om hvilken hash vi skal bruke.
        }
        if(arr[hashIndex] == NULL)
        {
            size++;
            arr[hashIndex] = temp;
        }
    }

    V delete(int key)
    {
        int hashIndex = hashCode(key);

        while (arr[hashIndex] != NULL)
        {
            if(arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = arr[hashIndex];

                arr[hashIndex] = dummy;

                size--;
                return temp->value;
            }
            hashIndex++;
            hashindex%=capacity;
        }
        return NULL;
    }
    V get(int key)
    {
        int hashIndex = hashCode(key);
        int counter = 0;

        while(arr[hashIndex] != NULL){
            if(counter++ > capacity) return NULL;
            if(arr[hashIndex->key==key])return arr[hashIndex]->value;
            hashindex++;
            hashIndex %= capacity;
        }
        return NULL;
    }
};



int hashLinear(){
    //hi(X) = (hash(X)+i)%HashTableSize
    //kjør en while som sjekker om table[index] = NULL, og inkrementerer i når det er noe der.
    //plasser element i posisjon en index havner på.
    //ved collision inkrementerer vi collisions[0];
    /*
    int index = (key%HashTableSize); 
    int i = 1;
    
    while(hash[index] != null)
    {
        i++;
        collisions[0]++;
        index = (key+i)%HashTableSize;
    }

    */

    return 0; //return index;


}
int hashQuadratic(){
    //hi(X) = (hash(X)+i^2)%HashTableSilze - ez utvikling fra linear
    //ved collision inkrementerer vi collisions[1];
    /*
    int index = (key%HashTableSize); 
    int i = 1;
    
    while(hash[index] != null)
    {
        i++;
        collisions[0]++;
        index = (key+i*i)%HashTableSize;
    }

    */

    return 0; //return index;
}
int hashDouble(){
    //hi(X) = (Hash(X) +i*Hash2(X))%HashTableSize
    //ved collision inkrementerer vi collisions[2];
    /*
    int index = (key%HashTableSize); 
    int i = 1;
    
    while(hash[index] != null)
    {
        i++;
        collisions[0]++;
        index = ((key%HashTableSize)+i*(key%HashTableSize))%HashTableSize;
    }

    */

    return 0; //return index;
}

int main(){
    
    int *numbers = (int*)malloc(arrSize*sizeof(int));
    numbers[0] = rand()%1000 +1;
    for (size_t i = 1; i < arrSize; i++)
    {
        numbers[i] = numbers[i-1] + rand()%10 + 1;
    }
    //shuffel funksjon jeg fant på internett.
    //randomize(numbers, arrSize);


    /**
     * 3 hashtabeller /m åpen addressering
     *      lineær probing, altså send til første ledige index i tabellen.
     *      kvadratisk probing
     *      dobbel hashing
     * */

    //Opprett hashtabeller
    HashLinear h1;
    

    for (size_t i = 0; i < arrSize; i++)
    {
        //send tabellene over til insert, og hash riktig.
    }

    //Print antall kollisjoner
    /* 
    for (size_t i = 0; i < 3; i++)
    {
        std::cout<<"Collisions type "<< i+1 << " had: "<<collisions[i]<<" collisions."<<std::endl;
    } */
    

    free(numbers);
    return 0;
}
void PrintLine(){
    std::cout<<"----------------------------------------------------------------------------------------------------------------------------"<<std::endl;
}


//Kopierte inn denne shufflingen fra internett, NB: ikke laget selv!
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// A utility function to print an array
void printArray (int arr[], int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}
// A function to generate a random
// permutation of arr[]
void randomize (int arr[], int n)
{
    // Use a different seed value so that
    // we don't get same result each time
    // we run this program
    srand (time(NULL));
 
    // Start from the last element and swap
    // one by one. We don't need to run for
    // the first element that's why i > 0
    for (int i = n - 1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);
 
        // Swap arr[i] with the element
        // at random index
        swap(&arr[i], &arr[j]);
    }
}
