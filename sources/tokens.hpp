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
  struct CanBe<TokenType::STRING>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c == '"';
    }
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

  // EQUAL = 6,
  template <>
  struct CanBe<TokenType::EQUAL>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c == '=';
    }
  };

  template <>
  struct Extract<TokenType::EQUAL>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 1);
    }
  };

  template <>
  struct CanBe<TokenType::LPAR>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c == '(';
    }
  };

  template <>
  struct Extract<TokenType::LPAR>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 1);
    }
  };

  template <>
  struct CanBe<TokenType::RPAR>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c == ')';
    }
  };

  template <>
  struct Extract<TokenType::RPAR>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 1);
    }
  };

  template <>
  struct CanBe<TokenType::PLUS>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c == '+';
    }
  };

  template <>
  struct Extract<TokenType::PLUS>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 1);
    }
  };

  template <>
  struct CanBe<TokenType::LESS>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c == '<';
    }
  };

  template <>
  struct Extract<TokenType::LESS>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 1);
    }
  };

  template <>
  struct CanBe<TokenType::GREATER>
  {
    constexpr bool operator()(Char c) const noexcept
    {
      return c == '>';
    }
  };

  template <>
  struct Extract<TokenType::GREATER>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 1);
    }
  };

  template <>
  struct CanBe<TokenType::LESSEQ>
  {
    constexpr bool operator()(StringCRange s) const noexcept
    {
      return s.starts_with(sr("<="));
    }
  };

  template <>
  struct Extract<TokenType::LESSEQ>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 2);
    }
  };

  template <>
  struct CanBe<TokenType::GREATEREQ>
  {
    constexpr bool operator()(StringCRange s) const noexcept
    {
      return s.starts_with(sr(">="));
    }
  };

  template <>
  struct Extract<TokenType::GREATEREQ>
  {
    constexpr auto operator()(StringCRange src) const noexcept
    {
      return src.sub(0, 2);
    }
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

        else if (canbe<TokenType::LABEL>(c))
          res = extract<TokenType::LABEL>(line);

        else if (canbe<TokenType::NUMBER>(c))
          res = extract<TokenType::NUMBER>(line);

        else if (canbe<TokenType::STRING>(c))
          res = extract<TokenType::STRING>(line);

        else if (canbe<TokenType::PLUS>(c))
          res = extract<TokenType::PLUS>(line);

        else if (canbe<TokenType::LPAR>(c))
          res = extract<TokenType::LPAR>(line);

        else if (canbe<TokenType::RPAR>(c))
          res = extract<TokenType::RPAR>(line);

        else if (canbe<TokenType::LESSEQ>(line))
          res = extract<TokenType::LESSEQ>(line);

        else if (canbe<TokenType::GREATEREQ>(line))
          res = extract<TokenType::GREATEREQ>(line);

        else if (canbe<TokenType::EQUAL>(c))
          res = extract<TokenType::EQUAL>(line);

        else if (canbe<TokenType::LESS>(c))
          res = extract<TokenType::LESS>(line);

        else if (canbe<TokenType::GREATER>(c))
          res = extract<TokenType::GREATER>(line);

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
    WHILE,
    IF,
    FOR,
    LET,
    SET,
    RETURN,
    BEGIN,
    END,
    ADD,
    NUM,
    STR,
    VAR,

  };

  using Depth = int;

  struct Node
  {
    NodeType type;
    Depth depth;
    StringCRange value;
  };

  template <NodeType type>
  struct Analyzer
  {
  };

  void syntax_while(VectorCRange<Token> tokens, Depth depth, Vector<Node> &nodes) noexcept
  {
    if (!tokens.empty() &&
        (*tokens.begin()).value == sr("while"))
    {
      nodes.push(Node{NodeType::WHILE, depth + 1, (*tokens.begin()).value});
      tokens = tokens.sub(1);
    }
  }

  void syntax_statements(VectorCRange<Token> tokens, Depth depth, Vector<Node> &nodes) noexcept
  {
    while (!tokens.empty())
    {
      const Token &t = *tokens.begin();

      if (t.value == sr("while"))
        syntax_while(tokens, depth, nodes);
    }
  }

  Vector<Node>
  syntax(VectorCRange<Token> tokens) noexcept
  {
    Vector<Node> nodes;

    for (auto &&t : tokens)
      logger::debug("token : type : ", (int)t.type, "; value : ", t.value);

    if (!tokens.contains_if(
            [](const Token &t)
            { return t.type == TokenType::ERROR; }))
    {
      logger::debug("aucun token error detecté dans tokens");
      syntax_statements(tokens, 0, nodes);
    }
    else
      logger::error("un token error est contenu dans tokens");

    return nodes;
  }
}

#endif