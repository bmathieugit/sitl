#ifndef __sitl_lineanalyser_hpp__
#define __sitl_lineanalyser_hpp__

#include <lib/vector.hpp>

namespace sitl
{
  template <typename... A>
  struct Lineyser
  {
    static constexpr Size S = (0 + ... + A::S);
    constexpr bool operator()(
      VectorCRange<Token> tline) const noexcept
    {
      bool tmp;
      Position pos = 0;
      return ((tline.size() >= S) && ... && ((tmp = A()(tline, pos)), pos += A::S, tmp));
    }
  };
}

#endif