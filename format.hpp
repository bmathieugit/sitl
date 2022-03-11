#ifndef __clon_format_hpp__
#define __clon_format_hpp__

#include <string_view>
#include <string>
#include <vector>
#include <array>

#include "format-core.hpp"

namespace fmt
{
  template <typename... args_t>
  constexpr auto format(
      std::string_view fm,
      const args_t &...args)
  {
    auto bfmt = [](std::string &buff,
                   std::string_view fmt)
    {
      auto htag = fmt.find('#');
      auto part = fmt.substr(0, htag);

      buff.append(part);

      return fmt.substr(htag != fmt.size() ? htag + 1 : htag);
    };

    std::string buff;

    ((fm = bfmt(buff, fm),
      format_to(buff, args)),
     ...);
    bfmt(buff, fm);

    return buff;
  };
}

#include "format-string.hpp"
#include "format-integer.hpp"
#include "format-bool.hpp"
#include "format-ansi.hpp"
#include "format-vector.hpp"
#include "format-map.hpp"

#endif
