#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ai_functions.h"


void payout(){

  using std::cout;

  srand(time(0));

  const int price = 3;
  const int games = 100;

  int money = 100;

  cout << "Initial money: " << money << '\n';

  for(int i = 0; i < games; i++){
    money += rand() % 6 + 1 - price;
  }

  cout << "Money after " << games << " games: " << money << '\n';

}
