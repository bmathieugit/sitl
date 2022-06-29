#ifndef __sitl_global_tokenizer_hpp__
#define __sitl_global_tokenizer_hpp__

#include <lib/string.hpp>
#include <lib/vector.hpp>
#include <model/tokentype.hpp>
#include <model/token.hpp>

namespace sitl
{
  template <typename... T>
  class GlobalTokenizer
  {
    using TT = TokenType;

    template <typename T0, typename... TN>
    constexpr Token tokenize(StringCRange line) const noexcept
    {
      if (T0().canbe(line))
        return T0().extract(line);
      else if constexpr (sizeof...(TN) > 0)
        return tokenize<TN...>(line);
      else
        return Token{TT::ERROR, line.sub(0, 1)};
    }

  public:
    constexpr Vector<Token> operator()(StringCRange src) const noexcept
    {
      Vector<Token> tokens;

      do
      {
        StringCRange line = src.go_after('\n');
        Token tk;

        while (!line.empty())
        {
          tk = tokenize<T...>(line);
          line = line.sub(tk.value.size());

          if (tk.type == TT::ERROR)
            break;
          else if (tk.type != TT::BLANK)
            tokens.push(move(tk));
        }

        if (tk.type == TT::ERROR)
          break;

        tokens.push(Token{TT::EOL, sr("\\n")});

      } while (!src.empty());

      return tokens;
    }
  };

}

#endif