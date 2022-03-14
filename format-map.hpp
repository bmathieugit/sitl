#ifndef __fmt_format_map_hpp__
#define __fmt_format_map_hpp__

#include <string>
#include <map>

#include "meta.hpp"
#include "format-core.hpp"
#include "format-string.hpp"

template <typename K, typename V>
struct fmt::formatter<std::map<K, V>>
    : fmt::formatter<K>,
      fmt::formatter<V>,
      fmt::formatter<char>,
      fmt::formatter<std::string_view>
{
  void format(
      std::string &buff,
      const std::map<K, V> &m) const
  {
    fmt::formatter<char>::format(buff, '{');

    for (const auto &p : m)
    {
      fmt::formatter<K>::format(buff, p.first);
      fmt::formatter<std::string_view>::format(buff, ": ");
      fmt::formatter<V>::format(buff, p.second);
      fmt::formatter<char>::format(buff, ';');
    }

    fmt::formatter<char>::format(buff, '}');
  }
};

#endif