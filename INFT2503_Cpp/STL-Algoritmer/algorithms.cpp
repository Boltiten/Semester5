#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream &operator<<(ostream &out, const vector<int> &table) {
  for (auto &e : table)
    out << e << " ";
  return out;
}

bool isOdd(int i){return ((i%2)==1);}

int main() {
  vector<int> v1 = {3, 3, 12, 14, 17, 25, 30};
  cout << "v1: " << v1 << endl;

  vector<int> v2 = {2, 3, 12, 14, 24};
  cout << "v2: " << v2 << endl;

  // Søker etter enkeltverdi med find()
  auto pos = find(v1.begin(), v1.end(), 25);
  if (pos != v1.end()) {
    cout << "25 fins i v1 på indeks " << (pos - v1.begin()) << endl;
  } else
    cout << "25 fins ikke i v1" << endl;

  auto start = v1.begin() + 2;
  auto end = v1.end() - 2;
  cout << "Søker i en del av tabellen: ";
  for (auto it = start; it != end; ++it)
    cout << *it << " ";
  cout << endl;
  pos = find(start, end, 14);
  if (pos != end) {
    cout << "14 fins i v1 på indeks " << (pos - v1.begin()) << endl;
  } else
    cout << "14 fins ikke i v1" << endl;

  // Søker etter den første blant flere, find_first_of()
  // Søker i v1 {3, 3, 12, 14, 17, 25, 30} etter den første av
  // {12, 14, 24} (en del av v2). Svaret skal bli 2
  pos = find_first_of(v1.begin(), v1.end(), v2.begin() + 2, v2.end());
  cout << "Første på indeks " << (pos - v1.begin()) << endl;

  // Søker etter to like, ved siden av hverandre, adjacent_find()
  pos = adjacent_find(v1.begin(), v1.end());
  cout << "Finner to like på indeks " << (pos - v1.begin()) << endl;

  // Teller antall 3-tall i v1
  cout << "v1 inneholder " << count(v1.begin(), v1.end(), 3) << " 3-tall" << endl;

  // Finner største verdi i v1 (max_element returnerer en iterator)
  cout << "Største verdi i v1 er " << *max_element(v1.begin(), v1.end()) << endl; // dereferanse


  cout<<"\n\n\n"<<"Leksestart"<<endl;
  //bruk find_if til å finne første element større enn 15 i v1

  /*
  Vi definerer "omtrent lik" til å bety at forskjellen mellom to verdier ikke er mer enn 2. Finn ut om 
  intervallet [v1.begin(), v1.begin() + 5> og v2 er like i denne betydningen av likhet. Hva med intervallet [v1.begin(), v1.begin() + 4>? Bruk algoritmen equal.
  */

  //Erstatt alle oddetall i v1 med 100 ved hjelp av replace_copy_if.
  replace_copy_if(v1.begin(),v1.end(),v1.begin(), isOdd, 100);
  cout << "v1: " << v1 << endl;
}

/* Kjøring av programmet:
v1: 3 3 12 14 17 25 30
v2: 2 3 12 14 24
25 fins i v1 på indeks 5
Søker i en del av tabellen: 12 14 17
14 fins i v1 på indeks 3
Første på indeks 2
Finner to like på indeks 0
v1 inneholder 2 3-tall
Største verdi i v1 er 30
*/