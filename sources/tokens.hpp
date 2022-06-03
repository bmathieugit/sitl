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
  };

  struct Token
  {
    TokenType type;
    StringCRange value;
  };

  template <TokenType type>
  struct CanBe;

  template <TokenType type>
  struct Extract;

  template <TokenType type>
  constexpr bool canbe(Char c) noexcept
  {
    return CanBe<type>()(c);
  }

  template <TokenType type>
  constexpr bool canbe(StringCRange s) noexcept
  {
    return CanBe<type>()(s);
  }

  template <TokenType type>
  constexpr Token extract(StringCRange src) noexcept
  {
    StringCRange res = Extract<type>()(src);

    return res.empty()
               ? Token{TokenType::ERROR, src.sub(0, 1)}
               : Token{type, res};
  }

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
    constexpr bool operator()(Char c) const noexcept
    {
      return c == o;
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

  template <>
  struct CanBe<TokenType::LABEL>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c.between('a', 'z') || c == '_';
    }
  };

  template <>
  struct Extract<TokenType::LABEL>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.before_if(
          [](Char c)
          { return !(c.between('a', 'z') || c == '_'); });
    }
  };

  template <>
  struct CanBe<TokenType::NUMBER>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c.between('0', '9');
    }
  };

  template <>
  struct Extract<TokenType::NUMBER>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.before_if(
          [](Char c)
          { return !c.between('0', '9'); });
    }
  };

  template <>
  struct CanBe<TokenType::STRING> : CanBeNChars<'"'>
  {
  };

  template <>
  struct Extract<TokenType::STRING>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.inside('"', '"');
    }
  };

  template <>
  struct CanBe<TokenType::BLANK>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c.in(" \t");
    }
  };

  template <>
  struct Extract<TokenType::BLANK>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.before_if([](Char c)
                           { return !c.in(" \t"); });
    }
  };

  template <>
  struct CanBe<TokenType::STAR> : CanBeNChars<'*'>
  {
  };

  template <>
  struct Extract<TokenType::STAR> : ExtractNChars<1>
  {
  };

  template <>
  struct CanBe<TokenType::EQUAL> : CanBeNChars<'='>
  {
  };

  template <>
  struct Extract<TokenType::EQUAL> : ExtractNChars<1>
  {
  };

  template <>
  struct CanBe<TokenType::LPAR> : CanBeNChars<'('>
  {
  };

  template <>
  struct Extract<TokenType::LPAR> : ExtractNChars<1>
  {
  };

  template <>
  struct CanBe<TokenType::RPAR> : CanBeNChars<')'>
  {
  };

  template <>
  struct Extract<TokenType::RPAR> : ExtractNChars<1>
  {
  };

  template <>
  struct CanBe<TokenType::PLUS> : CanBeNChars<'+'>
  {
  };

  template <>
  struct Extract<TokenType::PLUS> : ExtractNChars<1>
  {
  };

  template <>
  struct CanBe<TokenType::LESS> : CanBeNChars<'<'>
  {
  };

  template <>
  struct Extract<TokenType::LESS> : ExtractNChars<1>
  {
  };

  template <>
  struct CanBe<TokenType::GREATER> : CanBeNChars<'>'>
  {
  };

  template <>
  struct Extract<TokenType::GREATER> : ExtractNChars<1>
  {
  };

  template <>
  struct CanBe<TokenType::LESSEQ> : CanBeNChars<'<', '='>
  {
  };

  template <>
  struct Extract<TokenType::LESSEQ> : ExtractNChars<2>
  {
  };

  template <>
  struct CanBe<TokenType::GREATEREQ> : CanBeNChars<'>', '='>
  {
  };

  template <>
  struct Extract<TokenType::GREATEREQ> : ExtractNChars<2>
  {
  };

  template <>
  struct CanBe<TokenType::STRUCT> : CanBeNChars<'s', 't', 'r', 'u', 'c', 't'>
  {
  };

  template <>
  struct Extract<TokenType::STRUCT> : ExtractNChars<6>
  {
  };

  template <>
  struct CanBe<TokenType::WHILE> : CanBeNChars<'w', 'h', 'i', 'l', 'e'>
  {
  };

  template <>
  struct Extract<TokenType::WHILE> : ExtractNChars<5>
  {
  };

  template <>
  struct CanBe<TokenType::BEGIN> : CanBeNChars<'b', 'e', 'g', 'i', 'n'>
  {
  };

  template <>
  struct Extract<TokenType::BEGIN> : ExtractNChars<5>
  {
  };

  template <>
  struct CanBe<TokenType::END> : CanBeNChars<'e', 'n', 'd'>
  {
  };

  template <>
  struct Extract<TokenType::END> : ExtractNChars<3>
  {
  };

  Vector<Token> tokenize(StringCRange src) noexcept
  {
    Vector<Token> tokens;

    do
    {
      StringCRange line = src.go_after('\n');
      Token res;

      while (!line.empty())
      {
        Char c = line[0];

        if (canbe<TokenType::BLANK>(c))
          res = extract<TokenType::BLANK>(line);

        else if (canbe<TokenType::NUMBER>(c))
          res = extract<TokenType::NUMBER>(line);
        else if (canbe<TokenType::STRING>(c))
          res = extract<TokenType::STRING>(line);

        else if (canbe<TokenType::LPAR>(c))
          res = extract<TokenType::LPAR>(line);
        else if (canbe<TokenType::RPAR>(c))
          res = extract<TokenType::RPAR>(line);

        else if (canbe<TokenType::STAR>(c))
          res = extract<TokenType::STAR>(line);

        else if (canbe<TokenType::BEGIN>(line))
          res = extract<TokenType::BEGIN>(line);
        else if (canbe<TokenType::END>(line))
          res = extract<TokenType::END>(line);
        else if (canbe<TokenType::WHILE>(line))
          res = extract<TokenType::WHILE>(line);
        else if (canbe<TokenType::STRUCT>(line))
          res = extract<TokenType::STRUCT>(line);

        else if (canbe<TokenType::LABEL>(c))
          res = extract<TokenType::LABEL>(line);

        line = line.sub(res.value.size());

        if (res.type == TokenType::ERROR)
          break;
        else if (res.type != TokenType::BLANK)
          tokens.push(move(res));
      }

      tokens.push(Token{TokenType::EOL, sr("\\n")});

      if (tokens.back().type == TokenType::ERROR)
        break;

    } while (!src.empty());

    return tokens;
  }

  enum class NodeType : int
  {
    STRUCT,
    BEGIN,
    END,
    LABEL
  };

  using Depth = int;

  struct Node
  {
    NodeType type;
    Depth depth;
    StringCRange value;
  };

  template <NodeType type>
  struct SyntaxAnalyser;

  template <>
  struct SyntaxAnalyser<NodeType::STRUCT>
  {
    constexpr auto operator()(VectorCRange<Token> line) const noexcept
    {
      if (line.size() == 2)
      {
        auto &&tstruct = line[0];
        auto &&tname = line[1];

        if (tstruct.type == TokenType::STRUCT &&
            tname.type == TokenType::LABEL)
        {
          NodeType type = NodeType::STRUCT;
          Node nstruct{NodeType::STRUCT, depth + 1, tname.value};

          // On retourne un array d'une taille fixe permettant ainsi de 
          return Array<Node, 1>(nstruct); // On retourne
        }
      }
    }
  };
}

#endif