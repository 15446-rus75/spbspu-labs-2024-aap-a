#include "input.hpp"
#include "shape.hpp"
#include "count_point.hpp"
#include <iostream>
#include <string>
#include <limits>
namespace karnauhova
{
  void eat_trash(std::istream & in);
}
void karnauhova::eat_trash(std::istream & in)
{
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool karnauhova::input(std::istream &in, double* t, std::string* names, size_t i)
{
  std::string name;
  double x1 = 0, x2 = 0;
  char n = 0;
//  for (size_t i = 0; in >> name; i++)
  //{
    in >> name;
    if (!(in >> name) || name.empty())
    {
      std::cerr << "EOF\n";
      return false;
      std::cerr << "EOF\n";
    }
    if (!karnauhova::count_point(name))
    {
      karnauhova::eat_trash(in);
      std::cerr << "Name\n";
      return false;
      std::cerr << "Name\n";
    }
    names[i] = name;
    for (int j = 0; j < (karnauhova::count_point(name)*2); j+=2)
    {
      if (!(in >> x1 >> x2))
      {
        eat_trash(in);
        std::cerr << "Error reading coordinates at index " << j << "\n";
        return false;
      }
      t[j+i] = x1;
      t[j+i+1] = x2;
    }
    in >> n;
    if (n != '\n' && !in.eof())
    {
      karnauhova::eat_trash(in);
      std::cerr << "n\n";
      return false;
    }
  //}
  return true;
}

bool input_retangle(std::istream & in, double* x_y, size_t j)
{
  double x = 0;
  for (size_t i = 0; i < 4; i++)
  {
    if (in.peek() != '\n' && in.peek() != EOF)
    {
      if (!(in >> x))
      {
        return false;
      }
      x_y[j + i] = x;
    }
    else
    {
      return false;
    }
  }
  if (in.peek() != '\n' && in.peek() != EOF)
  {
    eat_trash(in);
    return false;
  }
  return true;
}

bool input_triangle(std::istream & in, double* x_y, size_t j)
{
  double x = 0;
  for (size_t i = 0; i < 6; i++)
  {
    if (in.peek() != '\n' && in.peek() != EOF)
    {
      if (!(in >> x))
      {
        return false;
      }
      x_y[j + i] = x;
    }
    else
    {
      return false;
    }
  }
  if (in.peek() != '\n' && in.peek() != EOF)
  {
    eat_trash(in);
    return false;
  }
  return true;
}

