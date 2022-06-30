#ifndef __sitl_oneanalyser_hpp__
#define __sitl_oneanalyser_hpp__

#include <lib/vector.hpp>

namespace sitl
{
  template <TokenType type>
  struct OneLineyser
  {
    static constexpr Size S = 1;

    constexpr bool operator()(VectorCRange<Token> tline, Position pos) const noexcept
    {
      return tline[pos].type == type;
    }
  };

  template<TokenType type>
  using One = OneLineyser<type>;
}

#endif