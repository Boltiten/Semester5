//bruker boka

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <math.h>
#include <iomanip>


int stringTranslateInt(std::string input);
const unsigned A = 2654435769U;
int collisions = 0;

class Hash{
    private:
        static const int tableSize = 179;
        struct item{
            std::string name;
            item* next;
        };
        item* HashTable[tableSize];
    public:
        Hash();
        int HashFunction(std::string key);
        void AddItem(std::string name);
        int NumberOfItemsInIndex(int index);
        void PrintTable();
        void PrintItemsInIndex(int index);
        void FindName(std::string name);
};

Hash::Hash()
{
    //initialize
    for (int i = 0; i < tableSize; i++)
    {
        HashTable[i] = new item;
        //HashTable[i]->name.erase();
        HashTable[i]->next = NULL;
    }    
}

void Hash::AddItem(std::string name){
    int index = HashFunction(name);

    if(HashTable[index]->name.empty())
    {
        HashTable[index]->name = name;
    }
    else
    {
        item *ptr = HashTable[index];
        item *n = new item;
        n->name = name;
        n->next = NULL;
        std::cout<<ptr->name<<" collides with "<<n->name<<std::endl;
        collisions++;
        //find next avaliable pos
        while (ptr->next != NULL)
        {      
            ptr=ptr->next;            
        }
        ptr->next = n;
    }
}

int Hash::NumberOfItemsInIndex(int index)
{
    int count = 0;

    if(HashTable[index]->name.empty()){
        return 0;
    }
    else
    {
        count++;
        item* ptr = HashTable[index];
        while(ptr->next != NULL){
            count++;
            ptr = ptr->next;
        }
    }
    return count;
}

void Hash::PrintTable()
{
    int number;
    for (int i = 0; i < tableSize; i++)
    {
        PrintItemsInIndex(i);

    }
    
}
void Hash::PrintItemsInIndex(int index){
    item* ptr = HashTable[index];
    if(ptr->name.empty())
    {
        std::cout<<"index: "<<index<< " is empty"<<std::endl;
    }
    else
    {
        std::cout<<"index: "<< index << " contains \n";
        while(ptr != NULL)
        {
            std::cout<<ptr->name<<std::endl;
            ptr = ptr->next;            
        }
    }
}

void Hash::FindName(std::string name)
{
    int index = HashFunction(name);
    bool foundName = false;
    std::string tmp;

    item* ptr = HashTable[index];
    while(ptr != NULL)
    {
        if(ptr->name == name)
        {
            foundName = true;
            tmp = ptr->name;
        }
        ptr = ptr->next;
    }
    if(foundName){
        std::cout<<"found name: "<<name<<" at index "<<index<<std::endl;
    }
    else
    {
        std::cout<<"Couldnt find: "<<name<<std::endl;
    }
}

int Hash::HashFunction(std::string key){
    int hash = 0;
    int index;
    index = stringTranslateInt(key);
    return index%tableSize;
}

int stringTranslateInt(std::string input)
{
    //translate names to int
    int value = 0;
    for (int i = 0; i < input.length(); i++)
    {
        value += input.at(i) * (i + 1);
    }
    return value;
}

int main()
{
    Hash h;

    std::string names = "names.txt";
    std::fstream f(names, std::ios::in);
    std::string name;

    if (f.is_open())
    {
        while (getline(f,name))
        {
            h.AddItem(name);            
        }
        f.close();
    }
    else
        std::cout << "Couldn't open file!" << std::endl;

    //h.PrintTable();
    std::cout<<"Collisions: "<<collisions<<std::endl;
    h.FindName("Morten Stavik Eggen");
    h.FindName("Helge Hafting");
    h.FindName("Sander August Heggland Schrader");
    h.FindName("Arvid Jr Kirkbakk");
    std::cout<<"There are "<<h.NumberOfItemsInIndex(0)<<" names at index 0"<<std::endl;;
    double last = 117.0 / 179.0;
    std::cout<<"Lasten er "<<std::setprecision(2)<<last<<std::endl;
    double mean = collisions/118.0;
    std::cout<<"Gjennomsnittlig antall collisjoner per person:  "<<std::setprecision(2)<<mean<<std::endl;

    return 0;
}