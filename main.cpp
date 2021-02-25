#include <iostream>
#include <limits>
#include "sudoku.h"

int main(int, char **)
{
  Sudoku sudoku;
  std::string puzzle;
  std::string menu = "\n";
  menu += "[1] Generate new puzzle\n";
  menu += "[2] Import puzzle from terminal\n";
  menu += "[0] Exit\n";
  menu += "Select an option: ";
  int option;
menu:
  std::cout << menu;
  std::cin >> option;
  std::cout << '\n';
  // Validates input as integer
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input.\n\n";
    goto menu;
  }
  // Runs corresponding option
  switch (option)
  {
  case 1: // Generate new
    sudoku.fill(time(NULL));
    std::cout << sudoku.print();
    break;
  case 2: // Import from terminal
  importTerm:
    std::cout << "Enter puzzle string: ";
    std::cin >> puzzle;
    std::cout << '\n';
    if (sudoku.validatePuzzle(puzzle))
    {
      sudoku.load(puzzle);
      std::cout << sudoku.print();
    }
    else
    {
      std::cout << "Invalid puzzle string provided.\n\n";
      goto importTerm;
    }
    break;
  case 0:
    return 0;
  default:
    std::cout << "Invalid option provided.\n\n";
    goto menu;
  }
  return 0;
}