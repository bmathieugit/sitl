#ifndef __clon_format_hpp__
#define __clon_format_hpp__

#include <string_view>
#include <string>
#include <vector>
#include <array>

#include "format-core.hpp"

namespace fmt::impl
{
  template <typename C>
  std::basic_string_view<C>
  bfmt(
      std::basic_string<C> &buff,
      std::basic_string_view<C> fmt)
  {
    auto htag = fmt.find('#');
    auto part = fmt.substr(0, htag);

    buff.append(part);

    return fmt.substr(
        htag != fmt.size()
            ? htag + 1
            : htag);
  }

  template <typename C,
            typename... args_t>
  constexpr auto format(
      std::basic_string_view<C> fm,
      const args_t &...args)
  {
    std::basic_string<C> buff;

    ((fm = bfmt(buff, fm),
      formatter<args_t>{}(buff, args)),
     ...);
    bfmt(buff, fm);

    return buff;
  };
}

namespace fmt
{
  template <typename... args_t>
  constexpr auto
  format(std::basic_string_view<char> fmt,
         const args_t &...args)
  {
    return impl::format(fmt, args...);
  }

  template <typename... args_t>
  constexpr auto
  format(std::basic_string_view<wchar_t> fmt,
         const args_t &...args)
  {
    return impl::format(fmt, args...);
  }
}

#include "format-string.hpp"
#include "format-integer.hpp"
#include "format-bool.hpp"
#include "format-ansi.hpp"

#endif
