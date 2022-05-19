#include <fstream>
#include <streambuf>

#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/args.hpp>

namespace sitl
{
  enum class TokenType : int
  {
    label = 0,
    number = 1,
    string = 2,
    symbol = 3,
    blank = 4,
    eol = 5,
    eos = 6
  };

  struct Token
  {
    lib::StringView val;
    TokenType type;
  };

  struct StringTokenizer
  {
    constexpr bool canbe(lib::StringView src) const noexcept
    {
      return !src.empty() && src[0] == '"';
    }

    constexpr Token tokenize(lib::StringView src) const noexcept
    {
      return Token{
          src.range().inside('"', '"'),
          TokenType::string};
    }
  };

  struct NumberTokenizer
  {
    constexpr bool canbe(lib::StringView src) const noexcept
    {
      return !src.empty() && ('0' <= src[0] && src[0] <= '9');
    }

    constexpr Token tokenize(lib::StringView src) const noexcept
    {
      return Token{
          lib::StringView(
              src.range().find_if_not(
                  [](char c)
                  { return '0' <= c && c <= '9'; }),
              src.end()),
          TokenType::string};
    }
  };

  struct LabelTokenizer
  {
    constexpr bool canbe(lib::StringView src) const noexcept
    {
      return !src.empty() && ('a' <= src[0] && src[0] <= 'z');
    }
  };

  struct BlankTokenizer
  {
  };

  struct Tokenizer
  {
    constexpr lib::Vector<Token> tokenize(
        lib::StringView src) const noexcept
    {
      constexpr StringTokenizer string_tok;
      constexpr NumberTokenizer number_tok;
      constexpr BlankTokenizer blank_tok;
      constexpr LabelTokenizer label_tok;

      if (string_tok.canbe(src))
      {
      }
      else if (number_tok.canbe(src))
      {
      }
      else if (label_tok.canbe(src))
      {
      }

      return {};
    }
  };
}

int main(int argc, char **argv)
{
  lib::CommandLine args(argc, argv);

  if (args.contains("file"))
  {
    lib::StringView fname = args.value("file");
    lib::logger::debug("file name found, fname");
  }

  lib::StringView src = "int i = 12;";
  lib::Vector<sitl::Token> tokens = sitl::Tokenizer().tokenize(src);

  for (const sitl::Token &token : tokens)
  {
    lib::logger::debug(token.val, " : ", (int)token.type);
  }

  return EXIT_SUCCESS;
}