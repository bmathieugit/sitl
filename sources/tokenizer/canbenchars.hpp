#ifndef __sitl_canbenchars_hpp__
#define __sitl_canbenchars_hpp__

#include <lib/string.hpp>
#include <lib/array.hpp>

namespace sitl
{
  template <char c0, char... cn>
  struct CanBeNChars
  {
    constexpr bool operator()(
        StringCRange s) const noexcept
    {
      constexpr auto sz = 1 + sizeof...(cn);
      
      if constexpr (sizeof...(cn) > 0)
        return s.starts_with(Array<char, sz>{{c0, cn...}});
      else
        return s[0] == c0;
    }
  };
}

#endif