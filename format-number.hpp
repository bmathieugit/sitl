#include <string>
#include <concepts>

#include "meta.hpp"
#include "format-model.hpp"

namespace fmt
{
  template <typename C>
  class stack_array
  {
    C data[20];
    int i = -1;

  public:
    void push(C c) { data[++i] = c; }
    C pop() { return data[i--]; }
    bool empty() { return i == -1; }
  };

  template <
      typename C>
  void fmt(
      buffer<C> &buff,
      is_integer auto t)
  {
    bool neg = t < 0;
    auto _abs = [](int i)
    { return i < 0 ? -i : i; };

    stack_array<C> tbuff;

    while (t != 0)
    {
      tbuff.push("0123456789"[_abs(t % 10)]);
      t /= 10;
    }

    if (neg)
      tbuff.push('-');

    while (not tbuff.empty())
      buff.push_back(tbuff.pop());
  }

}