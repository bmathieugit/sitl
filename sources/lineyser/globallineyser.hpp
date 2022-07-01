#ifndef __sitl_globalanalyser_hpp__
#define __sitl_globalanalyser_hpp__

#include <lib/vector.hpp>
#include <model/token.hpp>
#include <model/tokentype.hpp>

namespace sitl
{
  template <typename... L>
  struct GlobalLineyser
  {
    constexpr Vector<Line> operator()(
        VectorCRange<Token> tokens) const noexcept
    {
      Vector<Line> lines;
      Depth depth = 0;

      do
      {
        VectorCRange<Token> tline = tokens.go_after_if(
            [](const Token &t)
            { return t.type == TokenType::EOL; });

        lines.push(lineyse<L...>(tline, depth));
        depth = lines.back().depth;
      } while (!tokens.empty() &&
               lines.back().type != LT::ERROR);

      return lines;
    }

  private:
    template <typename L0, typename... LN>
    Line lineyse(VectorCRange<Token> tline, Depth depth) const noexcept
    {
      Line l = L0()(tline, depth);

      if (l.type != LT::ERROR)
        return l;
      else if constexpr (sizeof...(LN) > 0)
        return lineyse<LN...>(tline, depth);
      else
        return Line{Depth(0), LT::ERROR};
    }
  };
}

#endif