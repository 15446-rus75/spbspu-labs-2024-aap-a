#include "find_osed.hpp"

int brevnov::find_osed(const int * t, size_t m, size_t n)
{
  int answer = 0;
  for (size_t i = 0; i < m; i++)
  {
    size_t min_member = brevnov::find_index_min(t, n, i);
    if (i == (brevnov::find_index_max(t, m, n, min_member)))
    {
      answer++;
    }
  }
  return answer;
}

size_t brevnov::find_index_min(const int * t, size_t n, size_t i)
{
  int min_member = t[i * n];
  size_t min_index = 0;
  for (size_t j = 1; j < n; ++j)
  {
    if (min_member > t[i * n + j])
    {
      min_member = t[i * n + j];
      min_index = j;
    }
  }
  return min_index;
}

size_t brevnov::find_index_max(const int * t, size_t m, size_t n, int min_member)
{
  int max_member = t[min_mem];
  size_t max_index = 0;
  for (size_t j = 1; j < m; ++j)
  {
    if (max_member < t[j * n + min_member])
    {
      max_member = t[j * n + min_member];
      max_index = j;
    }
  }
  return max_index;
}
