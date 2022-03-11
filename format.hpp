#ifndef __clon_format_hpp__
#define __clon_format_hpp__

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

  template <
      typename arg_t,
      typename... args_t>
  void format(
      std::string &buff,
      std::string_view fm,
      const arg_t &arg,
      const args_t &...args)
  {
    fm = bfmt(buff, fm);
    formatter<arg_t>{}(buff, arg);

    if constexpr (sizeof...(args_t) > 0)
      format(buff, fm, args...);
    else
      buff.append(fm);
  }

  template <
      typename... args_t>
  std::string format(
      std::string_view fm,
      const args_t &...args)
  {
    std::string buff;

    if constexpr (sizeof...(args_t) > 0)
      format(buff, fm, args...);
    else
      buff.append(fm);

    return buff;
  };
}

#include "format-integer.hpp"
#include "format-bool.hpp"
#include "format-ansi.hpp"
#include "format-vector.hpp"
#include "format-map.hpp"

#endif
