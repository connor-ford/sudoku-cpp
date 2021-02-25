#pragma once
#include <string.h>
#include <list>

class Sudoku
{
private:
  char board[9][9];
  std::list<char> solves[9][9];
  void check(int x, int y, char init); // Checks the specified square for valid solves, starting with the provided character

public:
  void fill(int seed); // Fills board
  std::string print(); // Prints board
};