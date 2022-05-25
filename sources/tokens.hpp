#ifndef __sitl_tokens_hpp__
#define __sitl_tokens_hpp__

#include <lib/string.hpp>
#include <lib/vector.hpp>

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
    EQUAL = 8
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

  using EqualTokenizer =
      Tokenizer<TokenType::EQUAL,
                decltype([](StringCRange src) noexcept
                         { return !src.empty() && src[0] == '='; }),
                decltype([](StringCRange src) noexcept
                         { return src.sub(0, 1); })>;

  using StringTokenizer =
      Tokenizer<TokenType::STRING,
                decltype([](StringCRange src) noexcept
                         { return !src.empty() && src[0] == '"'; }),
                decltype([](StringCRange src) noexcept
                         { return src.inside('"', '"'); })>;

  using NumberTokenizer =
      Tokenizer<TokenType::NUMBER,
                decltype([](StringCRange src) noexcept
                         { return !src.empty() && '0' <= src[0] && src[0] <= '9'; }),
                decltype([](StringCRange src) noexcept
                         { return StringCRange(
                               src.begin(),
                               src.find_if_not(
                                   [](char c)
                                   { return '0' <= c && c <= '9'; })); })>;

  using BlankTokenizer =
      Tokenizer<TokenType::BLANK,
                decltype([](StringCRange src) noexcept
                         { return !src.empty() && sr(" \t\n\r").contains(src[0]); }),
                decltype([](StringCRange src) noexcept
                         { return StringCRange(
                               src.begin(),
                               src.find_if_not(
                                   [](char c)
                                   { return sr(" \t\n\r").contains(c); })); })>;

  using LabelTokenizer =
      Tokenizer<TokenType::LABEL,
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

  Vector<Token> tokenize(StringCRange src) noexcept
  {
    Vector<Token> tokens;

    while (!src.empty())
    {

      // TODO: faire un traitement ligne par ligne. 
      // TODO: aucun token n'est sur plusieurs lignes. 
      StringCRange line = src.before('\n');

      if (BlankTokenizer().canbe(src))
        src = src.sub(BlankTokenizer().extract(src).value.size());

      if (LabelTokenizer().canbe(src))
        tokens.push(LabelTokenizer().extract(src));
      else if (NumberTokenizer().canbe(src))
        tokens.push(NumberTokenizer().extract(src));
      else if (StringTokenizer().canbe(src))
        tokens.push(StringTokenizer().extract(src));
      else if (EqualTokenizer().canbe(src))
        tokens.push(EqualTokenizer().extract(src));

      if (tokens.back().type == TokenType::ERROR)
        break;
      else
        src = src.sub(tokens.back().value.size());
    }

    return tokens;
  }

}

#endif