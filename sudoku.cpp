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

void Sudoku::create(int clues)
{
  fill(time(NULL));
  int inc, x, y, sols;
  char c;
  for (int i = 0; i < 81 - clues; i++)
  {
    inc = rand() % 81;
    for (int j = 0; j < 81; j++)
    {
      inc = (inc == 80 ? 0 : inc + 1);
      x = inc % 9;
      y = inc / 9;

      if (board[y][x] == 0)
      {
        continue;
      }
      c = board[y][x];
      board[y][x] = 0;
      sols = numOfSols();
      if (sols != 1)
      {
        board[y][x] = c;
      }
      break;
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
      check(x, y, (rand() % 8) + '1');
      // If there is a solution, use it
      if (solves[y][x].size() > 0)
      {
        board[y][x] = solves[y][x].front();
      }
      else
      {
        while (1)
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

int Sudoku::numOfSols()
{
  // Get blank squares in puzzle
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      solves[y][x].clear();
      if (board[y][x] == 0)
      {
        blanks.push_back(std::make_pair(x, y));
      }
    }
  }
  int x, y, sols = 0;
  for (int i = 0; i < blanks.size(); i++)
  {
    x = blanks.at(i).first;
    y = blanks.at(i).second;
    // Get possible solutions for square
    check(x, y, '1');
    // If there is an available solution, use it
    if (solves[y][x].size() > 0)
    {
      board[y][x] = solves[y][x].front();
    }
    else
    {
      board[y][x] = 0;
      while (1)
      {
        board[y][x] = 0;
        // Move to previous blank
        i--;
        // If no more possibilities
        if (i < 0)
        {
          return sols;
        }
        x = blanks.at(i).first;
        y = blanks.at(i).second;
        // If no more branches to try, delete possibilities
        if (solves[y][x].size() < 2)
        {
          board[y][x] = 0;
          solves[y][x].clear();
        }
        else
        {
          break;
        }
      }
      // Delete current branch and try the next one
      solves[y][x].pop_front();
      board[y][x] = solves[y][x].front();
    }
    if (i + 1 == blanks.size())
    {
      solves[y][x].clear();
      board[y][x] = 0;
      while (1)
      {
        // Move to previous blank
        i--;
        // If no more possibilities
        if (i < 0)
        {
          return sols;
        }
        x = blanks.at(i).first;
        y = blanks.at(i).second;
        // If no more branches to try, delete possibilities
        if (solves[y][x].size() < 2)
        {
          board[y][x] = 0;
          solves[y][x].clear();
        }
        else
        {
          break;
        }
      }
      // Delete current branch and try the next one
      solves[y][x].pop_front();
      board[y][x] = solves[y][x].front();
    }
  }
  return sols;
}

std::string Sudoku::print(bool formatted)
{
  std::string s;
  if (formatted)
  {
    for (int y = 0; y < 9; y++)
    {
      for (int x = 0; x < 9; x++)
      {
        s += (board[y][x] == 0 ? '.' : board[y][x]);
        s += (x % 3 == 2 && x != 8 ? "|" : "");
      }
      s += (y % 3 == 2 && y != 8 ? "\n---+---+---\n" : "\n");
    }
  }
  else
  {
    for (int y = 0; y < 9; y++)
    {
      for (int x = 0; x < 9; x++)
      {
        s += (board[y][x] == 0 ? '.' : board[y][x]);
      }
    }
  }
  return s;
}

bool Sudoku::solve()
{
  // Get blank squares in puzzle
  for (int y = 0; y < 9; y++)
  {
    for (int x = 0; x < 9; x++)
    {
      solves[y][x].clear();
      if (board[y][x] == 0)
      {
        blanks.push_back(std::make_pair(x, y));
      }
    }
  }
  int y, x;
  for (int i = 0; i < blanks.size(); i++)
  {
    x = blanks.at(i).first;
    y = blanks.at(i).second;
    // Get possible solutions for square
    check(x, y, '1');
    // If there is an available solution, use it
    if (solves[y][x].size() > 0)
    {
      board[y][x] = solves[y][x].front();
    }
    else
    {
      while (1)
      {
        // Move to previous blank
        i--;
        // If no more possibilities
        if (i < 0)
        {
          return false;
        }
        x = blanks.at(i).first;
        y = blanks.at(i).second;
        // If no more branches to try, delete possibilities
        if (solves[y][x].size() < 2)
        {
          board[y][x] = 0;
          solves[y][x].clear();
        }
        else
        {
          break;
        }
      }
      // Delete current branch and try the next one
      solves[y][x].pop_front();
      board[y][x] = solves[y][x].front();
    }
  }
  return true;
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