#include <iostream>
#include "sudoku.h"

int main(int, char **)
{
  Sudoku sudoku;
  sudoku.fill(time(NULL));
  std::cout << sudoku.print();

  return 0;
}