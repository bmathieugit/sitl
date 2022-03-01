#include <array>
#include <string>
#include <concepts>

#include "meta.hpp"
#include "format-model.hpp"

namespace fmt
{
  template <
      typename C>
  void fmt(
      buffer<C> &buff,
      is_integer auto t)
  {
    if (t == 0)
      buff.push_back('0');

    std::array<char, 50> tbuff;
    auto e = tbuff.end();
    auto i = e - 1;

    while (t != 0)
    {
      *i = "0123456789"[t % 10];
      --i;
      t /= 10;
    }

    if (i != e)
      ++i;

    for (; i != e; ++i)
      buff.push_back(*i);
  }
}