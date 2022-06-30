#ifndef __sitl_lineanalyser_hpp__
#define __sitl_lineanalyser_hpp__

#include <lib/vector.hpp>
#include <model/line.hpp>
#include <model/linetype.hpp>

namespace sitl
{
  template <LineType type, TokenType... ttypes>
  struct Lineyser
  {
    static constexpr Size S = (0 + ... + A::S);
    constexpr Line operator()(
      VectorCRange<Token> tline) const noexcept
    {
      Line line;
      line.tokens = Vector<Token>(S);
      line.tokens.lpush()
      Position pos = 0;
      return ((tline.size() >= S) && ... && ((tmp = A()(tline, pos)), pos += A::S, tmp));
    }
  };
}

#endif