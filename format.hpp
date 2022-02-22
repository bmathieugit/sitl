#ifndef __clon_format_hpp__
#define __clon_format_hpp__

#include <string_view>
#include <string>
#include <vector>
#include <array>

#include "format-number.hpp"
#include "format-bool.hpp"
#include "format-string.hpp"

namespace lib
{
  template <typename C>
  using basic_format = std::basic_string_view<C>;

  template<typename C>
  using basic_view = std::basic_string_view<C>;
}

namespace lib::impl
{
  template <typename C>
  basic_format<C>
  format_of_fmt(
      std::basic_string<C> &buff,
      basic_format<C> fmt)
  {
    auto htag = fmt.find('#');
    auto part = fmt.substr(0, htag);

    buff.append(part);

    return fmt.substr(
        htag != fmt.size()
            ? htag + 1
            : htag);
  }

  template <
      typename C,
      typename... args_t>
  std::basic_string<C>
  format(
      basic_format<C> fmt,
      const args_t &...args)
  {

    std::basic_string<C> buff;

    buff.reserve((length_of(args) + ... + fmt.size()));

    ((fmt = format_of_fmt(buff, fmt),
      format_of(buff, args)),
     ...,
     format_of(buff, fmt));

    return buff;
  }
}

namespace lib
{
  template <typename... args_t>
  std::basic_string<char>
  format(basic_format<char> fmt,
         const args_t &...args)
  {
    return impl::format(fmt, args...);
  }

  template <typename... args_t>
  std::basic_string<wchar_t>
  format(basic_format<wchar_t> fmt,
         const args_t &...args)
  {
    return impl::format(fmt, args...);
  }
}

#endif
