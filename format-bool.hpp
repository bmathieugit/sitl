#ifndef __sitl_fmt_format_bool_hpp__
#define __sitl_fmt_format_bool_hpp__

#include <array>
#include <string>
#include <concepts>

#include "meta.hpp"
#include "format-core.hpp"
#include "format-string.hpp"

template <>
struct fmt::formatter<bool>
    : fmt::formatter<std::string_view>
{
  void format(
      std::string &buff,
      const bool &b) const
  {
    fmt::formatter<std::string_view>::
        format(buff, (b ? "true" : "false"));
  }
};

#endif