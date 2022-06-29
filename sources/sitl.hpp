#ifndef __sitl_tokens_hpp__
#define __sitl_tokens_hpp__

#include <lib/string.hpp>
#include <lib/vector.hpp>
#include <model/token.hpp>
#include <model/tokentype.hpp>
#include<tokenizer/tokenizer.hpp>
#include <tokenizer/globaltokenizer.hpp>
#include <tokenizer/canbenchars.hpp>
#include <tokenizer/extractinside.hpp>
#include <tokenizer/extractnchars.hpp>
#include <tokenizer/tokenizers.hpp>
#include <tokenizer/proceduraltokenizer.hpp>
#include <tokenizer/expressiontokenizer.hpp>
#include <model/line.hpp>
#include <model/linetype.hpp>
#include <analyser/oneanalyser.hpp>
#include <analyser/nsomeanalyser.hpp>
#include <analyser/sequenceanalyser.hpp>


namespace sitl
{

  template <typename... A>
  struct LineAnalyser
  {
    static constexpr Size S = (0 + ... + A::S);
    constexpr bool operator()(VectorCRange<Token> tline) const noexcept
    {
      bool tmp;
      Size pos = 0;
      return ((tline.size() >= S) && ... && ((tmp = A()(tline, pos)), pos += A::S, tmp));
    }
  };

  using BeginLineAnalyser =
      LineAnalyser<One<TokenType::BEGIN>>;

  using StructLineAnalyser =
      LineAnalyser<Sequence<
          TokenType::STRUCT,
          TokenType::LABEL>>;

  using ParamLineAnalyser =
      LineAnalyser<
          One<TokenType::PARAM>,
          One<TokenType::LABEL>,
          One<TokenType::LABEL>>;

  using EndLineAnalyser =
      LineAnalyser<One<TokenType::END>>;

  using LetLineAnalyser =
      LineAnalyser<
          Sequence<TokenType::LET,
                   TokenType::LABEL,
                   TokenType::LABEL,
                   TokenType::EXPR>>;

  using IfLineAnalyser =
      LineAnalyser<One<TokenType::IF>>;

  template <typename... A>
  struct GlobalAnalyser
  {
    constexpr bool operator()(VectorCRange<Token> tokens) const noexcept
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

  using SitlAnalyser =
      GlobalAnalyser<
          StructLineAnalyser,
          BeginLineAnalyser,
          ParamLineAnalyser,
          EndLineAnalyser,
          LetLineAnalyser>;

  struct ExpressionAnalyser
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