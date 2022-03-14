#ifndef __sitl_fmt_format_hpp__
#define __sitl_fmt_format_hpp__

#include <string_view>
#include <string>
#include <vector>
#include <array>

#include "format-core.hpp"
#include "format-string.hpp"

namespace fmt
{
  std::string_view
  bfmt(std::string &buff,
       std::string_view fmt);

  template <typename arg_t>
  std::string_view format(
      std::string &buff,
      std::string_view fm,
      const arg_t &arg);

  template <typename... args_t>
  std::string format(
      std::string_view fm,
      const args_t &...args);
}

template <typename arg_t>
std::string_view fmt::format(
    std::string &buff,
    std::string_view fm,
    const arg_t &arg)
{
  fm = fmt::bfmt(buff, fm);
  fmt::formatter<arg_t>{}.format(buff, arg);
  return fm;
}

template <typename... args_t>
std::string fmt::format(
    std::string_view fm,
    const args_t &...args)
{
  std::string buff;

  ((fm = fmt::format(buff, fm, args)), ...);
  buff.append(fm);

  return buff;
};

#include "format-integer.hpp"
#include "format-bool.hpp"
#include "format-ansi.hpp"
#include "format-vector.hpp"
#include "format-map.hpp"

#endif
