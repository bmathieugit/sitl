#include <array>
#include <string>
#include <concepts>

#include "meta.hpp"

template <is_boolean boolean>
constexpr unsigned length_of(boolean b)
{
  return b ? 4 : 5;
}

template <
    typename char_t,
    is_boolean boolean>
constexpr void format_of(
    std::basic_string<char_t> &buff,
    boolean b)
{
  buff.append(b ? "true" : "false");
}