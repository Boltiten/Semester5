#include <iostream>
#include <functional>
#include <string>
#include <vector>

using namespace std;


class Chess {
public:
  enum class Player { white,
                      black };

 

  static string player_name(Player player) {
    if (player == Player::white)
      return "white";
    else
      return "black";
  }

 

  vector<function<void(Player winner)>> on_victory;
 

  /// In this game, black always wins
  void play() {

       for (size_t i = 0; i < on_victory.size(); i++)
       {
           on_victory[i](Player::black);
       }

   }
};

int main(){
Chess chess;

 

chess.on_victory.emplace_back([](Chess::Player winner) {
  cout << Chess::player_name(winner) << " won" << endl;
});

 

chess.on_victory.emplace_back([](Chess::Player winner) {
  cout << Chess::player_name(winner == Chess::Player::white
                                 ? Chess::Player::black
                                 : Chess::Player::white)
       << " lost" << endl;
});

 

chess.play();    

    return 0;
}

/*
black won
white lost
*/