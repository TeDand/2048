#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iomanip>

void generate_two(std::vector<int>& v);
bool make_move(std::vector<int>& gridNumbers, char move);
int twod_to_oned(int row, int col, int rowlen);
bool proc_num(std::vector<int>& v, int bi, int ei);
bool push_left(std::vector<int>& v);
void print_grid(const std::vector<int> v);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);

int main() {
  std::ifstream infile;
  std::string filename;
  std::vector<int> fileNumbers;
  int number;
  char move;

  std::cout << "Please enter the name of the file you want to read from" << std::endl;
  std::cin >> filename;

  infile.open(filename.c_str());

  if (!infile.is_open()) {
    std::cout << "Sorry, that file does not exist" << std::endl;
    std::cout << "Loading default file..." << std::endl;
    infile.open("defaultconf.txt");
  }

  while (infile >> number) {
    fileNumbers.push_back(number);
  }

  print_grid(fileNumbers);

  //checks wether the user inputs a correct move
  bool validInput = 0;

  //loops unitl there are no possible moves left
  while (!game_over(fileNumbers)) {
    bool movMade = 0;

    //loops until a valid move is made
    while (movMade == 0) {
      validInput = 0;
      std::cout << "Please enter the move you would like to make (w/a/s/d)" << std::endl;
      //loops until the user enters a valid input
      while (!validInput) {
        std::cin >> move;
        if ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd')) {
          std::cout << "That is not a valid input" << std::endl;
        }
        else {
          validInput = 1;
        }
      }
      //checks if the mov actually does anything
      if (!make_move(fileNumbers, move)) {
        std::cout << "That is not a valid move" << std::endl;
      }
      //if the move is made then a random 2 is generated
      else {
        movMade = 1;
        generate_two(fileNumbers);
      }
    }

    //prints the grid after every move
    print_grid(fileNumbers);
  }

  //the game ends when there are no valid moves left and so you exit the while
  std::cout << "Game over!" << std::endl;

  return 0;
}

//generates a 2 in a random empty cell
void generate_two(std::vector<int>& v){
  int randNo;
  bool valid = 0;

  while (valid == 0) {
    randNo = rand() % v.size();
    if (v[randNo] == 0) {
      valid = 1;
      v[randNo] = 2;
    }
  }
}

//makes a move
bool make_move(std::vector<int>& gridNumbers, char move) {
  bool madeMove = 0;

  //moves up
  if (move == 'w') {
    rotate_anti_clock(gridNumbers);
    madeMove = push_left(gridNumbers);
    rotate_anti_clock(gridNumbers);
    rotate_anti_clock(gridNumbers);
    rotate_anti_clock(gridNumbers);
  }
  //moves left
  else if (move == 'a') {
    madeMove = push_left(gridNumbers);
  }
  //moves down
  else if (move == 's') {
    rotate_anti_clock(gridNumbers);
    rotate_anti_clock(gridNumbers);
    rotate_anti_clock(gridNumbers);
    madeMove = push_left(gridNumbers);
    rotate_anti_clock(gridNumbers);
  }
  //moves right
  else if (move == 'd') {
    rotate_anti_clock(gridNumbers);
    rotate_anti_clock(gridNumbers);
    madeMove = push_left(gridNumbers);
    rotate_anti_clock(gridNumbers);
    rotate_anti_clock(gridNumbers);
  }

  //returns if a move was possible or not
  return madeMove;
}

//pushes all the rows left using proc_num
bool push_left(std::vector<int>& v){
  int side = std::sqrt(v.size());
  bool madeMove = 0;

  for (int i = 0; i < side; i++) {
    if (proc_num(v, side * i, (side * i) + side)) {
      madeMove = 1;
    }
  }

  return madeMove;
}

//returns index of a cell from the grid in the vector
int twod_to_oned(int row, int col, int rowlen) {

  return row*rowlen+col;
}

//squashes the vector in the given range
bool proc_num(std::vector<int>& v, int bi, int ei) {
  bool match = 0;

  //compares consecutive numbers
  for (int j = bi; j < ei; j++) {
    //merges if the two numbers are the same
    for (int i = bi; i < ei - 1; i++) {
      if ((v[i] == v[i+1]) && (v[i] != 0)) {
        v[i] = 2 * v[i+1];
        v[i+1] = 0;
        match = 1;
      }
      //swaps if the number on the left if 0
      else if((v[i] == 0) && (v[i+1] != 0)) {
        v[i] = v[i+1];
        v[i+1] = 0;
        match = 1;
      }
    }
  }

  //returns wether a valid move was made
  return match;
}

//prints out an n x n grid
void print_grid(const std::vector<int> v) {
  int side = std::sqrt(v.size());

  std::cout << std::setw(5);
  for(int i = 0; i < side; i++){
      for(int j = 0; j < side; j++){
          std::cout << v[twod_to_oned(i,j,side)] << std::setw(5);
      }
      std::cout << std::endl;
  }
  std::cout << std::endl;
}

//rotates an n x n grid anti-clockwise
void rotate_anti_clock(std::vector<int>& v) {
  std::vector<int> newV;
  int side = std::sqrt(v.size());

  for (int i = side - 1; i >= 0; i--) {
    for (int j = 0; j < side; j++) {
      newV.push_back(v[twod_to_oned(j,i,side)]);
    }
  }

  v = newV;
}

//checks if there are any valid moves on any of the rows
bool game_over(const std::vector<int>& v) {
  int possibleMoves = 0;

  for (int i = 0; i < 4; i++) {
    std::vector<int> newV = v;
    //checks if you can move up
    if ((i == 0) && (make_move(newV, 'w'))) {
      possibleMoves = possibleMoves + 1;
    }
    //checks if you can move left
    else if ((i == 1) && (make_move(newV, 'a'))) {
      possibleMoves = possibleMoves + 1;
    }
    //checks if you can move down
    else if ((i == 2) && (make_move(newV, 's'))) {
      possibleMoves = possibleMoves + 1;
    }
    //checks if you can move right
    else if ((i == 3) && (make_move(newV, 'd'))) {
      possibleMoves = possibleMoves + 1;
    }
  }

  //checks if there are any possible moves and returns true if there aren't
  if (possibleMoves != 0) {
    return 0;
  }
  else {
    return 1;
  }
}
