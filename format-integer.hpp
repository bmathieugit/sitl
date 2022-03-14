#ifndef __sitl_fmt_format_integer_hpp__
#define __sitl_fmt_format_integer_hpp__

#include <string>
#include <concepts>

#include "meta.hpp"
#include "format-core.hpp"
#include "format-string.hpp"

template <is_integer T>
struct fmt::formatter<T>
    : fmt::formatter<char>
{
  class stack_array
  {
    char data[40];
    int i = -1;

  public:
    void push(char c) { data[++i] = c; }
    char pop() { return data[i--]; }
    bool empty() { return i == -1; }
  };

  void format(std::string &buff, T t) const
  {
    bool neg = t < 0;
    auto _abs = [](int i)
    { return i < 0 ? -i : i; };

    stack_array tbuff;

    if (t == 0)
      formatter<char>::format(buff, '0');
    else
      while (t != 0)
      {
        tbuff.push("0123456789"[_abs(t % 10)]);
        t /= 10;
      }

    if (neg)
      tbuff.push('-');

    while (not tbuff.empty())
      formatter<char>::format(buff, tbuff.pop());
  }
};

#endif