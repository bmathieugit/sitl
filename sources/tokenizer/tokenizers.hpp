#ifndef __sitl_tokenizers_hpp__
#define __sitl_tokenizers_hpp__

#include <model/tokentype.hpp>
#include <lib/string.hpp>
#include <tokenizer/tokenizer.hpp>
#include <tokenizer/canbenchars.hpp>
#include <tokenizer/extractinside.hpp>
#include <tokenizer/extractnchars.hpp>

namespace sitl
{
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

}

#endif