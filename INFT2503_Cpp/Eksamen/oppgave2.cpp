#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal{
    string species;
public:
    Animal(string species_) : species(species_){};
    string produce();
};

string Animal::produce(){
    if (species=="chicken")return "egg";
    if (species=="cow")return "milk";
    if (species=="sheep")return "wool";
    return "1";
}


class Farm{

public: 
    void add_animal(string species);
    vector<Animal*> animals;   
};

void Farm::add_animal(string species)
{
    Animal *a = new Animal(species);
    animals.push_back(a);
    
};

int main(){
Farm farm;


farm.add_animal("chicken");
farm.add_animal("chicken");
farm.add_animal("chicken");
farm.add_animal("cow");
farm.add_animal("sheep");
farm.add_animal("sheep");

cout << "Farm production: " << endl;

for (auto &animal : farm.animals)
  cout << animal->produce() << endl;
    return 0;
}