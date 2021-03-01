#pragma once
#include <list>
#include <vector>

class Sudoku
{
private:
  std::vector<std::pair<int, int>> blanks;
  char board[9][9];
  std::list<char> solves[9][9];
  std::string validInput = "123456789.";
  void check(int, int, char); // Checks the specified square for valid solves, starting with the provided character
  bool createHole(int);       // Creates a specified amount of holes in the board
  void fill(int);             // Fills board
public:
  Sudoku();                               // Init
  void clear();                           // Clears puzzle
  void create(int);                       // Creates puzzle
  void load(std::string);                 // Loads puzzle
  int numOfSols();                        // Finds number of solutions to loaded puzzle
  std::string print(bool);                // Prints puzzle
  bool solve();                           // Solves loaded puzzle
  bool validatePuzzleString(std::string); // Validates string as a puzzle
};