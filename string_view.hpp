#ifndef __lib_string_view_hpp__
#define __lib_string_view_hpp__

#include "span.hpp"
#include "meta.hpp"

namespace lib
{
  struct cstring_limit
  {
    constexpr size_t 
    sized(size_t n)
    {
      return n - 1;
    }
  };

  template <character char_t>
  using basic_string_view = span<const char_t, cstring_limit>;

  using string_view = basic_string_view<char>;
  using wstring_view = basic_string_view<wchar_t>;
}

#endif