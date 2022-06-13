#ifndef __sitl_tokens_hpp__
#define __sitl_tokens_hpp__

#include <lib/string.hpp>
#include <lib/vector.hpp>
#include <lib/logger.hpp>

namespace sitl
{
  enum class TokenType : int
  {
    LABEL = 0,
    NUMBER = 1,
    STRING = 2,
    BLANK = 3,
    EOL = 4,
    ERROR = 5,
    EQUAL = 6,
    LPAR = 7,
    RPAR = 8,
    PLUS = 9,
    LESS = 10,
    GREATER = 11,
    LESSEQ = 12,
    GREATEREQ = 13,
    STAR = 14,
    WHILE = 15,
    STRUCT = 16,
    BEGIN = 17,
    END = 18,
    PARAM = 19,
    LET = 20,
    EXPR = 21,
    IF = 22,
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

  using LabelTokenizer = Tokenizer<
      TokenType::LABEL,
      decltype([](StringCRange s) noexcept
               { return Char(s[0]).between('a', 'z') ||
                        s[0] == '_'; }),
      decltype([](StringCRange src) noexcept
               { return src.before_if(
                     [](Char c) noexcept
                     { return !(c.between('a', 'z') ||
                                c == '_'); }); })>;

  using NumberTokenizer = Tokenizer<
      TokenType::NUMBER,
      decltype([](StringCRange s) noexcept
               { return Char(s[0]).between('0', '9'); }),
      decltype([](StringCRange src) noexcept
               { return src.before_if(
                     [](Char c) noexcept
                     { return !c.between('0', '9'); }); })>;

  using StringTokenizer = Tokenizer<
      TokenType::STRING,
      CanBeNChars<'"'>,
      decltype([](StringCRange src) noexcept
               { return src.inside('"', '"'); })>;

  using BlankTokenizer = Tokenizer<
      TokenType::BLANK,
      decltype([](StringCRange s) noexcept
               { return Char(s[0]).in(" \t"); }),
      decltype([](StringCRange src) noexcept
               { return src.before_if(
                     [](Char c)
                     { return !c.in(" \t"); }); })>;

  using ExpressionTokenizer = Tokenizer<
      TokenType::EXPR,
      decltype([](StringCRange s)
               { return s.starts_with(sr("$(")); }),
      decltype([](StringCRange s)
               {
        auto r = s.sub(2);
        auto lvl = 1;
        auto i = 0;
        auto sz = r.size();
        while (lvl != 0 && i < sz)
        {
          if (r[i] == '(')
            ++lvl;
          else if (r[i] == ')')
            --lvl;
          
          ++i;
        }
        return s.sub(0, i+2); })>;

  using StarTokenizer = Tokenizer<TokenType::STAR, CanBeNChars<'*'>, ExtractNChars<1>>;
  using EqualTokenizer = Tokenizer<TokenType::EQUAL, CanBeNChars<'='>, ExtractNChars<1>>;
  using LParTokenizer = Tokenizer<TokenType::LPAR, CanBeNChars<'('>, ExtractNChars<1>>;
  using RParTokenizer = Tokenizer<TokenType::RPAR, CanBeNChars<')'>, ExtractNChars<1>>;
  using PlusTokenizer = Tokenizer<TokenType::PLUS, CanBeNChars<'+'>, ExtractNChars<1>>;
  using LessTokenizer = Tokenizer<TokenType::LESS, CanBeNChars<'<'>, ExtractNChars<1>>;
  using GreaterTokenizer = Tokenizer<TokenType::GREATER, CanBeNChars<'>'>, ExtractNChars<1>>;
  using LessEqTokenizer = Tokenizer<TokenType::LESSEQ, CanBeNChars<'<', '='>, ExtractNChars<2>>;
  using GreaterEqTokenizer = Tokenizer<TokenType::GREATEREQ, CanBeNChars<'>', '='>, ExtractNChars<2>>;

  using StructTokenizer = Tokenizer<TokenType::STRUCT, CanBeNChars<'s', 't', 'r', 'u', 'c', 't'>, ExtractNChars<6>>;
  using BeginTokenizer = Tokenizer<TokenType::BEGIN, CanBeNChars<'b', 'e', 'g', 'i', 'n'>, ExtractNChars<5>>;
  using EndTokenizer = Tokenizer<TokenType::END, CanBeNChars<'e', 'n', 'd'>, ExtractNChars<3>>;
  using ParamTokenizer = Tokenizer<TokenType::PARAM, CanBeNChars<'p', 'a', 'r', 'a', 'm'>, ExtractNChars<5>>;
  using LetTokenizer = Tokenizer<TokenType::LET, CanBeNChars<'l', 'e', 't'>, ExtractNChars<3>>;

  using SitlTokenizer = GlobalTokenizer<
      StructTokenizer,
      BeginTokenizer,
      EndTokenizer,
      ParamTokenizer,
      LetTokenizer,
      NumberTokenizer,
      StringTokenizer,
      ExpressionTokenizer,
      BlankTokenizer,
      StarTokenizer,
      EqualTokenizer,
      LParTokenizer,
      RParTokenizer,
      PlusTokenizer,
      LessTokenizer,
      GreaterTokenizer,
      LessEqTokenizer,
      GreaterEqTokenizer,
      LabelTokenizer>;

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
        logger::debug("temporary res : ", res, " with a line of length ", line.size());
      } while (!tokens.empty() && res);

      return res;
    }
  };

  using SitlAnalyser =
      GlobalAnalyser<
          StructLineAnalyser,
          BeginLineAnalyser,
          ParamLineAnalyser,
          EndLineAnalyser>;

}

#endif