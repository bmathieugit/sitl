#include <vector>
#include <string_view>
#include <functional>

#include "tokens.hpp"

// static bool __isdigit(char c)
// {
//   return '0' <= c and c <= '9';
// }

// static bool __isalpha(char c)
// {
//   return ('a' <= c and c <= 'z') or
//          ('A' <= c and c <= 'Z') or
//          c == '_';
// }

// static bool __isblank(char c)
// {
//   return c == ' ' or
//          c == '\r' or
//          c == '\v' or
//          c == '\f';
// }

static std::string_view __ignoreblk(std::string_view src)
{
  size_t pos = src.find_first_not_of(" \r\t\n");
  return pos == std::string_view::npos
             ? std::string_view()
             : src.substr(pos);
}

static auto keyword(
    std::string_view kw,
    sitl::token_type tp)
{
  return [=](std::string_view src)
  {
    return src.starts_with(kw)
               ? sitl::token{tp, kw}
               : sitl::token{};
  };
}

// static sitl::token string(std::string_view src)
// {
// }

// static sitl::token identifier(std::string_view src)
// {
// }

static sitl::token integer(std::string_view src)
{
  size_t pos = src.find_first_not_of("0123456789");
  return pos == std::string_view::npos
             ? sitl::token{}
             : sitl::token{sitl::token_type::sm_int, src.substr(0, pos)};
}

struct parser
{
  std::string_view src;
  sitl::token tk;
  std::vector<std::function<sitl::token(std::string_view)>> tests;

  parser &init(std::string_view sc)
  {
    src = sc;
    return *this;
  }

  parser &tryparse(const std::function<sitl::token(std::string_view)> &test)
  {
    tests.push_back(test);
    return *this;
  }

  sitl::token token()
  {
    for (auto &&test : tests)
    {
      sitl::token tk = test(src);

      if (tk.tp != sitl::token_type::notyet)
        return tk;
    }

    sitl::token tk;
    tk.tp = sitl::token_type::unexpected;
    return tk;
  }
};

std::vector<sitl::token> sitl::tokens(std::string_view src)
{
  using tt = sitl::token_type;

  std::vector<sitl::token> tks;
  std::string_view scan = src;

  parser psr;

  psr.tryparse(keyword("type", tt::kw_type))
      .tryparse(keyword("build", tt::kw_build))
      .tryparse(keyword("copy", tt::kw_copy))
      .tryparse(keyword("move", tt::kw_move))
      .tryparse(keyword("fun", tt::kw_fun))
      .tryparse(keyword("del", tt::kw_del))
      .tryparse(keyword("if", tt::kw_if))
      .tryparse(keyword("while", tt::kw_while))
      .tryparse(keyword("for", tt::kw_for))
      .tryparse(keyword("true", tt::kw_true))
      .tryparse(keyword("false", tt::kw_false))
      .tryparse(keyword("return", tt::kw_return))
      .tryparse(keyword("('", tt::sm_lbracket))
      .tryparse(keyword(")", tt::sm_rbracket))
      .tryparse(keyword("[", tt::sm_lsbracket))
      .tryparse(keyword("]", tt::sm_rsbracket))
      .tryparse(keyword("{", tt::sm_lbrace))
      .tryparse(keyword("}", tt::sm_rbrace))
      .tryparse(keyword(":=", tt::sm_mv))
      .tryparse(keyword("=", tt::sm_eq))
      .tryparse(keyword(":", tt::sm_colon))
      .tryparse(keyword(",", tt::sm_comma))
      /*.tryparse(string)
        .tryparse(identifier)*/
        .tryparse(integer)
      ;

  while (not scan.empty())
  {

    scan = __ignoreblk(scan);
    sitl::token tk = psr.init(scan).token();

    if (tk.tp == tt::unexpected)
      scan = scan.substr(1);
    else
      scan = scan.substr(tk.val.size());

    tks.push_back(tk);
  }

  return tks;
}