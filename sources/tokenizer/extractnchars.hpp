#ifndef __sitl_extractnchars_hpp__
#define __sitl_extractnchars_hpp__

#include <lib/string.hpp>

namespace sitl
{
  template <Size n>
  struct ExtractNChars
  {
    constexpr auto operator()(
        StringCRange src) const noexcept
    {
      return src.sub(0, n);
    }
  };
}

#endif