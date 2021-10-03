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
const int PRIME = 29;
const int hashSize = 10000019;
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
    int collisions;
    HashNode<K,V>* dummy;

public:
    explicit HashMap(int cap)
    {
        capacity = cap;
        size = 0;
        collisions = 0;
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
    int getCollisions(){
        return collisions;
    }
    void zeroCollisions(){
        collisions = 0;
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
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = this->hashCode(key);
        int i = 0;
        
        //collision
        while(this->arr[hashIndex] != NULL
                && this->arr[hashIndex]->key !=-1)
        {
            //linear
            this->collisions++;
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

    void deleteNode(int key)
    {
        int hashIndex = this->hashCode(key);
        int i = 0;

        while (this->arr[hashIndex] != NULL)
        {
            if(this->arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = this->arr[hashIndex];

                this->arr[hashIndex] = this->dummy;

                this->size--;
                return;
            }
            i++;
            hashIndex += i;
            hashIndex%=this->capacity;
        }
    }
    V get(int key)
    {
        int hashIndex = this->hashCode(key);
        int counter = 0;
        int i = 0;

        while(this->arr[hashIndex] != NULL){
            if(counter++ > this->capacity) return NULL;
            if(this->arr[hashIndex]->key==key)return this->arr[hashIndex]->value;
            i++;
            hashIndex += i;
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
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = this->hashCode(key);
        int i=0;
        
        //collision
        while(this->arr[hashIndex] != NULL
                && this->arr[hashIndex]->key !=-1)
        {
            //linear
            this->collisions++;
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

    void deleteNode(int key)
    {
        int hashIndex = this->hashCode(key);
        int i = 0;

        while (this->arr[hashIndex] != NULL)
        {
            if(this->arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = this->arr[hashIndex];

                this->arr[hashIndex] = this->dummy;

                this->size--;
                return;
            }
            i++;
            hashIndex+= i*i;
            hashIndex%=this->capacity;
        }
    }
    V get(int key)
    {
        int hashIndex = this->hashCode(key);
        int counter = 0;
        int i = 0;

        while(this->arr[hashIndex] != NULL){
            if(counter++ > this->capacity) return NULL;
            if(this->arr[hashIndex]->key==key)return this->arr[hashIndex]->value;
            i++;
            hashIndex+= i*i;
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
    void insert(K key, V value)
    {
        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        int hashIndex = this->hashCode(key);
        int hashIndex2 = (key%PRIME)+1;
        int i=0;
        
        //collision
        while(this->arr[hashIndex] != NULL
                && this->arr[hashIndex]->key !=-1)
        {
            //Double hashing 
            this->collisions++;
            i++;
            int newIndex = (hashIndex+i*hashIndex2);
            hashIndex%=this->capacity;
            if(this->arr[newIndex] == NULL){
                hashIndex = newIndex;
                break;
            }

            //her kan jeg finne forskjellige metoder å legge inn på, kanskje en id om hvilken hash vi skal bruke.
        }
        if(this->arr[hashIndex] == NULL)
        {
            this->size++;
            this->arr[hashIndex] = temp;
        }
    }

    void deleteNode(int key)
    {
        int hashIndex = this->hashCode(key);
        int hashIndex2 = (key%PRIME)+1;
        int i=0;

        while (this->arr[hashIndex] != NULL)
        {
            if(this->arr[hashIndex]->key==key)
            {
                HashNode<K,V>* temp = this->arr[hashIndex];

                this->arr[hashIndex] = this->dummy;

                this->size--;
                return;
            }
            i++;
            int newIndex = (hashIndex+i*hashIndex2);
            hashIndex%=this->capacity;
            if(this->arr[newIndex] == NULL){
                hashIndex = newIndex;
            }
        }
    }
    V get(int key)
    {
        int hashIndex = this->hashCode(key);
        int counter = 0;
        int hashIndex2 = (key%PRIME)+1;
        int i=0;

        while(this->arr[hashIndex] != NULL){
            if(counter++ > this->capacity) return NULL;
            if(this->arr[hashIndex]->key==key)return this->arr[hashIndex]->value;
            i++;
            int newIndex = (hashIndex+i*hashIndex2);
            hashIndex%=this->capacity;
            if(this->arr[newIndex] == NULL){
                hashIndex = newIndex;
            }
        }
        return NULL;
    }
    
};

int main(){
    srand(time(NULL));
    int *numbers = (int*)malloc(arrSize*sizeof(int));
    numbers[0] = rand()%100 +1;
    for (size_t i = 1; i < arrSize; i++)
    {
        numbers[i] = numbers[i-1] + rand()%100 + 1;
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
    
    HashLinear<int, int> h1 = HashLinear<int, int>(hashSize);
    HashQuadratic<int, int> h2 = HashQuadratic<int, int>(hashSize);
    HashDouble<int, int> h3 = HashDouble<int, int>(hashSize);    

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize/2; i++)
    {
        h1.insert(numbers[i],numbers[i]);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på linear 50%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize/2; i++)
    {
        h2.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på qudratic 50%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize/2; i++)
    {
        h3.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på double 50%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    //Print antall kollisjoner
    std::cout<<"Collisions type: linear 50%,      had: "<<h1.getCollisions()<<" collisions."<<std::endl; 
    std::cout<<"Collisions type: quadratic 50%,   had: "<<h2.getCollisions()<<" collisions."<<std::endl; 
    std::cout<<"Collisions type: double hash 50%, had: "<<h3.getCollisions()<<" collisions."<<std::endl;
    
    HashLinear<int, int> h4 = HashLinear<int, int>(hashSize);
    HashQuadratic<int, int> h5 = HashQuadratic<int, int>(hashSize);
    HashDouble<int, int> h6 = HashDouble<int, int>(hashSize);

    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize*0.9; i++)
    {
        h4.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på linear 90%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize*0.9; i++)
    {
        h5.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på qudratic 90%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize*0.9; i++)
    {
        h6.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på double 90%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    //Print antall kollisjoner
    std::cout<<"Collisions type: linear 90%,      had: "<<h4.getCollisions()<<" collisions."<<std::endl; 
    std::cout<<"Collisions type: quadratic 90%,   had: "<<h5.getCollisions()<<" collisions."<<std::endl; 
    std::cout<<"Collisions type: double hash 90%, had: "<<h6.getCollisions()<<" collisions."<<std::endl;


    HashLinear<int, int> h7 = HashLinear<int, int>(hashSize);
    HashQuadratic<int, int> h8 = HashQuadratic<int, int>(hashSize);
    HashDouble<int, int> h9 = HashDouble<int, int>(hashSize);

    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize*0.99; i++)
    {
        h7.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på linear 99%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize*0.99; i++)
    {
        h8.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på qudratic 99%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    begin = std::chrono::steady_clock::now();
    for (size_t i = 0; i < arrSize*0.99; i++)
    {
        h9.insert(numbers[i],numbers[i]);
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Tid brukt på double 99%: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    //Print antall kollisjoner
    std::cout<<"Collisions type: linear 99%,      had: "<<h7.getCollisions()<<" collisions."<<std::endl; 
    std::cout<<"Collisions type: quadratic 99%,   had: "<<h8.getCollisions()<<" collisions."<<std::endl; 
    std::cout<<"Collisions type: double hash 99%, had: "<<h9.getCollisions()<<" collisions."<<std::endl;

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
