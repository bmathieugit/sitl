#include <fstream>
#include <streambuf>

#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/args.hpp>
#include <lib/vector.hpp>

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
    StringCRange val;
    TokenType type;
  };

  struct StringTokenizer
  {
    constexpr bool canbe(StringCRange src) const noexcept
    {
      return !src.empty() && src[0] == '"';
    }

    constexpr Token tokenize(StringCRange src) const noexcept
    {
      return Token{
          src.inside('"', '"'),
          TokenType::string};
    }
  };

  struct NumberTokenizer
  {
    constexpr bool canbe(StringCRange src) const noexcept
    {
      return !src.empty() && ('0' <= src[0] && src[0] <= '9');
    }

    constexpr Token tokenize(StringCRange src) const noexcept
    {
      return Token{
          StringCRange(
              src.find_if_not(
                  [](char c)
                  { return '0' <= c && c <= '9'; }),
              src.end()),
          TokenType::string};
    }
  };

  struct LabelTokenizer
  {
    constexpr bool canbe(StringCRange src) const noexcept
    {
      return !src.empty() && ('a' <= src[0] && src[0] <= 'z');
    }
  };

  struct BlankTokenizer
  {
  };

  struct Tokenizer
  {
    constexpr Vector<Token> tokenize(
        StringCRange src) const noexcept
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

namespace sitl
{
  class InstructionLine
  {
  private:
    Vector<String> tks;

  public:
    InstructionLine() noexcept = default;

    explicit InstructionLine(Vector<String> &&_tokens) noexcept
        : tks(move(_tokens)) {}

    InstructionLine(const InstructionLine &) noexcept = default;
    InstructionLine(InstructionLine &&) noexcept = default;
    InstructionLine &operator=(const InstructionLine &) noexcept = default;
    InstructionLine &operator=(InstructionLine &&) noexcept = default;
    ~InstructionLine() noexcept = default;

  public:
    bool empty() const noexcept
    {
      return tks.empty();
    }

    Size size() const noexcept
    {
      return tks.size();
    }

    const Vector<String> &tokens() const noexcept
    {
      return tks;
    }

    auto begin() noexcept
    {
      return tks.begin();
    }

    auto end() noexcept
    {
      return tks.end();
    }

    auto begin() const noexcept
    {
      return tks.begin();
    }

    auto end() const noexcept
    {
      return tks.end();
    }
  };

  class InstructionLineBuilder
  {
  public:
    static InstructionLine build(StringCRange src) noexcept
    {
      StringCRange line = src.before('\n');
      Vector<String> sline(10);

      while (!line.empty())
      {
        String token;

        sline.push(move(token));
        
      }

      return InstructionLine(move(sline));
    }
  };
}

int main(int argc, char **argv)
{
  sitl::CommandLine args(argc, argv);

  if (args.contains(sitl::sr("file")))
  {
    sitl::StringCRange fname = args.value(sitl::sr("file"));
    sitl::logger::debug("file name found, fname");
  }

  sitl::StringCRange src = sitl::sr("int i = 12;");
  sitl::Vector<sitl::Token> tokens = sitl::Tokenizer().tokenize(src);

  for (const sitl::Token &token : tokens)
  {
    sitl::logger::debug(token.val, " : ", (int)token.type);
  }

  return EXIT_SUCCESS;
}