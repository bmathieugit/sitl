#ifndef __sitl_globalanalyser_hpp__
#define __sitl_globalanalyser_hpp__

#include <lib/vector.hpp>
#include <model/token.hpp>
#include <model/tokentype.hpp>

namespace sitl
{
  template <typename... A>
  struct GlobalAnalyser
  {
    constexpr bool operator()(
        VectorCRange<Token> tokens) const noexcept
    {
      bool res = true;

      do
      {
        VectorCRange<Token> line = tokens.go_after_if(
            [](const Token &t)
            { return t.type == TokenType::EOL; });

        res = res && (... || A()(line));
      } while (!tokens.empty() && res);

      return res;
    }
  };
}

#endif