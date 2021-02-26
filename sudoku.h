#pragma once
#include <list>
#include <vector>

class Sudoku
{
private:
  char board[9][9];
  std::list<char> solves[9][9];
  std::vector<std::pair<int, int>> blanks;
  std::string validInput = "123456789.";
  void check(int, int, char); // Checks the specified square for valid solves, starting with the provided character
public:
  Sudoku();                         // Init
  void fill(int);                   // Fills board
  void clear();                     // Clears puzzle
  void load(std::string);           // Loads puzzle
  std::string print();              // Prints puzzle
  bool solve();                     // Solves loaded puzzle
  bool validatePuzzle(std::string); // Validates string as a puzzle
};