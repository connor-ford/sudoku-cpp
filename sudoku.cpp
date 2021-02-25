#include <cstring>
#include <iostream>
#include "sudoku.h"

Sudoku::Sudoku()
{
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      board[y][x] = 0;
      solves[y][x].clear();
    }
  }
}

void Sudoku::check(int x, int y, char init)
{
  char c = init;
  bool valid;
  for (int i = 0; i < 9; i++)
  {
    valid = true;
    for (int j = 0; j < 9; j++)
    {
      if (board[y][j] == c                                          // Horizontal
          || board[j][x] == c                                       // Vertical
          || board[3 * (y / 3) + j / 3][3 * (x / 3) + (j % 3)] == c // Box
      )
      {
        valid = false;
        break;
      }
    }
    if (valid)
    {
      solves[y][x].push_back(c);
    }
    // Iterate character
    c = (c == '9' ? '1' : c + 1);
  }
}

void Sudoku::clear()
{
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      board[y][x] = 0;
      solves[y][x].clear();
    }
  }
}

void Sudoku::fill(int seed)
{
  srand(seed);
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      // Check each char for compatibility
      this->check(x, y, (rand() % 8) + '1');
      // If there is a solution, use it
      if (solves[y][x].size() > 0)
      {
        board[y][x] = solves[y][x].front();
      }
      else
      {
        while (true)
        {
          // Move to previous square
          x--;
          if (x == -1)
          {
            x = 8;
            y--;
          }
          // If only one solve, clear it
          if (solves[y][x].size() < 2)
          {
            for (int i = 0; i < 9; i++)
            {
              board[y][x] = 0;
              solves[y][x].clear();
            }
          }
          else
          {
            break;
          }
        }
        // Remove previous path and try the next one
        solves[y][x].pop_front();
        board[y][x] = solves[y][x].front();
      }
    }
  }
}

void Sudoku::load(std::string puzzle)
{
  for (int i = 0; i < 81; i++)
  {
    board[i / 9][i % 9] = (puzzle[i] == '.' ? 0 : puzzle[i]);
  }
}

std::string Sudoku::print()
{
  std::string s;
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      s += (board[y][x] == 0 ? '.' : board[y][x]);
      s += (x % 3 == 2 && x != 8 ? "|" : "");
    }
    s += (y % 3 == 2 && y != 8 ? "\n---+---+---\n" : "\n");
  }
  return s;
}

bool Sudoku::validatePuzzle(std::string s)
{
  if (s.length() != 81)
  {
    return false;
  }
  for (char c : s)
  {
    if (validInput.find(c) == std::string::npos)
    {
      return false;
    }
  }
  return true;
}