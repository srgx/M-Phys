#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;

char checkPattern(const std::vector<char> & vec);

int main(){

  std::cout << "Execute interactive program directly\n";
  std::cout << "Comment out line with 'return'\n";
  std::cout << "Part 5 - Chapter 25 - Exercise 1\n";

  // Comment out this line
  return 0;

  srand(time(0));

  const int numGames = 30;
  char input;
  char computerChoice;
  int points = 0;

  std::vector<char> vec;

  for(int i=0;i<numGames;i++){

    computerChoice =
      0 == i ?
        0 == rand() % 2 ? 'h' : 't' :
        i < 3 ?
          't' == vec.back() ? 'h' : 't'  :
          checkPattern(vec);

    do {
      cout << "Round " << i+1 << '\n';
      cout << "Heads(h) or Tails(t): ";
      cin >> input; while(cin.get()!='\n'){ continue; }
    } while(!('h'==input||'t'==input));

    vec.push_back(input);

    if(computerChoice!=input){
      cout << "Win\n";
      points++;
    } else {
      cout << "Lose\n";
    }

  }

  cout << "Score: " << points << '/' << numGames << '\n';

}

char checkPattern(const std::vector<char> & vec){

  const int len = vec.size();
  const int blIndex = len - 2;

  int heads, tails;
  heads = tails = 0;

  // Look for pattern in past moves
  for(int i=0;i<blIndex;i++){

    // Two moves match
    if(vec[i]==vec[blIndex] && vec[i+1]==vec.back()){

      char thirdMove = vec[i+2];

      // Increase chance of 'h' or 't'
      if('h'==thirdMove){
        heads++;
      } else if('t'==thirdMove){
        tails++;
      }

    }

  }

  // Return symbol with higher chance
  return heads > tails ? 'h' : 't';

}
