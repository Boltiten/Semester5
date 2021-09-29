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
const int arrSize = 10000000;
int collisions[3] = {0,0,0};
void PrintLine();
void swap(int *a, int *b);
void printArray(int arr[], int n);
void randomize(int arr[], int n);

template <class K, class V>

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

template <class K, class V>
class HashMap
{
protected:
    HashNode<K,V>** arr;
    int capacity;
    int size;
    HashNode<K,V>* dummy;

public:
    explicit HashMap()
    {
        capacity = 16777216;
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
    void display()
    {
        for (int i = 0; i < this->capacity; i++) {
            if (this->arr[i] != NULL && this->arr[i]->key != -1)
                std::cout << "key = " << this->arr[i]->key
                     << "  value = "
                     << this->arr[i]->value << std::endl;
        }
    }
    
};

template <class K, class V>
class HashLinear :  public HashMap <K,V>
{
    using HashMap<K,V>::HashMap;
public:
    using HashMap<K,V>::display;
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = this->hashCode(key);
        int i = 0;
        
        //collision
        while(this->arr[hashIndex] != NULL)
        {
            //linear
            collisions[0]++;
            i++;
            hashIndex += i;
            hashIndex%=this->capacity;

            //her kan jeg finne forskjellige metoder å legge inn på, kanskje en id om hvilken hash vi skal bruke.
        }
        if(this->arr[hashIndex] == NULL)
        {
            this->size++;
            this->arr[hashIndex] = temp;
        }
    }

    V deleteNode(int key)
    {
        int hashIndex = this->hashCode(key);

        while (this->arr[hashIndex] != NULL)
        {
            if(this->arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = this->arr[hashIndex];

                this->arr[hashIndex] = this->dummy;

                this->size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex%=this->capacity;
        }
        return NULL;
    }
    V get(int key)
    {
        int hashIndex = this->hashCode(key);
        int counter = 0;

        while(this->arr[hashIndex] != NULL){
            if(counter++ > this->capacity) return NULL;
            if(this->arr[hashIndex]->key==key)return this->arr[hashIndex]->value;
            hashIndex++;
            hashIndex %= this->capacity;
        }
        return NULL;
    }
    
};


template <class K, class V>
class HashQuadratic :  public HashMap <K,V>
{
    using HashMap<K,V>::HashMap;
public:
    using HashMap<K,V>::display;
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = this->hashCode(key);
        int i=0;
        
        //collision
        while(this->arr[hashIndex] != NULL)
        {
            //linear
            collisions[1]++;
            i++;
            hashIndex+= i*i;
            hashIndex%=this->capacity;

            //her kan jeg finne forskjellige metoder å legge inn på, kanskje en id om hvilken hash vi skal bruke.
        }
        if(this->arr[hashIndex] == NULL)
        {
            this->size++;
            this->arr[hashIndex] = temp;
        }
    }

    V deleteNode(int key)
    {
        int hashIndex = this->hashCode(key);

        while (this->arr[hashIndex] != NULL)
        {
            if(this->arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = this->arr[hashIndex];

                this->arr[hashIndex] = this->dummy;

                this->size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex%=this->capacity;
        }
        return NULL;
    }
    V get(int key)
    {
        int hashIndex = this->hashCode(key);
        int counter = 0;

        while(this->arr[hashIndex] != NULL){
            if(counter++ > this->capacity) return NULL;
            if(this->arr[hashIndex]->key==key)return this->arr[hashIndex]->value;
            hashIndex++;
            hashIndex %= this->capacity;
        }
        return NULL;
    }
    
};

template <class K, class V>
class HashDouble :  public HashMap <K,V>
{
    using HashMap<K,V>::HashMap;
public:
    using HashMap<K,V>::display;
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = this->hashCode(key);
        int i=0;
        
        //collision
        while(this->arr[hashIndex] != NULL)
        {
            //Double hashing 
            collisions[2]++;
            i++;
            hashIndex;
            hashIndex%=this->capacity;

            //her kan jeg finne forskjellige metoder å legge inn på, kanskje en id om hvilken hash vi skal bruke.
        }
        if(this->arr[hashIndex] == NULL)
        {
            this->size++;
            this->arr[hashIndex] = temp;
        }
    }

    V deleteNode(int key)
    {
        int hashIndex = this->hashCode(key);

        while (this->arr[hashIndex] != NULL)
        {
            if(this->arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = this->arr[hashIndex];

                this->arr[hashIndex] = this->dummy;

                this->size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex%=this->capacity;
        }
        return NULL;
    }
    V get(int key)
    {
        int hashIndex = this->hashCode(key);
        int counter = 0;

        while(this->arr[hashIndex] != NULL){
            if(counter++ > this->capacity) return NULL;
            if(this->arr[hashIndex]->key==key)return this->arr[hashIndex]->value;
            hashIndex++;
            hashIndex %= this->capacity;
        }
        return NULL;
    }
    
};
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
    
    HashLinear<int, int> h1;
    HashQuadratic<int, int> h2;
    

    for (size_t i = 0; i < arrSize; i++)
    {
        h1.insert(numbers[i],numbers[i]);
        h2.insert(numbers[i],numbers[i]);
    }

    //Print antall kollisjoner
     
    for (size_t i = 0; i < 3; i++)
    {
        std::cout<<"Collisions type "<< i+1 << " had: "<<collisions[i]<<" collisions."<<std::endl;
    }
    //h1.display();

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
