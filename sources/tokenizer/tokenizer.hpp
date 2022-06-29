#ifndef __sitl_tokenizer_hpp__
#define __sitl_tokenizer_hpp__

#include <lib/string.hpp>
#include <model/tokentype.hpp>
#include <model/token.hpp>

namespace sitl
{
  template <TokenType type,
            typename CANBE,
            typename EXTRACT>
  struct Tokenizer
  {
    constexpr bool canbe(
        StringCRange s) const noexcept
    {
      return CANBE()(s);
    }

    constexpr Token extract(
        StringCRange src) const noexcept
    {
      auto value = EXTRACT()(src);
      return value.empty()
                 ? Token{TokenType::ERROR, src.sub(0, 1)}
                 : Token{type, value};
    }
  };
}

#endif