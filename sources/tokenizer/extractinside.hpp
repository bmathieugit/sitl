#ifndef __sitl_extractinside_hpp__
#define __sitl_extractinside_hpp__

#include <lib/string.hpp>

namespace sitl
{
  template <char b, char e>
  struct ExtractInside
  {
    constexpr auto operator()(
      StringCRange src) const noexcept
    {
      return src.inside(b, e);
    }
  };
}

#endif