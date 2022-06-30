#ifndef __sitl_lineysers_hpp__
#define __sitl_lineysers_hpp__

#include <lineyser/lineyser.hpp>
#include <lineyser/onelineyser.hpp>
#include <lineyser/nsomelineyser.hpp>
#include <lineyser/sequencelineyser.hpp>
#include <model/tokentype.hpp>

namespace sitl
{
  using BeginLineyser =
      Lineyser<One<TokenType::BEGIN>>;

  using StructLineyser =
      Lineyser<Sequence<
          TokenType::STRUCT,
          TokenType::LABEL>>;

  using ParamLineyser =
      Lineyser<
          One<TokenType::PARAM>,
          One<TokenType::LABEL>,
          One<TokenType::LABEL>>;

  using EndLineyser =
      Lineyser<One<TokenType::END>>;

  using LetLineyser =
      Lineyser<
          Sequence<TokenType::LET,
                   TokenType::LABEL,
                   TokenType::LABEL,
                   TokenType::EXPR>>;

  using IfLineyser =
      Lineyser<One<TokenType::IF>>;

}

#endif 