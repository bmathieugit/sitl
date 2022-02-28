#include <string_view>
#include <functional>
// #include <tuple>
#include <vector>

#include "tokens.hpp"

static constexpr std::string_view lower =
    "abcdefghijklmnopqrstuvwxyz";

static constexpr std::string_view upper =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static constexpr std::string_view digit =
    "0123456789";

static constexpr std::string_view blank =
    " \n\t\r";

static constexpr std::string_view alnum =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "_";

static constexpr std::string_view alpha =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "_";

static constexpr size_t svnpos = std::string_view::npos;

static std::string_view
__ignoreblk(std::string_view src)
{
  size_t pos = src.find_first_not_of(blank);
  return pos == svnpos
             ? std::string_view()
             : src.substr(pos);
}

static auto
keyword(
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

static sitl::token string(std::string_view src)
{
  if (src.starts_with('"'))
  {
    size_t pos = src.substr(1).find_first_of('"');

    if (pos != svnpos)
      return sitl::token{
          sitl::token_type::sm_str,
          src.substr(0, pos + 2)};
  }

  return sitl::token{};
}

static sitl::token identifier(std::string_view src)
{
  using tt = sitl::token_type;
  size_t pos = src.find_first_of(alpha) == 0
                   ? src.find_first_not_of(alnum)
                   : svnpos;
  return pos == svnpos
             ? sitl::token{}
             : sitl::token{tt::sm_id, src.substr(0, pos)};
}

static sitl::token integer(std::string_view src)
{
  using tt = sitl::token_type;
  size_t pos = src.find_first_not_of(digit);
  return pos == 0
             ? sitl::token{}
             : sitl::token{tt::sm_int, src.substr(0, pos)};
}

template <
    typename... test_t>
constexpr static auto make_parser(
    test_t &&...t)
{
  return [=](std::string_view src)
  {
    using tt = sitl::token_type;

    if (src.empty())
      return sitl::token{tt::last};

    sitl::token tk;

    return (((tk = t(src)).tp != tt::notyet) || ...)
               ? tk
               : sitl::token{tt::unexpected};
  };
}

std::vector<sitl::token> sitl::tokens(std::string_view src)
{
  using tt = sitl::token_type;

  std::vector<sitl::token> tks;
  std::string_view scan = src;
  auto prs = make_parser(
      keyword("type", tt::kw_type),
      keyword("build", tt::kw_build),
      keyword("copy", tt::kw_copy),
      keyword("move", tt::kw_move),
      keyword("fun", tt::kw_fun),
      keyword("del", tt::kw_del),
      keyword("if", tt::kw_if),
      keyword("while", tt::kw_while),
      keyword("for", tt::kw_for),
      keyword("true", tt::kw_true),
      keyword("false", tt::kw_false),
      keyword("return", tt::kw_return),
      keyword("('", tt::sm_lbracket),
      keyword(")", tt::sm_rbracket),
      keyword("[", tt::sm_lsbracket),
      keyword("]", tt::sm_rsbracket),
      keyword("{", tt::sm_lbrace),
      keyword("}", tt::sm_rbrace),
      keyword(":=", tt::sm_mv),
      keyword("=", tt::sm_eq),
      keyword(":", tt::sm_colon),
      keyword(",", tt::sm_comma),
      string,
      integer,
      identifier);

  while (not scan.empty())
  {
    scan = __ignoreblk(scan);

    sitl::token tk = prs(scan);

    if (tk.tp == tt::last)
      scan = "";
    if (tk.tp == tt::unexpected)
      scan = scan.substr(1);
    else
      scan = scan.substr(tk.val.size());

    tks.push_back(tk);
  }

  return tks;
}