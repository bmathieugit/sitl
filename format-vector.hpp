#ifndef __fmt_format_vector_hpp__
#define __fmt_format_vector_hpp__

#include <string>
#include <vector>

#include "meta.hpp"
#include "format-core.hpp"
#include "format-string.hpp"

template <typename T>
struct fmt::formatter<std::vector<T>>
    : fmt::formatter<T>,
      fmt::formatter<std::string_view>,
      fmt::formatter<char>
{
  void format(
      std::string &buff,
      const std::vector<T> &v) const
  {
    fmt::formatter<char>::format(buff, '{');

    for (size_t i = 0; i < v.size(); ++i)
    {
      fmt::formatter<T>::format(buff, v[i]);

      if (i < v.size() - 1)
        fmt::formatter<std::string_view>::format(buff, ", ");
    }

    fmt::formatter<char>::format(buff, '}');
  }
};

#endif