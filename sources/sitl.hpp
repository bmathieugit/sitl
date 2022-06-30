#ifndef __sitl_tokens_hpp__
#define __sitl_tokens_hpp__

#include <lib/string.hpp>
#include <lib/vector.hpp>
#include <model/token.hpp>
#include <model/tokentype.hpp>
#include <tokenizer/tokenizer.hpp>
#include <tokenizer/globaltokenizer.hpp>
#include <tokenizer/canbenchars.hpp>
#include <tokenizer/extractinside.hpp>
#include <tokenizer/extractnchars.hpp>
#include <tokenizer/tokenizers.hpp>
#include <tokenizer/proceduraltokenizer.hpp>
#include <tokenizer/expressiontokenizer.hpp>
#include <model/line.hpp>
#include <model/linetype.hpp>
#include <lineyser/onelineyser.hpp>
#include <lineyser/nsomelineyser.hpp>
#include <lineyser/sequencelineyser.hpp>
#include <lineyser/globallineyser.hpp>
#include <lineyser/lineyser.hpp>

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

  using SitlLineyser =
      GlobalLineyser<
          StructLineyser,
          BeginLineyser,
          ParamLineyser,
          EndLineyser,
          LetLineyser>;

  struct ExpressionLineyser
  {
  public:
    constexpr bool operator()(VectorCRange<Token> tokens) const noexcept
    {
      return analyseExpression(tokens) != 0;
    }

  private:
    using Distance = Size;
    using TT = TokenType;

    constexpr bool analyseNumber(VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::NUMBER;
    }

    constexpr bool analyseString(VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::STRING;
    }

    constexpr bool analyseLabel(VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::LABEL;
    }

    constexpr bool analyseOpenExpression(VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::LPAR;
    }

    constexpr bool analyseCloseExpression(VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::RPAR;
    }

    constexpr Distance analyseExpression(VectorCRange<Token> tokens) const noexcept
    {
      Distance d = 0;

      if (analyseOpenExpression(tokens))
      {
        ++d;
        tokens = tokens.sub(1);

        if (analyseLabel(tokens))
        {
          ++d;
          tokens = tokens.sub(1);

          while (!tokens.empty() && analyseCloseExpression(tokens))
          {
            if (analyseString(tokens) ||
                analyseLabel(tokens) ||
                analyseNumber(tokens))
            {
              ++d;
              tokens.sub(1);
            }
            else if (Distance subd = analyseExpression(tokens); subd != 0)
            {
              d += subd;
              tokens.sub(subd);
            }
          }

          if (analyseCloseExpression(tokens))
          {
            ++d;
          }
        }
        else
        {
          d = 0;
        }
      }
      else if (analyseLabel(tokens) ||
               analyseString(tokens) ||
               analyseNumber(tokens))
        ++d;

      return d;
    }
  };

}

#endif