#ifndef __sitl_tokens_hpp__
#define __sitl_tokens_hpp__

#include <lib/string.hpp>
#include <lib/vector.hpp>

namespace sitl
{
  enum class TokenType : int
  {
    LABEL,
    NUMBER,
    BLANK,
    STRING,
    EOL,
    ERROR,
    WHILE,
    STRUCT,
    BEGIN,
    END,
    PARAM,
    LET,
    EXPR,
    IF,
    RETURN,
    FUN,
    PROC,
    LPAR,
    RPAR
  };

  struct Token
  {
    TokenType type;
    StringCRange value;
  };

  template <TokenType type, typename CANBE, typename EXTRACT>
  struct Tokenizer
  {
    constexpr bool canbe(StringCRange s) const noexcept
    {
      return CANBE()(s);
    }

    constexpr Token extract(StringCRange src) const noexcept
    {
      auto value = EXTRACT()(src);
      return value.empty()
                 ? Token{TokenType::ERROR, src.sub(0, 1)}
                 : Token{type, value};
    }
  };

  template <typename... T>
  class GlobalTokenizer
  {
    using TT = TokenType;

    constexpr Token error(StringCRange line) const noexcept
    {
      return Token{TT::ERROR, line.sub(0, 1)};
    }

    constexpr Token eol() const noexcept
    {
      return Token{TT::EOL, sr("\\n")};
    }

    template <typename T0, typename... TN>
    constexpr Token tokenize(StringCRange line) const noexcept
    {
      if (T0().canbe(line))
        return T0().extract(line);
      else if constexpr (sizeof...(TN) > 0)
        return tokenize<TN...>(line);
      else
        return error(line);
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

        tokens.push(eol());

      } while (!src.empty());

      return tokens;
    }
  };

  template <char... cn>
  struct CanBeNChars
  {
    constexpr bool operator()(StringCRange s) const noexcept
    {
      return s.starts_with(Array<const char, sizeof...(cn)>{{cn...}});
    }
  };

  template <char o>
  struct CanBeNChars<o>
  {
    constexpr bool operator()(StringCRange s) const noexcept
    {
      return s[0] == o;
    }
  };

  template <Size n>
  struct ExtractNChars
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, n);
    }
  };

  template <char b, char e>
  struct ExtractInside
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.inside(b, e);
    }
  };

  using NumberTokenizer = Tokenizer<
      TokenType::NUMBER,
      decltype([](StringCRange s) noexcept
               { return Char(s[0]).between('0', '9'); }),
      decltype([](StringCRange s) noexcept
               { return s.before_if(
                     [](Char c) noexcept
                     { return !(c.between('0', '9')); }); })>;
  using LabelTokenizer =
      Tokenizer<
          TokenType::LABEL,
          decltype([](StringCRange s) noexcept
                   { return Char(s[0]).between('a', 'z') ||
                            s[0] == '_'; }),
          decltype([](StringCRange src) noexcept
                   { return src.before_if(
                         [](Char c) noexcept
                         { return !(c.between('a', 'z') ||
                                    c == '_'); }); })>;
  using BlankTokenizer =
      Tokenizer<
          TokenType::BLANK,
          decltype([](StringCRange s) noexcept
                   { return Char(s[0]).in(" \t"); }),
          decltype([](StringCRange src) noexcept
                   { return src.before_if(
                         [](Char c)
                         { return !c.in(" \t"); }); })>;
  using StringTokenizer =
      Tokenizer<
          TokenType::STRING,
          CanBeNChars<'"'>,
          ExtractInside<'"', '"'>>;
  using ExpressionTokenizer =
      Tokenizer<TokenType::EXPR,
                CanBeNChars<'\''>,
                ExtractInside<'\'', '\''>>;
  using StructTokenizer =
      Tokenizer<TokenType::STRUCT,
                CanBeNChars<'s', 't', 'r', 'u', 'c', 't'>,
                ExtractNChars<6>>;
  using RParTokenizer =
      Tokenizer<TokenType::RPAR,
                CanBeNChars<')'>,
                ExtractNChars<1>>;
  using LParTokenizer =
      Tokenizer<TokenType::LPAR,
                CanBeNChars<'('>,
                ExtractNChars<1>>;
  using BeginTokenizer =
      Tokenizer<TokenType::BEGIN,
                CanBeNChars<'b', 'e', 'g', 'i', 'n'>,
                ExtractNChars<5>>;
  using EndTokenizer =
      Tokenizer<TokenType::END,
                CanBeNChars<'e', 'n', 'd'>,
                ExtractNChars<3>>;
  using ParamTokenizer =
      Tokenizer<TokenType::PARAM,
                CanBeNChars<'p', 'a', 'r', 'a', 'm'>,
                ExtractNChars<5>>;
  using LetTokenizer =
      Tokenizer<TokenType::LET,
                CanBeNChars<'l', 'e', 't'>,
                ExtractNChars<3>>;
  using ReturnTokenizer =
      Tokenizer<TokenType::RETURN,
                CanBeNChars<'r', 'e', 't', 'u', 'r', 'n'>,
                ExtractNChars<6>>;

  using FunTokenizer =
      Tokenizer<TokenType::FUN,
                CanBeNChars<'f', 'u', 'n'>,
                ExtractNChars<3>>;
  using ProcTokenizer =
      Tokenizer<TokenType::PROC,
                CanBeNChars<'p', 'r', 'o', 'c'>,
                ExtractNChars<4>>;

  using SitlTokenizer = GlobalTokenizer<
      BlankTokenizer,
      StructTokenizer,
      BeginTokenizer,
      EndTokenizer,
      ParamTokenizer,
      LetTokenizer,
      ReturnTokenizer,
      ExpressionTokenizer,
      LabelTokenizer>;

  using LispTokenizer = GlobalTokenizer<
      NumberTokenizer,
      StringTokenizer,
      LabelTokenizer,
      LParTokenizer,
      RParTokenizer,
      BlankTokenizer>;

  enum class LineType : int
  {
    STRUCT,
    BEGIN,
    END,
    PARAM,
    ERROR,
    IF
  };

  using Depth = int;

  struct Line
  {
    LineType type;
    Depth depth;
    Vector<Token> tokens;
  };

  using Position = Size;

  template <TokenType type>
  struct One
  {
    static constexpr Size S = 1;
    constexpr bool operator()(VectorCRange<Token> tline, Position pos) const noexcept
    {
      return tline[pos].type == type;
    }
  };

  template <TokenType... types>
  struct Sequence
  {
    static constexpr Size S = sizeof...(types);
    constexpr bool operator()(VectorCRange<Token> tline, Position pos) const noexcept
    {
      return (true && ... && (tline[pos++].type == types));
    }
  };

  template <Size n, TokenType type>
  struct NSome
  {
    static constexpr Size S = n;
    constexpr bool operator()(VectorCRange<Token> tline, Position pos) const noexcept
    {
      for (int i = pos; i < n; i++)
        if (tline[i].type != type)
          return false;
      return true;
    }
  };

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