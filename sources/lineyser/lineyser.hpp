#ifndef __sitl_lineanalyser_hpp__
#define __sitl_lineanalyser_hpp__

#include <lib/vector.hpp>
#include <lib/array.hpp>
#include <model/line.hpp>
#include <model/linetype.hpp>

namespace sitl
{
  using DepthModifier = int;

  template <DepthModifier mod,
            LineType type,
            TokenType... ttypes>
  struct Lineyser
  {
    constexpr Line operator()(
        VectorCRange<Token> tline,
        Depth depth) const noexcept
    {
      Line line;

      if (depth + mod >= 0)
        line.depth = depth + mod;
      else
        line.depth = 0;

      if (tline.map([](const Token &t)
                    { return t.type; })
              .starts_with(Array<TT, sizeof...(ttypes)>({ttypes...})))
      {
        line.tokens.append(tline.begin(),
                           tline.begin() + sizeof...(ttypes));
        line.type = type;
      }
      else
        line.type = LT::ERROR;

      return line;
    }
  };
}

#endif
