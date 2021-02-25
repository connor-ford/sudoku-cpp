# sudoku-cpp

A C++ program that generates and solves Sudoku puzzles.

## Solving puzzles

The program recursively finds every possible solution to a board by iterating over every valid move in a branch. When it hits a dead end or the board is solved, it backtracks to the next branch and tries again. The process is complete when there are no other branches available.

## Generating puzzles

The board is randomly filled in recursively by backtracking whenever it hits a dead end. Once the board is filled, it starts removing numbers to create a puzzle. Each time a number is removed, a solve check is run to make sure that there is still only one possible solution to the puzzle.

## Contribution

If you have any comments or suggestions for this program, feel free to make a pull request or email me at connor.ford2022@gmail.com.
