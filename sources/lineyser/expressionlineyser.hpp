#ifndef __sitl_expression_lineyser_hpp__
#define __sitl_expression_lineyser_hpp__

#include <model/token.hpp>
#include <model/tokentype.hpp>
#include <lib/vector.hpp>

namespace sitl
{
  struct ExpressionLineyser
  {
  public:
    constexpr bool operator()(
        VectorCRange<Token> tokens) const noexcept
    {
      return analyseExpression(tokens) != 0;
    }

  private:
    using Distance = Size;
    using TT = TokenType;

    constexpr bool analyseNumber(
        VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::NUMBER;
    }

    constexpr bool analyseString(
        VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::STRING;
    }

    constexpr bool analyseLabel(
        VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::LABEL;
    }

    constexpr bool analyseOpenExpression(
        VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::LPAR;
    }

    constexpr bool analyseCloseExpression(
        VectorCRange<Token> tokens) const noexcept
    {
      return !tokens.empty() &&
             tokens[0].type == TT::RPAR;
    }

    constexpr Distance analyseExpression(
        VectorCRange<Token> tokens) const noexcept
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
            else if (
              Distance subd = analyseExpression(tokens); 
              subd != 0)
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