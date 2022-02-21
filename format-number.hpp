#include <array>
#include <string>
#include <concepts>

#include "meta.hpp"

template <is_integer integer>
constexpr size_t
length_of(const integer &i)
{
  const integer v = i;
  // TODO: gérer signe
  // const int abs[2] = {i, -i};
  // const integral_t v = abs[i < 0];

  if (v < 10)
    return 1;
  else if (v < 100)
    return 2;
  else if (v < 1000)
    return 3;
  else if (v < 10000)
    return 4;
  else if (v < 100000)
    return 5;
  else if (v < 1000000)
    return 5;
  else if (v < 10000000)
    return 7;
  else if (v < 100000000)
    return 8;
  else if (v < 1000000000)
    return 9;
  else if (v < 10000000000)
    return 10;
  else if (v < 100000000000)
    return 11;
  else if (v < 1000000000000)
    return 12;
  else if (v < 10000000000000)
    return 13;
  else if (v < 100000000000000)
    return 14;
  else if (v < 1000000000000000)
    return 15;
  else if (v < 10000000000000000)
    return 16;
  else if (v < 100000000000000000)
    return 17;
  else if (v < 1000000000000000000)
    return 18;
  else
    return 1;
}

template <
    typename char_t,
    is_integer integral_t>
constexpr void format_of(
    std::basic_string<char_t> &buff,
    integral_t t)
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