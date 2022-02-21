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
  template <typename char_t>
  using basic_format = std::basic_string_view<char_t>;
}

namespace lib::impl
{
  template <typename char_t>
  basic_format<char_t>
  format_of_fmt(
      std::basic_string<char_t> &buff,
      basic_format<char_t> fmt)
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
      typename char_t,
      typename... args_t>
  std::basic_string<char_t>
  format(
      basic_format<char_t> fmt,
      const args_t &...args)
  {

    std::basic_string<char_t> buff;

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
