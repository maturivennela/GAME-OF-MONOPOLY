#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int SIZE_BOARD = 40;
const int MAX_PLAYERS = 4;
const int STARTING_AMOUNT = 1500;
const int TURNS_MAX = 100;
struct Player {
    string name;
    int pos; //POSITION
    int money;
    bool bkrpt; //Bankrupt
};
struct Property {
  string name;
  bool owned;
  int price;
  int rent;
  int owner;
};
Property board[SIZE_BOARD];
Player players[MAX_PLAYERS];
int numPlayers;
void initializeB() {
  for (int i = 0; i < SIZE_BOARD; i++) {
    board[i].name = "Property " + to_string(i + 1);
    board[i].owned = false;
    board[i].price = (rand() % 300) + 100; // Range of price between 100 and 400
    board[i].rent = (rand() % 200) + 50; // range of Rent between 50 and 250
    board[i].owner = -1; // No owner found
  }
}
void initializeP() {
  for (int i = 0; i < numPlayers; i++) {
    players[i].name = "Player " + to_string(i + 1);
    players[i].pos = 0;
    players[i].money = STARTING_AMOUNT;
    players[i].bkrpt = false;
  }
}
int rollDice() {
  int dice1 = (rand() % 6) + 1;
  int dice2 = (rand() % 6) + 1;
  return dice1 + dice2; // two dices rolled together
}
void turntaken(int playerIdx) {
  if (players[playerIdx].bkrpt) return; // Skip if bankrupt
  int rolldice = rollDice();
  cout << players[playerIdx].name << " rolls a " << rolldice << endl;
  players[playerIdx].pos = (players[playerIdx].pos + rolldice) %SIZE_BOARD;
  Property& landedProperty = board[players[playerIdx].pos];
  cout << players[playerIdx].name << " lands on position:" <<
landedProperty.name << endl;
if (landedProperty.owned) {
  if (landedProperty.owner != playerIdx) {
    // Pay rent to the owner
  cout << players[playerIdx].name << " pays $" << landedProperty.rent
  << " rent to " << players[landedProperty.owner].name << endl;
  players[playerIdx].money -= landedProperty.rent;
  players[landedProperty.owner].money += landedProperty.rent;
 }
} else if (players[playerIdx].money >= landedProperty.price) {
cout << players[playerIdx].name << " buys " << landedProperty.name
  << " for $" << landedProperty.price << endl;
players[playerIdx].money -= landedProperty.price;
landedProperty.owned = true;
landedProperty.owner = playerIdx;
} else {
  cout << players[playerIdx].name << " can't afford " <<
landedProperty.name << endl;
}
if (players[playerIdx].money < 0) {
  players[playerIdx].bkrpt = true;
  cout << players[playerIdx].name << " is bankrupt!" << endl;
  }
}
void checkGameOver() {
int activePlayers = 0;
int lastPlayerIdx = -1;
for (int i = 0; i < numPlayers; i++) {
  if (!players[i].bkrpt) {
  activePlayers++;
  lastPlayerIdx = i;
  }
}
if (activePlayers == 1) {
  cout << players[lastPlayerIdx].name << " wins the game!" << endl;
  exit(0); // End the program
  }
}
// Function to play the game
void playGame() {
  for (int turn = 0; turn < TURNS_MAX; turn++) {
    cout << "Turn " << turn + 1 << endl;
    for (int i = 0; i < numPlayers; i++) {
      if (!players[i].bkrpt) {
        turntaken(i);
      }
  }
  checkGameOver();
  }
cout << "Game over! No winner after " << TURNS_MAX << " turns." << endl;
}
int main() {
  srand(time(0));
  cout << "Enter number of players (1-4): ";
  cin >> numPlayers;
  if (numPlayers < 1 || numPlayers > MAX_PLAYERS) {
    cout << "Invalid number of players. Please enter a number between 1 and4." << endl;
  return 0;
}
initializeB();
initializeP();
playGame();
return 0;
}
