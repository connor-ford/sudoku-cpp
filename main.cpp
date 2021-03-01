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
  while (1)
  {
    std::cout << menu;
    std::cin >> option;
    std::cout << '\n';
    // Validates input as integer
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input.\n\n";
      continue;
    }
    // Runs corresponding option
    switch (option)
    {
    case 1: // Generate new
      while (1)
      {
        std::cout << "How many clues? (17-81): ";
        std::cin >> option;
        std::cout << '\n';
        // Validates input as integer
        if (std::cin.fail())
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input.\n\n";
          continue;
        }
        // Validates integer is within range
        if (option < 17 || option > 81)
        {
          std::cin.clear();
          std::cout << "Number of clues must be between 17-81.\n\n";
          continue;
        }
        break;
      }
      sudoku.create(option);
      std::cout << '\n'
                << sudoku.print(true) << '\n';
      std::cout << sudoku.print(false) << "\n\n";
      break;
    case 2: // Import from terminal
      while (1)
      {
        std::cout << "Enter puzzle string: ";
        std::cin >> puzzle;
        std::cout << '\n';
        if (sudoku.validatePuzzleString(puzzle))
        {
          sudoku.load(puzzle);
          std::cout << "Puzzle:\n\n"
                    << sudoku.print(true) << '\n';
          std::cout << "Number of solves: " << sudoku.numOfSols() << "\n\n";
          if (sudoku.solve())
          {
            std::cout << "Solved Puzzle:\n\n"
                      << sudoku.print(true) << '\n';
          }
          else
          {
            std::cout << "Could not solve the Puzzle.\n\n";
          }
          break;
        }
        else
        {
          std::cout << "Invalid puzzle string provided.\n\n";
        }
      }
      break;
    case 0:
      return 0;
    default:
      std::cout << "Invalid option provided.\n\n";
      continue;
    }
    return 0;
  }
}