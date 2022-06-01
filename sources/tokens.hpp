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
    SYMBOL = 3,
    BLANK = 4,
    EOL = 5,
    EOS = 6,
    ERROR = 7,
    EQUAL = 8,
    LPAR = 9,
    RPAR = 10,
    PLUS = 11,
    LESS = 12,
    GREATER = 13,
    LESSEQ = 14,
    GREATEREQ = 15,
  };

  struct Token
  {
    StringCRange value;
    TokenType type;
  };

  template <TokenType type,
            typename CANBE,
            typename EXTRACT>
  struct Tokenizer
  {

    constexpr bool canbe(StringCRange src) const noexcept
    {
      return CANBE()(src);
    }

    constexpr Token extract(StringCRange src) const noexcept
    {
      Token t{EXTRACT()(src), type};

      if (t.value.empty())
        t.type = TokenType::ERROR;

      return t;
    }
  };

  using LessEqTokenizer =
      Tokenizer<
          TokenType::LESSEQ,
          decltype([](StringCRange src) noexcept
                   { return src.starts_with(sr("<=")); }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 2); })>;

  using GreaterEqTokenizer =
      Tokenizer<
          TokenType::GREATEREQ,
          decltype([](StringCRange src) noexcept
                   { return src.starts_with(sr(">=")); }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 2); })>;

  using LessTokenizer =
      Tokenizer<
          TokenType::LESS,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && src[0] == '<'; }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 1); })>;

  using GreaterTokenizer =
      Tokenizer<
          TokenType::GREATER,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && src[0] == '>'; }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 1); })>;

  using LParTokenizer =
      Tokenizer<
          TokenType::LPAR,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && src[0] == '('; }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 1); })>;

  using RParTokenizer =
      Tokenizer<
          TokenType::RPAR,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && src[0] == ')'; }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 1); })>;

  using PlusTokenizer =
      Tokenizer<
          TokenType::PLUS,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && src[0] == '+'; }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 1); })>;

  using EqualTokenizer =
      Tokenizer<
          TokenType::EQUAL,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && src[0] == '='; }),
          decltype([](StringCRange src) noexcept
                   { return src.sub(0, 1); })>;

  using StringTokenizer =
      Tokenizer<
          TokenType::STRING,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && src[0] == '"'; }),
          decltype([](StringCRange src) noexcept
                   { return src.inside('"', '"'); })>;

  using NumberTokenizer =
      Tokenizer<
          TokenType::NUMBER,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && '0' <= src[0] && src[0] <= '9'; }),
          decltype([](StringCRange src) noexcept
                   { return StringCRange(
                         src.begin(),
                         src.find_if_not(
                             [](char c)
                             { return '0' <= c && c <= '9'; })); })>;

  using BlankTokenizer =
      Tokenizer<
          TokenType::BLANK,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() && sr(" \t\n\r").contains(src[0]); }),
          decltype([](StringCRange src) noexcept
                   { return StringCRange(
                         src.begin(),
                         src.find_if_not(
                             [](char c)
                             { return sr(" \t\n\r").contains(c); })); })>;

  using LabelTokenizer =
      Tokenizer<
          TokenType::LABEL,
          decltype([](StringCRange src) noexcept
                   { return !src.empty() &&
                            (('a' <= src[0] && src[0] <= 'z') ||
                             src[0] == '_'); }),
          decltype([](StringCRange src) noexcept
                   { return StringCRange(
                         src.begin(),
                         src.find_if_not(
                             [](char c)
                             { return (('a' <= c && c <= 'z') ||
                                       c == '_'); })); })>;

  using ErrorTokenizer =
      Tokenizer<
          TokenType::ERROR,
          void, decltype([](StringCRange src)
                         { return src.sub(0, 1); })>;

  Vector<Token> tokenize(StringCRange src) noexcept
  {
    Vector<Token> tokens;

    do
    {
      StringCRange line = src.go_after('\n');
      Token res;

      while (!line.empty())
      {
        if (BlankTokenizer().canbe(line))
          line = line.sub(BlankTokenizer().extract(line).value.size());

        if (LabelTokenizer().canbe(line))
          res = LabelTokenizer().extract(line);
        else if (NumberTokenizer().canbe(line))
          res = NumberTokenizer().extract(line);
        else if (StringTokenizer().canbe(line))
          res = StringTokenizer().extract(line);
        else if (GreaterEqTokenizer().canbe(line))
          res = GreaterEqTokenizer().extract(line);
        else if (LessEqTokenizer().canbe(line))
          res = LessEqTokenizer().extract(line);
        else if (EqualTokenizer().canbe(line))
          res = EqualTokenizer().extract(line);
        else if (LParTokenizer().canbe(line))
          res = LParTokenizer().extract(line);
        else if (RParTokenizer().canbe(line))
          res = RParTokenizer().extract(line);
        else if (PlusTokenizer().canbe(line))
          res = PlusTokenizer().extract(line);
        else if (LessTokenizer().canbe(line))
          res = LessTokenizer().extract(line);
        else if (GreaterTokenizer().canbe(line))
          res = GreaterTokenizer().extract(line);
        else
          res = ErrorTokenizer().extract(line);

        tokens.push(move(res));

        if (tokens.back().type == TokenType::ERROR)
          break;

        line = line.sub(tokens.back().value.size());
      }

      if (tokens.back().type == TokenType::ERROR)
        break;

    } while (!src.empty());

    return tokens;
  }

}

#endif