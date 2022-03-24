#ifndef __sitl_tokens_hpp__
#define __sitl_tokens_hpp__

#include <string_view>
#include <vector>
#include <tuple>
#include <span>

namespace sitl
{
  enum class ttype
  {
    kw_type,
    kw_build,
    kw_copy,
    kw_move,
    kw_fun,
    kw_del,
    kw_if,
    kw_while,
    kw_for,
    kw_true,
    kw_false,
    kw_return,
    sm_lbrace,
    sm_rbrace,
    sm_lbracket,
    sm_rbracket,
    sm_lsbracket,
    sm_rsbracket,
    sm_eq,
    sm_mv,
    sm_colon,
    sm_scolon,
    sm_comma,
    sm_dot,
    sm_int,
    sm_str,
    sm_id,
    sm_blank,
    notyet,
    unexpected,
    last
  };

  struct token
  {
    using tt = ttype;

    ttype type = ttype::notyet;
    std::string_view val;
  };

  template <typename C, size_t n>
  struct keyword
  {
    constexpr keyword(
        const C (&s)[n])
    {
      std::span<const C> tmp(s);
      std::span<C> tmp2(kw);

      for (size_t i = 0; i < n; ++i)
        tmp2[i] = tmp[i];
    }

    C kw[n];
  };

  template <keyword kw, ttype>
  struct keyword_scanner
  {
    template <typename C>
    token<C> operator()(std::sv<C> src)
    {
      return src.starts_with(kw.kw)
                 ? {tp, kw.kw}
                 : {};
    }
  };

  struct integer_scanner
  {
    template <typename C>
    token<C> operator()(std::sv<C> src)
    {
      using tt = ttype;

      size_t pos = src.find_first_not_of(digit<C>());
      return pos == 0
                 ? {}
                 : {tt::sm_int, src.substr(0, pos)};
    }
  };

  struct string_scanner
  {
    template <typename C>
    token<C> operator()(std::sv<C> src)
    {
      usign tt = ttype;

      if (src.starts_with('"'))
      {
        size_t pos = src.substr(1)
                         .find_first_of('"');

        if (pos != std::sv<C>::npos)
          return {tt::sm_str, src.substr(0, pos + 2)};
      }

      return {};
    }
  };

  struct identifier_scanner
  {
    template <typename C>
    token<C> operator()(std::sv<C> src)
    {
      using tt = ttype;

      size_t pos = src.find_first_of(alpha<C>()) == 0
                       ? src.find_first_not_of(alnum<C>())
                       : std::sv<C>::npos;
      return pos == std::sv<C>::npos
                 ? {}
                 : {tt::sm_id, src.substr(0, pos)};
    }
  };

  struct ignore_scanner
  {
    template <typename C>
    token<C> operator()(std::sv<C> src)
    {
      using tt = ttype;

      size_t pos = src.find_first_not_of(blank<C>());
      return pos == std::sv<C>::npos
                 ? {}
                 : {tt::sm_blank, src.substr(0, pos)};
    }
  };

  struct empty_scanner
  {
    template <typename C>
    token<C> operator()(std::sv<C> src)
    {
      using tt = ttype;

      return src.empty()
                 ? {tt::last}
                 : {};
    }
  };

  template <typename... scanners>
  struct scanner_definition
  {
  };

  struct scanner
  {
    template <typename C,
              typename sc,
              typename... scs>
    token<C> scan_one(std::sv<C> src)
    {
      using tt = ttype;

      token<C> &&tk = sc{}(src);

      if (tk.type != tt::notyet)
        if constexpr (sizeof...(scs) > 0)
          return scan<C, scs...>(src);
        else
          return {tt::unexpected,
                  src.substr(0, 1)};
      else
        return tk;
    }

    template <typename C,
              typename... scanners>
    std::vec<token<C>> scan_all(std::sv<C> src)
    {
      using tt = ttype;
      std::vector<token<C>> tks;

      while (not src.empty())
      {
        token<C> &&tk = scan_one(src);
        src = src.substr(tk.val.size());

        if (tk.type == tt::sm_blank)
          continue;
        else if (tk.type == tt::unexpected)
          // TODO: voir ce que l'on fait ici
          src = src.substr(1);
        else
          tks.push_back(tk);
      }

      return tks;
    }
  };

  template <typename C, ttype tt>
  token<C> match(std::string_view);

  void proto()
  {
    using tt = ttype;
    scanner_definition<
        keyword_scanner<"type", tt::kw_type>,
        keyword_scanner<"build", tt::kw_build>,
        keyword_scanner<"copy", tt::kw_copy>,
        keyword_scanner<"move", tt::kw_move>,
        keyword_scanner<"fun", tt::kw_fun>,
        keyword_scanner<"del", tt::kw_del>,
        keyword_scanner<"if", tt::kw_if>,
        keyword_scanner<"while", tt::kw_while>,
        keyword_scanner<"for", tt::kw_for>,
        keyword_scanner<"true", tt::kw_true>,
        keyword_scanner<"false", tt::kw_false>,
        keyword_scanner<"return", tt::kw_return>,
        keyword_scanner<"(", tt::sm_lbracket>,
        keyword_scanner<")", tt::sm_rbracket>,
        keyword_scanner<"[", tt::sm_lsbracket>,
        keyword_scanner<"]", tt::sm_rsbracket>,
        keyword_scanner<"{", tt::sm_lbrace>,
        keyword_scanner<"}", tt::sm_rbrace>,
        keyword_scanner<":=", tt::sm_mv>,
        keyword_scanner<"=", tt::sm_eq>,
        keyword_scanner<":", tt::sm_colon>,
        keyword_scanner<";", tt::sm_scolon>,
        keyword_scanner<",", tt::sm_comma>,
        keyword_scanner<".", tt::sm_dot>,
        identifier_scanner,
        integer_scanner,
        string_scanner,
        ignore_scanner,
        empty_scanner>;
  }

  template <typename C>
  std::vector<token<C>>
  tokens(std::sv<C> src)
  {
    using tt = ttype;

    std::vector<token<C>> tks;

    while (not src.empty())
    {
      src = ignore_blanks(src);

      token<C> tk = prs(src);

      if (tk.tp == tt::last)
        src = "";
      if (tk.tp == tt::unexpected)
        src = src.substr(1);
      else
        src = src.substr(tk.val.size());

      tks.push_back(tk);
    }

    return tks;
  }

  template <typename C>
  struct tokens_scanner
  {
    std::vec<token<C>>
    operator()(std::sv<C> src)
    {
      std::vec<token<C>> tks;
    }
  };

} // namespace sitl
#endif