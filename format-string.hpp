#ifndef __sitl_fmt_format_string_hpp__
#define __sitl_fmt_format_string_hpp__

#include <string_view>
#include <string>

#include "format-core.hpp"
#include "meta.hpp"

template <>
struct fmt::formatter<char>
{
  void format(
      std::string &buff, char c) const
  {
    buff.push_back(c);
  }
};

template <>
struct fmt::formatter<std::string_view>
{
  void format(
      std::string &buff,
      std::string_view s) const
  {
    buff.append(s);
  }
};

template <>
struct fmt::formatter<std::string>
    : fmt::formatter<std::string_view>
{
  void format(
      std::string &buff,
      const std::string &s) const
  {
    fmt::formatter<std::string_view>::format(buff, s);
  }
};

template <size_t n>
struct fmt::formatter<char[n]>
    : fmt::formatter<std::string_view>
{
  void format(
      std::string &buff,
      const char (&s)[n]) const
  {
    fmt::formatter<std::string_view>::format(buff, s);
  }
};

#endif